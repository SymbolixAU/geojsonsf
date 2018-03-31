#include "rapidjson/document.h"

#include <algorithm>
#include <Rcpp.h>
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"

using namespace Rcpp;

void parse_geometry_object(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types,
                           int& sfg_objects) {

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

Rcpp::List parse_geometry_collection_object(const Value& val,
                                            Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types,
                                            int& sfg_objects) {
	std::string geom_type;

	auto geometries = val["geometries"].GetArray();
	int n = geometries.Size();

	Rcpp::List geom_collection(n);

	for (int i = 0; i < n; i++) {
		const Value& gcval = geometries[i];
		geom_type = gcval["type"].GetString();
		parse_geometry_object(geom_collection, i, gcval, bbox, geometry_types, sfg_objects);
	}
	geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");

	return geom_collection;
}

Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects) {
	// A feature MUST have
	// - type
	// - geometry
	// - properties

	// TODO:
	// error if there is no member called '"type": "Feature"
	const Value& geometry = feature["geometry"];
	Rcpp::List sfc(1);
	parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);

	// TODO:
	// parse properties

	return sfc;
}


Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types,
                                           int& sfg_objects) {
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
		feature_collection[i] = parse_feature_object(feature, bbox, geometry_types, sfg_objects);
	}

	return feature_collection;
}

void parse_geojson(const Value& v,
                   Rcpp::List& sfc,
                   Rcpp::List& properties,
                   int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types,
                   int& sfg_objects) {

	//TODO: checks if fields exist

	Rcpp::List res(1);
	std::string geom_type;

	if (v.HasMember("type") == FALSE) Rcpp::stop("No 'type' member - invalid GeoJSON");

	geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		res = parse_feature_object(v, bbox, geometry_types, sfg_objects);
		sfg_objects++;
		res.attr("geo_type") = "FEATURE";
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects);
		sfg_objects += res.length();
		res.attr("geo_type") = "FEATURECOLLECTION";

		sfc[i] = res;

	} else if (geom_type == "GeometryCollection") {

		res = parse_geometry_collection_object(v, bbox, geometry_types, sfg_objects);
		sfg_objects++;
		sfc[i] = res;

	} else {

		parse_geometry_object(sfc, i, v, bbox, geometry_types, sfg_objects);
		sfg_objects++;
	}
}

void parse_geojson_object(Document& d,
                          Rcpp::List& sfc,
                          Rcpp::List& properties,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types,
                          int& sfg_objects) {
	const Value& v = d;
	parse_geojson(v, sfc, properties, 0, bbox, geometry_types, sfg_objects);
}

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects) {
	const Value& v = d[i];
	parse_geojson(v, sfc, properties, i, bbox, geometry_types, sfg_objects);
}


Rcpp::List geojson_to_sf(const char* geojson,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects) {

	Document d;
	d.Parse(geojson);
	Rcpp::List sf(1);
	Rcpp::List sfc(1);
	Rcpp::List properties(1);

	if (d.IsObject() ) {
		//Rcpp::Rcout << "debug: is OBJECT" << std::endl;

	  Rcpp::List sfg(1);
		parse_geojson_object(d, sfg, properties, bbox, geometry_types, sfg_objects);
		sfc[0] = sfg;

	} else if (d.IsArray()) {
		Rcpp::Rcout << "debug: is ARRAY" << std::endl;

		Rcpp::List sfgs(d.Size());

		for (int i = 0; i < d.Size(); i++) {
			parse_geojson_array(d, sfgs, properties, i, bbox, geometry_types, sfg_objects);
		}
		sfc[0] = sfgs;
	}
	//Rcpp::List res = construct_sfc(sfg_objects, sfc, bbox, geometry_types);

	return sfc;
}

// TODO:
// A fector of goejson strings should be come sfgs...?
//
// - geometry becomes sfg
// - feature becomes sf
// - feature collection become sf


// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	int sfg_objects = 0;  // keep track of number of objects

	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	//Rcpp::StringVector sfc_classes = start_sfc_classes(n);

	//Rcpp::List sf = geojson_to_sf(geojson[0], bbox, geometry_types, sfg_objects);

	Rcpp::List sf(n);
	for (int i = 0; i < n; i++ ){
		sf[i] = geojson_to_sf(geojson[i], bbox, geometry_types, sfg_objects);
	}

  // If it's an object...
	//Rcpp::List res = construct_sfc(sfg_objects, sf, bbox, geometry_types);

  // If it's an array...
  Rcpp::List res = construct_sfc_array(sfg_objects, sf, bbox, geometry_types);

	//Rcpp::List res = sf;
	return res;
}
