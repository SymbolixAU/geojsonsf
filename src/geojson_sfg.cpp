// [[Rcpp::depends(rapidjsonr)]]

#include "rapidjson/document.h"

#include <Rcpp.h>
#include "geojson_sfg.h"
#include "geojson_sfc.h"

using namespace Rcpp;
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes(std::string geom_type) {
	return Rcpp::CharacterVector::create("XY", geom_type, "sfg");
}


// TODO:
// get different types (int, float, ...)
double get_lon(const Value& coord_array) {
	return coord_array[0].GetDouble();
}

double get_lat(const Value& coord_array) {
	return coord_array[1].GetDouble();
}

Rcpp::NumericVector get_point(const Value& point_array, Rcpp::NumericVector& bbox) {
	Rcpp::NumericVector point(2);
	point[0] = get_lon(point_array);
	point[1] = get_lat(point_array);
	point.attr("class") = sfg_attributes("POINT");

	calculate_bbox(bbox, point);

	return point;
}

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array, Rcpp::NumericVector& bbox) {
	size_t n = multi_point_array.Size();
	Rcpp::NumericMatrix multi_point(n, 2);

	for (int i = 0; i < n; i++) {
		multi_point(i, _) = get_point(multi_point_array[i], bbox);
	}
	multi_point.attr("class") = sfg_attributes("MULTIPOINT");
	return multi_point;
}

Rcpp::NumericMatrix get_line_string(const Value& line_array, Rcpp::NumericVector& bbox) {
	size_t n = line_array.Size();
	Rcpp::NumericMatrix line(n, 2);

	for (int i = 0; i < n; i++) {
		line(i, _) = get_point(line_array[i], bbox);
	}
	line.attr("class") = sfg_attributes("LINESTRING");
	return line;
}

Rcpp::List get_multi_line_string(const Value& multi_line_array, Rcpp::NumericVector& bbox) {
	size_t n = multi_line_array.Size();
	Rcpp::List multi_line(n);

	for (int i = 0; i < n; i++) {
		multi_line[i] = get_line_string(multi_line_array[i], bbox);
	}
	multi_line.attr("class") = sfg_attributes("MULTILINESTRING");
	return multi_line;
}

Rcpp::List get_polygon(const Value& polygon_array, Rcpp::NumericVector& bbox) {
	size_t n = polygon_array.Size();
	Rcpp::List polygon(n);
	for (int i = 0; i < n; i++) {
		polygon[i] = get_line_string(polygon_array[i], bbox);
	}
	polygon.attr("class") = sfg_attributes("POLYGON");
	return polygon;
}

Rcpp::List get_multi_polygon(const Value& multi_polygon_array, Rcpp::NumericVector& bbox) {
	size_t n = multi_polygon_array.Size();
	Rcpp::List multi_polygon(n);
	for (int i = 0; i < n; i++) {
		multi_polygon[i] = get_polygon(multi_polygon_array[i], bbox);
	}
	multi_polygon.attr("class") = sfg_attributes("MULTIPOLYGON");
	return multi_polygon;
}










