#ifndef GEOJSON_SFG_H
#define GEOJSON_SFG_H

#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace rapidjson;

double get_lon(const Value& coord_array);
double get_lat(const Value& coord_array);

Rcpp::NumericVector parse_point(const Value& coord_array);

Rcpp::NumericVector parse_point(const Value& coord_array, Rcpp::NumericVector& bbox);

Rcpp::NumericMatrix parse_line(const Value& coord_array);

Rcpp::NumericMatrix parse_line(const Value& coord_array, Rcpp::NumericVector& bbox);

Rcpp::NumericVector get_point(const Value& point_array);

Rcpp::NumericVector get_point(const Value& point_array, Rcpp::NumericVector& bbox);

void get_points( const Value& point_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                 bool requires_attribute, std::string attribute );

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array);

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array, Rcpp::NumericVector& bbox);

void get_line_string( const Value& line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                      bool requires_attribute, std::string attribute, int& max_cols );

Rcpp::NumericMatrix get_line_string(const Value& line_array);

Rcpp::NumericMatrix get_line_string(const Value& line_array, Rcpp::NumericVector& bbox);

Rcpp::List get_multi_line_string(const Value& multi_line_array);

Rcpp::List get_multi_line_string(const Value& multi_line_array, Rcpp::NumericVector& bbox);

void get_multi_line_string( const Value& line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                      bool requires_attribute, std::string attribute );

Rcpp::List get_polygon(const Value& polygon_array);

Rcpp::List get_polygon(const Value& polygon_array, Rcpp::NumericVector& bbox);

void get_polygon( const Value& multi_line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                  bool requires_attribute, std::string attribute );

Rcpp::List get_multi_polygon(const Value& multi_polygon_array);

Rcpp::List get_multi_polygon(const Value& multi_polygon_array, Rcpp::NumericVector& bbox);

void get_multi_polygon( const Value& multi_line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                  bool requires_attribute, std::string attribute );

#endif
