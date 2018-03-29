#include <Rcpp.h>
using namespace Rcpp;

#ifndef GEOJSONSFC_H
#define GEOJSONSFC_H

template <int RTYPE>
Rcpp::CharacterVector sfcClass(Vector<RTYPE> v);

Rcpp::CharacterVector getSfcClass(SEXP sfc);

void attach_sfc_attributes(Rcpp::List& sfc, Rcpp::StringVector sfc_classes, Rcpp::NumericVector bbox);

void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& pt);

Rcpp::NumericVector start_bbox();

Rcpp::StringVector start_sfc_classes(size_t collectionCount);

void attach_sfc_attributes(Rcpp::List& sfc, Rcpp::StringVector sfc_classes, Rcpp::NumericVector bbox);

//void sfc_get_sfg(bsoncxx::array::view& coord_array, int& geom_type,
//                Rcpp::List& sfc, int& counter, Rcpp::NumericVector& bbox);

#endif
