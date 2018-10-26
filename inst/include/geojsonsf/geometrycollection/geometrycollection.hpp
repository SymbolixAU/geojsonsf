#ifndef GEOJSONSF_GEOMETRYCOLLECTION_H
#define GEOJSONSF_GEOMETRYCOLLECTION_H

#include <Rcpp.h>
#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/writers/writers.hpp"

template < typename Writer >
void make_gc_type(Writer& writer, Rcpp::List& sfg, std::string& geom_type, Rcpp::CharacterVector& cls);

#endif
