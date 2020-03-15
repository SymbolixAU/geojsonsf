#ifndef GEOJSONSF_SFC_H
#define GEOJSONSF_SFC_H

#include <Rcpp.h>
//#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/sf/sfc/utils/sfc_utils.hpp"

namespace geojsonsf {
namespace sfc {

	inline Rcpp::List construct_sfc(int& sfg_objects,
	                         Rcpp::List& sf,
	                         Rcpp::NumericVector& bbox,
	                         std::unordered_set< std::string >& geometry_types,
	                         int& nempty) {

		Rcpp::List sfc_output( sfg_objects );
		std::string geom_attr;

		int sfg_counter = 0;

		geojsonsf::sfc::utils::fetch_geometries( sf, sfc_output, sfg_counter );
		geojsonsf::sfc::utils::attach_sfc_attributes( sfc_output, geom_attr, bbox, geometry_types, nempty );

		return sfc_output;
	}

} // namespace sfc
} // namespace geojsonsf

#endif
