#ifndef GEOJSONSF_GEOJSON_PARSE_H
#define GEOJSONSF_GEOJSON_PARSE_H

#include <Rcpp.h>
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_validate.hpp"

namespace geojsonsf {
namespace geojson {
namespace parse {

	inline void parse_geometry_object(Rcpp::List& sfc,
	                                  int i,
	                                  const Value& geometry,
	                                  Rcpp::NumericVector& bbox,
	                                  std::unordered_set< std::string >& geometry_types,
	                                  int& sfg_objects) {

		geojsonsf::validate::validate_type(geometry, sfg_objects);
		geojsonsf::validate::validate_coordinates(geometry, sfg_objects);
		geojsonsf::validate::validate_array(geometry["coordinates"], sfg_objects);

		std::string geom_type = geometry["type"].GetString();
		const Value& coord_array = geometry["coordinates"];
		geometry_types.insert( geom_type );


		if (geom_type == "Point") {
			geojsonsf::sfg::get_points( coord_array, bbox, sfc, i, true, "POINT");

		} else if (geom_type == "MultiPoint") {
			int max_cols = 2;
			geojsonsf::sfg::get_line_string( coord_array, bbox, sfc, i, true, "MULTIPOINT", max_cols );

		} else if (geom_type == "LineString") {
			int max_cols = 2;
			geojsonsf::sfg::get_line_string( coord_array, bbox, sfc, i, true, "LINESTRING", max_cols );

		} else if (geom_type == "MultiLineString") {
			geojsonsf::sfg::get_multi_line_string( coord_array, bbox, sfc, i, true, "MULTILINESTRING" );

		} else if (geom_type == "Polygon") {
			geojsonsf::sfg::get_polygon( coord_array, bbox, sfc, i, true, "POLYGON" );

		} else if (geom_type == "MultiPolygon") {
			geojsonsf::sfg::get_multi_polygon( coord_array, bbox, sfc, i, true, "MULTIPOLYGON" );

		} else {
			Rcpp::stop("unknown sfg type");
		}
	}

	inline Rcpp::List parse_geometry_collection_object(const Value& val,
	                                                   Rcpp::NumericVector& bbox,
	                                                   std::unordered_set< std::string >& geometry_types,
	                                                   int& sfg_objects,
	                                                   bool& expand_geometries) {
		std::string geom_type;
		geojsonsf::validate::validate_geometries(val, sfg_objects);
		auto geometries = val["geometries"].GetArray();
		unsigned int n = geometries.Size();
		unsigned int i;
		Rcpp::List geom_collection(n);

		for (i = 0; i < n; i++) {
			const Value& gcval = geometries[i];
			geojsonsf::validate::validate_type(gcval, sfg_objects);
			geom_type = gcval["type"].GetString();

			parse_geometry_object(geom_collection, i, gcval, bbox, geometry_types, sfg_objects);
		}
		geometry_types.insert( "GEOMETRYCOLLECTION" );

		if ( !expand_geometries ) {
			std::string dim = "XY";
			std::string attribute = "GEOMETRYCOLLECTION";
			geom_collection.attr("class") = geojsonsf::sfg::sfg_attributes( dim, attribute );
		} else {
			sfg_objects+=n;
		}
		return geom_collection;
	}

	inline Rcpp::List parse_feature_object(const Value& feature,
	                                       Rcpp::NumericVector& bbox,
	                                       std::unordered_set< std::string >& geometry_types,
	                                       int& sfg_objects,
	                                       std::unordered_set< std::string >& property_keys,
	                                       Document& doc_properties,
	                                       std::unordered_map< std::string, std::string>& property_types,
	                                       bool& expand_geometries,
	                                       int& nempty) {

		geojsonsf::validate::validate_geometry(feature, sfg_objects);

		Rcpp::List sfc(1);

		const Value& geometry = feature["geometry"];
		std::string type;

		if (geometry.Size() > 0) {

			geojsonsf::validate::validate_type( geometry, sfg_objects );
			type = geometry["type"].GetString();

			if (type == "GeometryCollection") {
				sfc[0] = geojsonsf::geojson::parse::parse_geometry_collection_object(geometry, bbox, geometry_types, sfg_objects, expand_geometries);
			} else {
				geojsonsf::geojson::parse::parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);
			}
		} else {
			geojsonsf::sfg::create_null_sfg(sfc, geometry_types, nempty);
		}

		if (type != "GeometryCollection") {
			sfg_objects++;
		} else if (type == "GeometryCollection" && !expand_geometries){
			sfg_objects++;
		}

		const Value& p = feature["properties"];

		geojsonsf::geojson_properties::get_property_keys(p, property_keys);
		geojsonsf::geojson_properties::get_property_types(p, property_types);

		unsigned int geomsize = 1;
		unsigned int i;

