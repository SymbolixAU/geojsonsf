
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"
#include "geojson_properties.h"

using namespace rapidjson;
using namespace Rcpp;


void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
	os << lon << " " << lat;
}

void encode_wkt_point(std::ostringstream& os, const Value& coord_array) {
	Rcpp::NumericVector point(2);
	point[0] = get_lon(coord_array);
	point[1] = get_lat(coord_array);

	addLonLatToWKTStream(os, point[0]*(float)1e-5, point[1]*(float)1e-5);
}

void parse_line_to_wkt(std::ostringstream& os, const Value& coord_array) {
	size_t n = coord_array.Size();

	for (int i = 0; i < n; i++) {
		encode_wkt_point(os, coord_array[i]);
	}
}



void geom_type(const char *cls, int *tp = NULL) {
/*
	int type = 0;
	if (strcmp(cls, "POINT") == 0)
		type = POINT;
	else if (strcmp(cls, "MULTIPOINT") == 0)
		type = MULTIPOINT;
	else if (strcmp(cls, "LINESTRING") == 0)
		type = LINESTRING;
	else if (strcmp(cls, "POLYGON") == 0)
		type = POLYGON;
	else if (strcmp(cls, "MULTILINESTRING") == 0)
		type = MULTILINESTRING;
	else if (strcmp(cls, "MULTIPOLYGON") == 0)
		type = MULTIPOLYGON;
	else
		type = UNKNOWN;
	if (tp != NULL)
		*tp = type;
	*/
}

void beginWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {

	int tp;
	geom_type(cls[1], &tp);

	switch( tp ) {
	case POINT:
		os << "POINT ";
		break;
	case MULTIPOINT:
		os << "MULTIPOINT (";
		break;
	case LINESTRING:
		os << "LINESTRING ";
		break;
	case MULTILINESTRING:
		os << "MULTILINESTRING (";
		break;
	case POLYGON:
		os << "POLYGON (";
		break;
	case MULTIPOLYGON:
		os << "MULTIPOLYGON ((";
		break;
	default: {
			Rcpp::stop("Unknown geometry type");
		}
	}
}

void endWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {

	int tp;
	geom_type(cls[1], &tp);

	switch( tp ) {
	case POINT:
		os << "";
		break;
	case MULTIPOINT:
		os << ")";
		break;
	case LINESTRING:
		os << "";
		break;
	case MULTILINESTRING:
		os << ")";
		break;
	case POLYGON:
		os << ")";
		break;
	case MULTIPOLYGON:
		os << "))";
		break;
	default: {
			Rcpp::stop("Unknown geometry type");
		}
	}
}

void coordSeparateWKT(std::ostringstream& os) {
  os << ", ";
}


void parse_geometry_object_wkt(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           std::set< std::string >& geometry_types,
                           int& wkt_objects) {

	validate_type(geometry, wkt_objects);
	validate_coordinates(geometry, wkt_objects);

	std::string geom_type = geometry["type"].GetString();
	const Value& coord_array = geometry["coordinates"];
	geometry_types.insert(geom_type);

	if (geom_type == "Point") {
		sfc[i] = get_point(coord_array);
		//sfc_classes[counter] = "POINT";

	} else if (geom_type == "MultiPoint") {
		sfc[i] = get_multi_point(coord_array);
		//sfc_classes[counter] = "MULTIPOINT";

	} else if (geom_type == "LineString") {
		sfc[i] = get_line_string(coord_array);
		//sfc_classes[counter] = "LINESTRING";

	} else if (geom_type == "MultiLineString") {
		sfc[i] = get_multi_line_string(coord_array);
		//sfc_classes[counter] = "MULTILINESTRING";

	} else if (geom_type == "Polygon") {
		sfc[i] = get_polygon(coord_array);
		//sfc_classes[counter] = "POLYGON";

	} else if (geom_type == "MultiPolygon") {
		sfc[i] = get_multi_polygon(coord_array);
		//sfc_classes[counter] = "MULTIPOLYGON";

	} else {
		Rcpp::stop("unknown sfg type");
	}
}

Rcpp::List parse_geometry_collection_object_wkt(const Value& val,
                                            std::set< std::string >& geometry_types,
                                            int& wkt_objects) {
	std::string geom_type;

	auto geometries = val["geometries"].GetArray();
	int n = geometries.Size();

	Rcpp::List geom_collection(n);

	for (int i = 0; i < n; i++) {
		const Value& gcval = geometries[i];
		geom_type = gcval["type"].GetString();
		parse_geometry_object_wkt(geom_collection, i, gcval, geometry_types, wkt_objects);
	}
	geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");

	return geom_collection;
}



