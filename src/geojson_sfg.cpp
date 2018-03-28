// [[Rcpp::depends(rapidjsonr)]]

#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace rapidjson;

// TODO:
// get different types (int, float, ...)
double get_lon(const Value& coord_array) { return coord_array[0].GetDouble(); }
double get_lat(const Value& coord_array) { return coord_array[1].GetDouble(); }

Rcpp::NumericVector get_point(const Value& point_array) {
  Rcpp::NumericVector point(2);
  point[0] = get_lon(point_array);
  point[1] = get_lat(point_array);
  return point;
}

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array) {
  size_t n = multi_point_array.Size();
  Rcpp::NumericMatrix multi_point(n, 2);

  for (int i = 0; i < n; i++) {
  	multi_point(i, 0) = get_lon(multi_point_array[i]);
  	multi_point(i, 1) = get_lat(multi_point_array[i]);
   }
  return multi_point;
}

Rcpp::NumericMatrix get_line(const Value& line_array) {
  size_t n = line_array.Size();
  Rcpp::NumericMatrix line(n, 2);

  for (int i = 0; i < n; i++) {
    line(i, 0) = get_lon(line_array[i]);
    line(i, 1) = get_lat(line_array[i]);
  }
  return line;
}

Rcpp::List get_multi_line(const Value& multi_line_array) {
  size_t n = multi_line_array.Size();
  Rcpp::List multi_line(n);

  for (int i = 0; i < n; i++) {
    multi_line[i] = get_line(multi_line_array[i]);
  }
  return multi_line;
}

Rcpp::List get_polygon(const Value& polygon_array) {
  size_t n = polygon_array.Size();
  Rcpp::List polygon(n);
  for (int i = 0; i < n; i++) {
    polygon[i] = get_line(polygon_array[i]);
  }
  return polygon;
}

Rcpp::List get_multi_polygon(const Value& multi_polygon_array) {
  size_t n = multi_polygon_array.Size();
  Rcpp::List multi_polygon(n);
  for (int i = 0; i < n; i++) {
    multi_polygon[i] = get_polygon(multi_polygon_array[i]);
  }
  return multi_polygon;
}

Rcpp::List geojson_to_sf(const char* geojson) {

	Document d;
	d.Parse(geojson);
	Rcpp::List sfg(1);
	const Value& arr = d.GetArray();

	std::cout << "arr size: " << arr.Size() << std::endl;

	Rcpp::NumericVector pt = get_point(arr);
	sfg[0] = pt;

	return sfg;

}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	Rcpp::List lst(n);

	for (int i = 0; i < n; i++ ){
		lst[i] = geojson_to_sf(geojson[i]);
	}
	return lst;
}




