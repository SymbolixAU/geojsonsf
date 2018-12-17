#ifndef GEOJSONSF_GEOMETRYCOLLECTION_H
#define GEOJSONSF_GEOMETRYCOLLECTION_H

#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/writers/writers.hpp"


template< typename Writer >
inline void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type, Rcpp::CharacterVector& cls, int& digits );

#include "geojsonsf/geometrycollection/geometrycollection.hpp"

template< typename Writer >
inline void make_gc_type(Writer& writer, Rcpp::List& sfg,
                         std::string& geom_type, Rcpp::CharacterVector& cls, int& digits) {

	bool isnull = false;

	for (Rcpp::List::iterator it = sfg.begin(); it != sfg.end(); it++) {

		switch( TYPEOF( *it ) ) {
		case VECSXP: {
			Rcpp::List tmp = Rcpp::as< Rcpp::List >(*it);
			if (!Rf_isNull(tmp.attr("class"))) {

				cls = tmp.attr("class");
				// TODO: error handle (there should aways be 3 elements as we're workgin wtih sfg objects)
				geom_type = cls[1];

				SEXP tst = *it;
				isnull = geojsonsf::utils::is_null_geometry( tst, geom_type );
				if ( isnull ) {
					//writer.Null();
				} else {
					geojsonsf::writers::begin_geojson_geometry(writer, geom_type);
					write_geojson(writer, tmp, geom_type, cls, digits);
					geojsonsf::writers::end_geojson_geometry(writer, geom_type);
				}
			} else {
				make_gc_type(writer, tmp, geom_type, cls, digits);
			}
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = Rcpp::as< Rcpp::NumericVector >( *it );
			if (!Rf_isNull(tmp.attr("class"))) {

				cls = tmp.attr("class");
				geom_type = cls[1];

				SEXP tst = *it;
				isnull = geojsonsf::utils::is_null_geometry( tst, geom_type );
				if ( isnull ) {
					//writer.Null();
				} else {
					geojsonsf::writers::begin_geojson_geometry(writer, geom_type);
					write_geojson(writer, tmp, geom_type, cls, digits);
					geojsonsf::writers::end_geojson_geometry(writer, geom_type);
				}
			}
			break;
		}
		default: {
			Rcpp::stop("Coordinates could not be found");
		}
		}
	}
}

#endif
