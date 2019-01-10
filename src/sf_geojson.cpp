
#include <Rcpp.h>
#include "geojsonsf/geojson/api/sf_api.hpp"

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sfc_to_geojson( Rcpp::List& sfc, int& digits ) {
	return geojsonsf::api::sfc_to_geojson( sfc, digits );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_atomise( Rcpp::DataFrame& sf, int& digits, bool& factors_as_string ) {
	return geojsonsf::api::sf_to_geojson_atomise( sf, digits, factors_as_string );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson( Rcpp::DataFrame& sf, int& digits, bool& factors_as_string ) {
	return geojsonsf::api::sf_to_geojson( sf, digits, factors_as_string );
}
