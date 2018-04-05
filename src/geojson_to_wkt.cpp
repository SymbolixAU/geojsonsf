
#include "rapidjson/document.h"
#include "geojsonsf.h"
#include "geojson_validate.h"
#include <Rcpp.h>

using namespace rapidjson;
using namespace Rcpp;


void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
	os << lon << " " << lat;
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

void parse_geojson_wkt(const Value& v, int i, int& wkt_objects) {

	validate_type(v, wkt_objects);

	std::string geom_type = v["type"].GetString();
}

void parse_geojson_object_wkt(Document& d, int& wkt_objects, int i) {
  const Value& v = d;
	parse_geojson_wkt(v, 0, wkt_objects);
}

void parse_geojson_array_wkt(Document& d, int i, int& wkt_objects) {
  const Value& v = d[i];
	parse_geojson_wkt(v, i, wkt_objects);
}

Rcpp::List geojson_to_wkt(const char* geojson, int& wkt_objects) {
  // TODO:
  // grab the geometry data and stream to WKT
  Document d;
  safe_parse(d, geojson);
  Rcpp::List wkt(1);

	std::ostringstream os;
  // Need to 'recurse' into the GeoJSON like what i did for geo_sf
  // because it can be arrays, objects, vectors.
	if (d.IsObject()) {

	} else if (d.IsArray()) {

	}

	return wkt;

}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_to_wkt(Rcpp::StringVector geojson) {
	int n = geojson.size();
	Rcpp::StringVector wkt(n);
	int wkt_objects = 0;

	for (int i = 0; i < n; i++) {
		wkt[i] = geojson_to_wkt(geojson[i], wkt_objects);
	}


	return wkt;
}
