#ifndef GEOJSONSF_SF_GEOJSON_TEST_H
#define GEOJSONSF_SF_GEOJSON_TEST_H

#include <Rcpp.h>

template< typename Writer >
void make_gc_type(Writer& writer, Rcpp::List& sfg,
                  std::string& geom_type, Rcpp::CharacterVector& cls);

#endif
