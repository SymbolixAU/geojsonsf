#ifndef GEOJSONSF_WRITE_GEOJSON_H
#define GEOJSONSF_WRITE_GEOJSON_H

#include <Rcpp.h>
#include "geojsonsf/writers/writers.hpp"

template< typename Writer >
inline void make_gc_type(Writer& writer, Rcpp::List& sfg,
                         std::string& geom_type, Rcpp::CharacterVector& cls, int& digits);

#include "geojsonsf/geometrycollection/geometrycollection.hpp"

template< typename Writer >
void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type, Rcpp::CharacterVector& cls, int& digits ) {

	if (geom_type == "POINT") {
		geojsonsf::writers::points_to_geojson( writer, sfg, digits );

	} else if (geom_type == "MULTIPOINT") {
		geojsonsf::writers::linestring_to_geojson( writer, sfg, digits );

	} else if (geom_type == "LINESTRING") {
		geojsonsf::writers::linestring_to_geojson( writer, sfg, digits );

	} else if (geom_type == "MULTILINESTRING") {
		Rcpp::List multiline = Rcpp::as< Rcpp::List >( sfg );
		geojsonsf::writers::polygon_to_geojson( writer, multiline, digits );

	} else if (geom_type == "POLYGON") {
		Rcpp::List polygon = Rcpp::as< Rcpp::List >(sfg);
		geojsonsf::writers::polygon_to_geojson( writer, polygon, digits );

	} else if (geom_type == "MULTIPOLYGON") {
		Rcpp::List multipolygon = Rcpp::as< Rcpp::List >( sfg );
		geojsonsf::writers::multi_polygon_to_geojson( writer, multipolygon, digits );

	} else if (geom_type == "GEOMETRYCOLLECTION") {
		Rcpp::List gc = Rcpp::as< Rcpp::List >( sfg );
		Rcpp::List sfgi(1);
		for (int i = 0; i < gc.size(); i++) {
			sfgi[0] = gc[i];
			make_gc_type(writer, sfgi, geom_type, cls, digits);
		}
	}
}


/*
 * used for down-casting MULTI objects
 */
template< typename Writer >
void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type,
                   Rcpp::CharacterVector& cls, int geometry, int& digits ) {

	if (geom_type == "POINT") {
		geojsonsf::writers::points_to_geojson( writer, sfg, digits );

	} else if (geom_type == "MULTIPOINT") {
		Rcpp::NumericMatrix mls = Rcpp::as< Rcpp::NumericMatrix >( sfg );
		Rcpp::NumericVector pts = mls(geometry, Rcpp::_ );
		geojsonsf::writers::points_to_geojson( writer, pts, digits );

	} else if (geom_type == "LINESTRING") {
		geojsonsf::writers::linestring_to_geojson( writer, sfg, digits );

	} else if (geom_type == "MULTILINESTRING") {
		Rcpp::List multiline = Rcpp::as< Rcpp::List >( sfg );
		SEXP ml = multiline[ geometry ];
		geojsonsf::writers::linestring_to_geojson( writer, ml, digits );

	} else if (geom_type == "POLYGON") {
		Rcpp::List polygon = Rcpp::as< Rcpp::List >(sfg);
		geojsonsf::writers::polygon_to_geojson( writer, polygon, digits );

	} else if (geom_type == "MULTIPOLYGON") {
		Rcpp::List multipolygon = Rcpp::as< Rcpp::List >( sfg );
		Rcpp::List mlp = multipolygon[ geometry ];
		geojsonsf::writers::polygon_to_geojson( writer, mlp, digits );

	} else if (geom_type == "GEOMETRYCOLLECTION") {
		Rcpp::List gc = Rcpp::as< Rcpp::List >( sfg );
		Rcpp::List sfgi(1);
		for (int i = 0; i < gc.size(); i++) {
			sfgi[0] = gc[i];
			make_gc_type(writer, sfgi, geom_type, cls, digits);
		}
	}
}


#endif
