#ifndef GEOJSONSF_SFC_UTILS_H
#define GEOJSONSF_SFC_UTILS_H

#include "geojsonsf/geojsonsf.h"

#include "sfheaders/sfheaders.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"

namespace geojsonsf {
namespace sfc {
namespace utils {

	inline Rcpp::List create_null_sfc() {
		Rcpp::List empty_sfc(0);

		std::string type = "GEOMETRY";
		Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
		Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
		Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
		int n_empty = 0;
		std::unordered_set< std::string > geometry_types{"GEOMETRY"};

		int epsg = geojsonsf::EPSG;
		std::string proj = geojsonsf::PROJ4STRING;

		sfheaders::sfc::attach_sfc_attributes(
			empty_sfc, type, geometry_types, bbox, z_range, m_range,
			epsg, proj, n_empty
			);
		return empty_sfc;
	}

	inline void fetch_geometries(
			Rcpp::List& sf,
			Rcpp::List& res,
			R_xlen_t& sfg_counter
  ) {

		std::string geom_attr;

		for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {

			switch( TYPEOF(*it) ) {

			case VECSXP: {
				Rcpp::List tmp = Rcpp::as< Rcpp::List >( *it );
				if(Rf_isNull(tmp.attr("class"))) {
					fetch_geometries(tmp, res, sfg_counter);
				} else {
					res[sfg_counter] = tmp;
					sfg_counter++;
				}
				break;
			}
			case REALSXP: {
				Rcpp::NumericVector tmp = Rcpp::as< Rcpp::NumericVector >( *it );
				if(Rf_isNull(tmp.attr("class"))) {
					Rcpp::stop("Geometry could not be determined");
				} else {
					res[sfg_counter] = tmp;
					sfg_counter++;
				}
				break;
			}
			case INTSXP: {
				Rcpp::IntegerVector tmp = Rcpp::as< Rcpp::IntegerVector >( *it );
				if(Rf_isNull( tmp.attr( "class" ) ) ){
					Rcpp::stop("Geometry could not be determined");
				} else {
					res[sfg_counter] = tmp;
					sfg_counter++;
				}
				break;
			}
			case STRSXP: {
				Rcpp::StringVector tmp = Rcpp::as< Rcpp::StringVector >( *it );
				if(Rf_isNull( tmp.attr( "class" ) ) ) {
					Rcpp::stop("Geometry could not be determined");
				} else {
					res[sfg_counter] = tmp;
					sfg_counter++;
				}
				break;
			}
			default: {
				res[0] = create_null_sfc();
				//Rcpp::stop("Geometry could not be determined");
			}
			}
		}
	}

} // namespace utils
} // namespace sfc
} // namespace geojsonsf

#endif
