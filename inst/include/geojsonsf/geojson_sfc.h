#ifndef GEOJSONSF_SFC_H
#define GEOJSONSF_SFC_H

#include <Rcpp.h>

void fetch_geometries(Rcpp::List& sf, Rcpp::List& res, int& sfg_counter);

void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& point);

Rcpp::NumericVector start_bbox();

Rcpp::StringVector start_sfc_classes(size_t collectionCount);

Rcpp::List construct_sfc(int& sfg_objects,
                         Rcpp::List& sfc,
                         Rcpp::NumericVector& bbox,
                         std::unordered_set< std::string >& geometry_types,
                         int& nempty);

#endif