Rcpp::List parse_feature_object_wkt(const Value& feature,
                                std::set< std::string >& geometry_types,
                                int& wkt_objects,
                                std::set< std::string >& property_keys,
                                Document& doc_properties,
                                std::map< std::string, std::string>& property_types) {

	validate_geometry(feature, wkt_objects);
	validate_properties(feature, wkt_objects);

	const Value& geometry = feature["geometry"];
	Rcpp::List sfc(1);
	parse_geometry_object_wkt(sfc, 0, geometry, geometry_types, wkt_objects);
	wkt_objects++;
	// get property keys
	const Value& p = feature["properties"];
	get_property_keys(p, property_keys);
	get_property_types(p, property_types);


	//https://stackoverflow.com/a/33473321/5977215
	std::string s = std::to_string(sfg_objects);
	Value n(s.c_str(), doc_properties.GetAllocator());

	// TODO: is this method deep-cloning?
	Value properties(feature["properties"], doc_properties.GetAllocator());
	doc_properties.AddMember(n, properties, doc_properties.GetAllocator());

	return sfc;
}


Rcpp::List parse_feature_collection_object_wkt(const Value& fc,
                                           std::set< std::string >& geometry_types,
                                           int& wkt_objects,
                                           std::set< std::string >& property_keys,
                                           Document& doc_properties,
                                           std::map< std::string, std::string>& property_types) {
	// a FeatureCollection MUST have members called features,
	// which is an array
	validate_features(fc, wkt_objects);

	auto features = fc["features"].GetArray();

	int n = features.Size(); // number of features
	Rcpp::List feature_collection(n);
	//std::string geom_type = "FeatureCollection";

	for (int i = 0; i < n; i++) {
		const Value& feature = features[i];
		feature_collection[i] = parse_feature_object_wkt(feature, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
	}
	return feature_collection;
}


void parse_geojson_wkt(const Value& v,
                       Rcpp::List& sfc,
                       Rcpp::List& properties,
                       int i,
                       std::set< std::string >& geometry_types,
                       int& wkt_objects,
                       std::set< std::string >& property_keys,
                       Document& doc_properties,
                       std::map< std::string, std::string >& property_types
                         ) {
  Rcpp::List res(1);
	validate_type(v, wkt_objects);

	std::string geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		res = parse_feature_object_wkt(v, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object_wkt(v, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
		sfc[i] = res;

	} else if (geom_type == "GeometryCollection") {

		res = parse_geometry_collection_object_wkt(v, geometry_types, wkt_objects);
		wkt_objects++;
		sfc[i] = res;

	} else {

		parse_geometry_object_wkt(sfc, i, v, geometry_types, wkt_objects);
		wkt_objects++;
	}

}

void parse_geojson_object_wkt(Document& d,
                              Rcpp::List& sfc,
                              Rcpp::List& properties,
                              std::set< std::string >& geometry_types,
                              int& wkt_objects,
                              std::set< std::string >& property_keys,
                              Document& doc_properties,
                              std::map< std::string, std::string>& property_types
                                ) {
  const Value& v = d;
	parse_geojson_wkt(v, sfc, properties, 0, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
}

void parse_geojson_array_wkt(Document& d,
                             Rcpp::List& sfc,
                             Rcpp::List& properties,
                             int i,
                             std::set< std::string >& geometry_types,
                             int& wkt_objects,
                             std::set< std::string >& property_keys,
                             Document& doc_properties,
                             std::map< std::string, std::string>& property_types
                               ) {
  const Value& v = d[i];
	parse_geojson_wkt(v, sfc, properties, i, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
}

Rcpp::List geojson_to_wkt(const char* geojson,
                          std::set< std::string >& geometry_types,
                          int& wkt_objects,
                          std::set< std::string >& property_keys,
                          Document& doc_properties,
                          std::map< std::string, std::string >& property_types
                            ) {
  // TODO:
  // grab the geometry data and stream to WKT
  Document d;
  safe_parse(d, geojson);
  Rcpp::List sf(1);
  Rcpp::List sfc(1);
  Rcpp::List properties(1);

	std::ostringstream os;
  // Need to 'recurse' into the GeoJSON like what i did for geo_sf
  // because it can be arrays, objects, vectors.
	if (d.IsObject()) {
		Rcpp::List sfg(1);
		parse_geojson_object_wkt(d, sfg, properties, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
		sfc[0] = sfg;

	} else if (d.IsArray()) {

	}
	return sfc;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_wkt(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	int wkt_objects = 0;  // keep track of number of objects
	int row_index;

	// Attributes to keep track of along the way
	std::set< std::string > geometry_types = start_geometry_types();
	std::set< std::string > property_keys;   // storing all the 'key' values from 'properties'
	std::map< std::string, std::string> property_types;

	Document doc_properties;    // Document to store the 'properties'
	doc_properties.SetObject();
	Rcpp::List sfc(n);

	for (int geo_ele = 0; geo_ele < n; geo_ele++) {
		sfc[geo_ele] = geojson_to_wkt(geojson[geo_ele], geometry_types, wkt_objects, property_keys, doc_properties, property_types);
	}


	return sfc;
}
