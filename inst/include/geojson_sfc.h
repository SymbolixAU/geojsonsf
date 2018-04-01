#ifndef GEOJSONSFC_H
#define GEOJSONSFC_H


#include <Rcpp.h>
using namespace Rcpp;

template <int RTYPE>
Rcpp::CharacterVector sfcClass(Vector<RTYPE> v);

Rcpp::CharacterVector getSfcClass(SEXP sfc);

void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& point);

std::string attach_class(Rcpp::List& sfc, std::string geom_type,
                         std::set< std::string >& geometry_types);

void attach_sfc_attributes(Rcpp::List& sfc, std::string& type,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types);

Rcpp::NumericVector start_bbox();

std::set< std::string > start_geometry_types();

//Rcpp::StringVector start_sfc_classes(size_t collectionCount);

//void sfc_get_sfg(bsoncxx::array::view& coord_array, int& geom_type,
//                Rcpp::List& sfc, int& counter, Rcpp::NumericVector& bbox);

Rcpp::List construct_sfc(int& sfg_objects,
                         Rcpp::List& sfc,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types);

#endif
