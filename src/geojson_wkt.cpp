
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"
using namespace rapidjson;
using namespace Rcpp;

void beginWKT(std::ostringstream& os, std::string& geom_type) {

  if (geom_type == "Point") {
    os << "POINT (";
  } else if (geom_type == "MultiPoint") {
    os << "MULTIPOINT ((";
  } else if (geom_type == "LineString") {
    os << "LINESTRING (";
  } else if (geom_type == "MultiLineString") {
    os << "MULTILINESTRING ((";
  } else if (geom_type == "Polygon") {
    os << "POLYGON ((";
  } else if (geom_type == "MultiPolygon") {
    os << "MULTIPOLYGON (((";
  } else if (geom_type == "GeometryCollection") {
    os << "GEOMETRYCOLLECTION (";
  }
}

void endWKT(std::ostringstream& os, std::string& geom_type) {

  if (geom_type == "Point") {
    os << ")";
  } else if (geom_type == "MultiPoint") {
    os << "))";
  } else if (geom_type == "LineString") {
    os << ")";
  } else if (geom_type == "MultiLineString") {
    os << "))";
  } else if (geom_type == "Polygon") {
    os << "))";
  } else if (geom_type == "MultiPolygon") {
    os << ")))";
  } else if (geom_type == "GeometryCollection") {
    os << ")";
  }
}

void coordSeparateWKT(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << ", ";
  }
}

void lineSeparateWKT(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << "),(";
  }
}

void polygonSeparateWKT(std::ostringstream& os, int i, int n) {
	if (i < (n - 1) ) {
    os << ")),((";
	}
}


void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
  os << lon << " " << lat;
}

void point_to_wkt(std::ostringstream& os, const Value& coord_array) {
  Rcpp::NumericVector point(2);
  point[0] = get_lon(coord_array);
  point[1] = get_lat(coord_array);
  addLonLatToWKTStream(os, point[0], point[1]);
}


void multi_point_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
  for (int i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i]);
    coordSeparateWKT(os, i, n);
  }
}

void line_string_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();

  for (int i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i]);
    coordSeparateWKT(os, i, n);
  }
}

void multi_line_string_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();

  for (int i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i]);
    lineSeparateWKT(os, i, n);
  }
}

void polygon_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();

  for (int i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i]);
    lineSeparateWKT(os, i, n);
  }
}

void multi_polygon_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
  for (int i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    polygon_to_wkt(os, coord_array[i]);
    polygonSeparateWKT(os, i, n);
  }
}


