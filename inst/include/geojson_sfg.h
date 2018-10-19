#ifndef GEOJSONSF_SFG_H
#define GEOJSONSF_SFG_H

#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace rapidjson;

double get_lon(const Value& coord_array);
double get_lat(const Value& coord_array);

void get_points( const Value& point_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                 bool requires_attribute, std::string attribute );

void get_line_string( const Value& line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                      bool requires_attribute, std::string attribute, int& max_cols );

void get_multi_line_string( const Value& line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                      bool requires_attribute, std::string attribute );

void get_polygon( const Value& multi_line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                  bool requires_attribute, std::string attribute );

void get_multi_polygon( const Value& multi_line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                  bool requires_attribute, std::string attribute );

#endif
