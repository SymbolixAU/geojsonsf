#include "rapidjson/document.h"

#include <algorithm>
#include <Rcpp.h>
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"

using namespace Rcpp;

void parse_geometry_object(Rcpp::List& sfc, int i, const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types) {

	std::string geom_type = geometry["type"].GetString();
	const Value& coord_array = geometry["coordinates"];
	geometry_types.insert(geom_type);

	if (geom_type == "Point") {
		sfc[i] = get_point(coord_array, bbox);
		//sfc_classes[counter] = "POINT";

	} else if (geom_type == "MultiPoint") {
		sfc[i] = get_multi_point(coord_array, bbox);
		//sfc_classes[counter] = "MULTIPOINT";

	} else if (geom_type == "LineString") {
		sfc[i] = get_line_string(coord_array, bbox);
		//sfc_classes[counter] = "LINESTRING";

	} else if (geom_type == "MultiLinestring") {
		sfc[i] = get_multi_line_string(coord_array, bbox);
		//sfc_classes[counter] = "MULTILINESTRING";

	} else if (geom_type == "Polygon") {
		sfc[i] = get_polygon(coord_array, bbox);
		//sfc_classes[counter] = "POLYGON";

	} else if (geom_type == "MultiPolygon") {
		sfc[i] = get_multi_polygon(coord_array, bbox);
		//sfc_classes[counter] = "MULTIPOLYGON";

	} else {
		Rcpp::stop("unknown sfg type");
	}
}

Rcpp::List parse_geometry_collection_object(const Value& val, Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types) {
	std::string geom_type;

	auto geometries = val["geometries"].GetArray();
	int n = geometries.Size();

	Rcpp::List geom_collection(n);

	for (int i = 0; i < n; i++) {
		const Value& gcval = geometries[i];
		geom_type = gcval["type"].GetString();
		parse_geometry_object(geom_collection, i, gcval, bbox, geometry_types);
	}
	geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");
	return geom_collection;
}

Rcpp::List parse_feature_object(const Value& feature, Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types) {
	// A feature MUST have
	// - type
	// - geometry
	// - properties

	// TODO:
	// error if there is no member called '"type": "Feature"
	const Value& geometry = feature["geometry"];
	Rcpp::List sfc(1);
	parse_geometry_object(sfc, 0, geometry, bbox, geometry_types);

	// TODO:
	// parse properties

	return sfc;
}


Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types) {
	// a FeatureCollection MUST have members called features,
	// which is an array

	// TODO:
	// - error handle if 'features' not present
	auto features = fc["features"].GetArray();

	int n = features.Size(); // number of features
	Rcpp::List feature_collection(n);
	std::string geom_type = "FeatureCollection";

	for (int i = 0; i < n; i++) {
		const Value& feature = features[i];
		feature_collection[i] = parse_feature_object(feature, bbox, geometry_types);
	}
	//attach_sfc_attributes(feature_collection, geom_type, bbox, geometry_types);

	return feature_collection;
}

void parse_geojson(const Value& v,
                   Rcpp::List& sfc, int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types) {

	//TODO: checks if fields exist

	Rcpp::List res(1);
	std::string geom_type;

	if (v.HasMember("type") == FALSE) Rcpp::stop("No 'type' member - invalid GeoJSON");

	geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		//std::string type = v["geometry"]["type"].GetString();
		//transform(type.begin(), type.end(), type.begin(), toupper);

		res = parse_feature_object(v, bbox, geometry_types);
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object(v, bbox, geometry_types);
		//Rcpp::Rcout << "debug: featurecollection size: " << res.size() << std::endl;
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfc[i] = res;

	} else if (geom_type == "GeometryCollection") {

		res = parse_geometry_collection_object(v, bbox, geometry_types);
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfc[i] = res;

	} else {

		parse_geometry_object(sfc, i, v, bbox, geometry_types);
		//attach_sfc_attributes(sfc, geom_type, bbox, geometry_types);
	}
	//attach_sfc_attributes(sfc, geom_type, bbox, geometry_types);
}

void parse_geojson_object(Document& d, Rcpp::List& sfc,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types) {
	const Value& v = d;
	parse_geojson(v, sfc, 0, bbox, geometry_types);
}

void parse_geojson_array(Document& d, Rcpp::List& sfc, int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {
	const Value& v = d[i];
	parse_geojson(v, sfc, i, bbox, geometry_types);
}


Rcpp::List geojson_to_sf(const char* geojson, Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {

	// TODO:
	// only start building the result sf when we are inside the final array


	Document d;
	d.Parse(geojson);
	Rcpp::List sf(1);

	if (d.IsObject() ) {
		Rcpp::Rcout << "debug: is OBJECT" << std::endl;

	  //Rcpp::List sfg(1);
		parse_geojson_object(d, sf, bbox, geometry_types);
		//sf[0] = sfg;

//	} else if (d.IsArray()) {
//		Rcpp::Rcout << "debug: is ARRAY" << std::endl;
//
//		Rcpp::List sfc(d.Size());
//
//		for (int i = 0; i < d.Size(); i++) {
//			parse_geojson_array(d, sfc, i, bbox, geometry_types);
//		}
//
//		sf[0] = sfc;
	}
	return sf;
}

// TODO:
// A fector of goejson strings should be come sfgs...?
//
// - geometry becomes sfg
// - feature becomes sf
// - feature collection become sf


// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(const char* geojson) {

	// iterate over the geojson
	//int n = geojson.size();

	// iff a vector, collapse to an array...


	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	//Rcpp::StringVector sfc_classes = start_sfc_classes(n);

	Rcpp::List sf = geojson_to_sf(geojson, bbox, geometry_types);

	//Rcpp::List sfc(n);
  //
	//for (int i = 0; i < n; i++ ){
	//	sfc[i] = geojson_to_sf(geojson[i], bbox, geometry_types);
	//}

	return sf;
}
