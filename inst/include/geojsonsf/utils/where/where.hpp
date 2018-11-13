#ifndef GEOJSONSF_UTILS_WHERE_H
#define GEOJSONSF_UTILS_WHERE_H

#include <Rcpp.h>

namespace geojsonsf {
namespace utils {
namespace where {

/*
* find_parameter_index_in_vector
* Finds the location (index) of a string in the list of parameters (as given by the R function call)
*/
inline int where_is(
		Rcpp::String to_find,
		Rcpp::StringVector& sv ) {
	int n = sv.size();
	int i;
	for( i = 0; i < n; i++ ) {
		if ( to_find == sv[i] ) {
			return i;
		}
	}
	return -1;
}

inline Rcpp::IntegerVector where_is(
		Rcpp::StringVector& param_value,
		Rcpp::StringVector& data_names) {

	int n = param_value.size();
	int i;
	Rcpp::IntegerVector res( n );
	for ( i = 0; i < n; i++ ) {
		Rcpp::String to_find = param_value[i];
		res[i] = where_is( to_find, data_names );
	}
	return res;
}

} // namespace where
} // namespace utils
} // namespace spatialwidget

#endif
