#include "rapidjson/document.h"

#include <Rcpp.h>
#include "geojson_sfg.h"
#include "geojson_sfc.h"

using namespace Rcpp;
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes(std::string geom_type) {
  return Rcpp::CharacterVector::create("XY", geom_type, "sfg");
}

double get_lon(const Value& coord_array) {
  return coord_array[0].GetDouble();
}

double get_lat(const Value& coord_array) {
  return coord_array[1].GetDouble();
}

Rcpp::NumericVector parse_point(const Value& coord_array, Rcpp::NumericVector& bbox) {
  Rcpp::NumericVector point(2);
  point[0] = get_lon(coord_array);
  point[1] = get_lat(coord_array);
  calculate_bbox(bbox, point);
  return point;
}

Rcpp::NumericVector get_point(const Value& point_array, Rcpp::NumericVector& bbox) {
  Rcpp::NumericVector point = parse_point(point_array, bbox);
  point.attr("class") = sfg_attributes("POINT");
  return point;
}

Rcpp::NumericMatrix parse_line(const Value& coord_array, Rcpp::NumericVector& bbox) {
  size_t n = coord_array.Size();
  Rcpp::NumericMatrix line_string(n, 2);
  for (int i = 0; i < n; i++) {
    line_string(i, _) = parse_point(coord_array[i], bbox);
  }
  return line_string;
}

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array, Rcpp::NumericVector& bbox) {
  Rcpp::NumericMatrix multi_point = parse_line(multi_point_array, bbox);
  multi_point.attr("class") = sfg_attributes("MULTIPOINT");
  return multi_point;
}

Rcpp::NumericMatrix get_line_string(const Value& line_array, Rcpp::NumericVector& bbox) {
  Rcpp::NumericMatrix line_string = parse_line(line_array, bbox);
  line_string.attr("class") = sfg_attributes("LINESTRING");
  return line_string;
}

Rcpp::List get_multi_line_string(const Value& multi_line_array, Rcpp::NumericVector& bbox) {
  size_t n = multi_line_array.Size();
  Rcpp::List multi_line(n);

  for (int i = 0; i < n; i++) {
    multi_line[i] = parse_line(multi_line_array[i], bbox);
  }
  multi_line.attr("class") = sfg_attributes("MULTILINESTRING");
  return multi_line;
}

Rcpp::List get_polygon(const Value& polygon_array, Rcpp::NumericVector& bbox) {
  size_t n = polygon_array.Size();
  Rcpp::List polygon(n);

  for (int i = 0; i < n; i++) {
    polygon[i] = parse_line(polygon_array[i], bbox);
  }

  polygon.attr("class") = sfg_attributes("POLYGON");
  return polygon;
}

Rcpp::List get_multi_polygon(const Value& multi_polygon_array, Rcpp::NumericVector& bbox) {
  size_t n = multi_polygon_array.Size();
  Rcpp::List multi_polygon(n);

  for (int i = 0; i < n; i++) {

    size_t np = multi_polygon_array[i].Size();
    Rcpp::List polygon(np);
    const Value& polygon_array = multi_polygon_array[i];

    for (int j = 0; j < np; j++) {
      polygon[j] = parse_line(polygon_array[j], bbox);
    }
    multi_polygon[i] = polygon;
  }

  multi_polygon.attr("class") = sfg_attributes("MULTIPOLYGON");
  return multi_polygon;
}










