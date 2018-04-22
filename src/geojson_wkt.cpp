
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"
using namespace rapidjson;
using namespace Rcpp;

void begin_wkt(std::ostringstream& os, std::string& geom_type) {

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

void end_wkt(std::ostringstream& os, std::string& geom_type) {

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

void object_separator(std::ostringstream& os) {
	os << ",";
}

void coord_separator(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << ",";
  }
}

void line_separator_wkt(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << "),(";
  }
}

void polygon_separate_wkt(std::ostringstream& os, int i, int n) {
	if (i < (n - 1) ) {
    os << ")),((";
	}
}


void add_lonlat_to_wkt_stream(std::ostringstream& os, float lon, float lat ) {
  os << lon << " " << lat;
}

void point_to_wkt(std::ostringstream& os, const Value& coord_array) {
  Rcpp::NumericVector point(2);
  point[0] = get_lon(coord_array);
  point[1] = get_lat(coord_array);
  add_lonlat_to_wkt_stream(os, point[0], point[1]);
}


void multi_point_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i]);
    coord_separator(os, i, n);
  }
}

void line_string_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i]);
    coord_separator(os, i, n);
  }
}

void multi_line_string_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i]);
    line_separator_wkt(os, i, n);
  }
}

void polygon_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i]);
    line_separator_wkt(os, i, n);
  }
}

void multi_polygon_to_wkt(std::ostringstream& os, const Value& coord_array) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    validate_array(coord_array[i]);
    polygon_to_wkt(os, coord_array[i]);
    polygon_separate_wkt(os, i, n);
  }
}