		if (expand_geometries && type == "GeometryCollection") {
			geojsonsf::validate::validate_geometries( geometry, sfg_objects );
			auto geometries = geometry["geometries"].GetArray();
			geomsize = geometries.Size();
		}

		std::string s;
		for ( i = 0; i < geomsize; i++ ) {
			//https://stackoverflow.com/a/33473321/5977215
			if ( expand_geometries ) {
				s = std::to_string( sfg_objects - i );
			} else {
				s = std::to_string( sfg_objects );
			}
			Value n( s.c_str(), doc_properties.GetAllocator() );

			// TODO: is this method deep-cloning?
			Value properties( feature["properties"], doc_properties.GetAllocator() );
			doc_properties.AddMember( n, properties, doc_properties.GetAllocator() );

		}

		return sfc;
	}

	inline Rcpp::List parse_feature_collection_object(const Value& fc,
	                                                  Rcpp::NumericVector& bbox,
	                                                  std::unordered_set< std::string >& geometry_types,
	                                                  int& sfg_objects,
	                                                  std::unordered_set< std::string >& property_keys,
	                                                  Document& doc_properties,
	                                                  std::unordered_map< std::string, std::string>& property_types,
	                                                  bool& expand_geometries,
	                                                  int& nempty) {

		// a FeatureCollection MUST have members (array) called features,
		geojsonsf::validate::validate_features(fc, sfg_objects);


		auto features = fc["features"].GetArray();

		unsigned int n = features.Size(); // number of features
		unsigned int i;

		Rcpp::List feature_collection(n);

		for ( i = 0; i < n; i++ ) {
			const Value& feature = features[i];
			feature_collection[i] = parse_feature_object(
				feature, bbox, geometry_types, sfg_objects, property_keys, doc_properties,
				property_types, expand_geometries, nempty
			);
		}
		return feature_collection;
	}

	inline void parse_geojson(const Value& v,
	                          Rcpp::List& sfc,
	                          Rcpp::List& properties,
	                          int i,
	                          Rcpp::NumericVector& bbox,
	                          std::unordered_set< std::string >& geometry_types,
	                          int& sfg_objects,
	                          std::unordered_set< std::string >& property_keys,
	                          Document& doc_properties,
	                          std::unordered_map< std::string, std::string>& property_types,
	                          bool& expand_geometries,
	                          int& nempty) {

		Rcpp::List res(1);
		geojsonsf::validate::validate_type(v, sfg_objects);

		std::string geom_type = v["type"].GetString();

		if (geom_type == "Feature") {
			res = parse_feature_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types, expand_geometries, nempty);
			sfc[i] = res;

		} else if (geom_type == "FeatureCollection") {

			res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types, expand_geometries, nempty);
			sfc[i] = res;

		} else if (geom_type == "GeometryCollection") {

			res = parse_geometry_collection_object(v, bbox, geometry_types, sfg_objects, expand_geometries);
			if (!expand_geometries) {
				sfg_objects++;
			}
			sfc[i] = res;

		} else {

			parse_geometry_object(sfc, i, v, bbox, geometry_types, sfg_objects);
			sfg_objects++;
		}
	}

	inline void parse_geojson_object(Document& d,
	                                 Rcpp::List& sfc,
	                                 Rcpp::List& properties,
	                                 Rcpp::NumericVector& bbox,
	                                 std::unordered_set< std::string >& geometry_types,
	                                 int& sfg_objects,
	                                 std::unordered_set< std::string >& property_keys,
	                                 Document& doc_properties,
	                                 std::unordered_map< std::string, std::string>& property_types,
	                                 bool& expand_geometries,
	                                 int& nempty) {
		const Value& v = d;
		parse_geojson(
			v, sfc, properties, 0, bbox, geometry_types, sfg_objects, property_keys,
			doc_properties, property_types, expand_geometries, nempty
		);

		// // out of order
		// for ( auto it = property_keys.begin(); it != property_keys.end(); it++ ) {
		// 	//const char s = *it->c_str();
		// 	std::cout << (*it) << std::endl;
		// }

	}

	inline void parse_geojson_array(Document& d,
	                                Rcpp::List& sfc,
	                                Rcpp::List& properties,
	                                int i,
	                                Rcpp::NumericVector& bbox,
	                                std::unordered_set< std::string >& geometry_types,
	                                int& sfg_objects,
	                                std::unordered_set< std::string >& property_keys,
	                                Document& doc_properties,
	                                std::unordered_map< std::string, std::string>& property_types,
	                                bool& expand_geometries,
	                                int& nempty) {
		const Value& v = d[i];
		parse_geojson(
			v, sfc, properties, i, bbox, geometry_types, sfg_objects, property_keys,
			doc_properties, property_types, expand_geometries, nempty
		);
	}

} // namespace parse
} // namespace geojson
} // namespace geojsonsf

#endif
