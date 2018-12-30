
#include "geojsonsf/geojson/geojson_to_sf.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sfc(Rcpp::StringVector geojson, bool& expand_geometries) {
	return geojsonsf::sf::create_sfc(geojson, expand_geometries);
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf( Rcpp::StringVector geojson, bool expand_geometries ) {
	return geojsonsf::sf::generic_geojson_to_sf( geojson, expand_geometries );
}
