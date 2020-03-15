#ifndef GEOJSONSF_GEOJSON_WRITERS_WRITE_GEOJSON_H
#define GEOJSONSF_GEOJSON_WRITERS_WRITE_GEOJSON_H

#include <Rcpp.h>
#include "geojsonsf/geojson/writers/writers.hpp"
#include "geojsonsf/geometrycollection/geometrycollection.hpp"

namespace geojsonsf {
namespace write_geojson {

	template< typename Writer >
	inline void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type, Rcpp::CharacterVector& cls, int& digits ) {

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
				std::string gc_geom_type;
				bool isnull = false;
				geojsonsf::geometrycollection::gc_type( sfgi, gc_geom_type, isnull, cls );
				if( !isnull ) {
					SEXP sfg_gc = gc[i];
					geojsonsf::writers::begin_geojson_geometry(writer, gc_geom_type);
					write_geojson( writer, sfg_gc, gc_geom_type, cls, digits );
					geojsonsf::writers::end_geojson_geometry(writer, gc_geom_type);
				}
			}
		}
	}


	/*
	 * used for down-casting MULTI objects
	 */
	template< typename Writer >
	inline void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type,
	                          Rcpp::CharacterVector& cls, int geometry_index, int& digits ) {

		if (geom_type == "POINT") {
			geojsonsf::writers::points_to_geojson( writer, sfg, digits );

		} else if (geom_type == "MULTIPOINT") {
			Rcpp::NumericMatrix mls = Rcpp::as< Rcpp::NumericMatrix >( sfg );
			Rcpp::NumericVector pts = mls(geometry_index, Rcpp::_ );
			geojsonsf::writers::points_to_geojson( writer, pts, digits );

		} else if (geom_type == "LINESTRING") {
			geojsonsf::writers::linestring_to_geojson( writer, sfg, digits );

		} else if (geom_type == "MULTILINESTRING") {
			Rcpp::List multiline = Rcpp::as< Rcpp::List >( sfg );
			SEXP ml = multiline[ geometry_index ];
			geojsonsf::writers::linestring_to_geojson( writer, ml, digits );

		} else if (geom_type == "POLYGON") {
			Rcpp::List polygon = Rcpp::as< Rcpp::List >(sfg);
			geojsonsf::writers::polygon_to_geojson( writer, polygon, digits );

		} else if (geom_type == "MULTIPOLYGON") {
			Rcpp::List multipolygon = Rcpp::as< Rcpp::List >( sfg );
			Rcpp::List mlp = multipolygon[ geometry_index ];
			geojsonsf::writers::polygon_to_geojson( writer, mlp, digits );

		} else if (geom_type == "GEOMETRYCOLLECTION") {
			Rcpp::List gc = Rcpp::as< Rcpp::List >( sfg );
			Rcpp::List sfgi(1);
			for (int i = 0; i < gc.size(); i++) {
				sfgi[0] = gc[i];

				std::string gc_geom_type;
				bool isnull = false;
				geojsonsf::geometrycollection::gc_type( sfgi, gc_geom_type, isnull, cls );
				if( !isnull ) {
					SEXP sfg_gc = gc[i];
					geojsonsf::writers::begin_geojson_geometry(writer, gc_geom_type);
					write_geojson( writer, sfg_gc, gc_geom_type, cls, digits );
					geojsonsf::writers::end_geojson_geometry(writer, gc_geom_type);
				}

			}
		}
	}

} // namespace geojsonsf
} // namespace write_geojson

#endif
