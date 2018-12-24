
#include <Rcpp.h>
#include "geojsonsf/geojson/api/df_api.hpp"


// [[Rcpp::export]]
Rcpp::StringVector rcpp_df_to_geojson_atomise(
		Rcpp::DataFrame& df,
		Rcpp::StringVector& geometry_columns,
		int& digits) {

	return geojsonsf::api::df_to_geojson_atomise( df, geometry_columns, digits );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_df_to_geojson(
		Rcpp::DataFrame& df,
		Rcpp::StringVector& geometry_columns,
		int& digits ) {

	return geojsonsf::api::df_to_geojson( df, geometry_columns, digits );
}
