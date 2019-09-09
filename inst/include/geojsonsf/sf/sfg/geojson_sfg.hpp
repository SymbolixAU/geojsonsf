#ifndef GEOJSONSF_SFG_H
#define GEOJSONSF_SFG_H


#include <Rcpp.h>
#include "rapidjson/document.h"
#include "geojsonsf/sf/sfc/geojson_sfc.hpp"
#include "geojsonsf/geojson/geojson_validate.hpp"
#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/utils/where/where.hpp"

#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

using namespace rapidjson;

namespace geojsonsf {
namespace sfg {



	inline Rcpp::CharacterVector sfg_attributes( std::string& dimension, std::string& geom_type ) {
		return Rcpp::CharacterVector::create( dimension, geom_type, "sfg" );
	}

	inline double get_lon(const Value& coord_array) {
		geojsonsf::validate::validate_point(coord_array[0]);
		return coord_array[0].GetDouble();
	}

	inline double get_lat(const Value& coord_array) {
		geojsonsf::validate::validate_point(coord_array[1]);
		return coord_array[1].GetDouble();
	}

	// inline std::string make_dimension( int n ) {
	// 	switch( n ) {
	// 	case 2: {
	// 	return "XY";
	// 	break;
	// }
	// 	case 3: {
	// 		return "XYZ";
	// 		break;
	// 	}
	// 	case 4: {
	// 		return "XYZM";
	// 		break;
	// 	}
	// 	default: {
	// 		Rcpp::stop("unknown dimension attribute");
	// 	}
	// 	}
	// 	return "XY"; // never reached
	// }

	inline void get_integer_points(
			const Value& point_array, int& n,
			Rcpp::IntegerVector iv
      ) {
		int i;
		for ( i = 0; i < n; i++ ) {
			iv[i] = point_array[i].GetDouble();
		}
	}

	inline void get_numeric_points(
			const Value& point_array, int& n,
			Rcpp::NumericVector nv,
	    Rcpp::NumericVector& bbox
  ) {
		int i;
		for ( i = 0; i < n; i++ ) {
			geojsonsf::validate::validate_point(point_array[i]);
			nv[i] = point_array[i].GetDouble();
		}
		sfheaders::bbox::calculate_bbox( bbox, nv );
		//geojsonsf::sfc::utils::calculate_bbox(bbox, nv);
	}



	inline void get_points(
			const Value& point_array,
			Rcpp::NumericVector& bbox,
			Rcpp::List& sfc,
			int& i,
			bool requires_attribute,
			std::string attribute
  ) {
		int n = point_array.Size();
		geojsonsf::validate::validate_points(point_array);

		//int r_type;

		// r_type = make_type( point_array );
		//
		// switch ( r_type ) {
		// case INTSXP: {
		// 	Rcpp::IntegerVector iv( n );
		// 	get_integer_points( point_array, n, iv );
		// 	if ( requires_attribute ) {
		// 		iv.attr("class") = sfg_attributes( attribute );
		// 	}
		// 	sfc[i] = iv;
		// 	break;
		// }
		// case REALSXP: {
		Rcpp::NumericVector nv( n );
		get_numeric_points( point_array, n, nv, bbox );

		if ( requires_attribute ) {
			//std::string dim = geojsonsf::utils::make_dimension( n );
			std::string dim = sfheaders::sfg::sfg_dimension( n );
			nv.attr("class") = sfg_attributes( dim, attribute );
		}
		sfc[i] = nv;
		// 	break;
		// }
		// default: {
		// 	Rcpp::stop("unknown coordinate type");
		// }
		// }
	}

	inline void get_line_string(
			const Value& line_array,
			Rcpp::NumericVector& bbox,
			Rcpp::List& sfc,
			int& i,
			bool requires_attribute,
			std::string attribute,
			int& max_cols
  ) {

		int n = line_array.Size();
		//int max_cols = 2;
		int row;

		//int r_type;
		// // TODO( does this take up too much time )?
		// r_type = make_type( line_array );
		//
		// switch ( r_type ) {
		// case INTSXP: {
		// 	Rcpp::IntegerMatrix im( n, 4 );
		// 	for( row = 0; row < n; row++ ) {
		// 		const Value& coord_array = line_array[ row ];
		// 		int n_points = coord_array.Size();
		// 		if( n_points > max_cols ) {
		// 			max_cols = n_points;
		// 		}
		// 		Rcpp::IntegerVector iv( n_points );
		// 		get_integer_points( coord_array, n_points, iv );
		// 		im( row, Rcpp::_ ) = iv;
		// 	}
		// 	im = im( Rcpp::_, Rcpp::Range(0, ( max_cols - 1 ) ) );
		//
		// 	if ( requires_attribute ) {
		// 		im.attr("class") = sfg_attributes( attribute );
		// 	}
		// 	sfc[i] = im;
		// 	break;
		// }
		// case REALSXP: {

		Rcpp::NumericMatrix nm( n, 4 );

		for( row = 0; row < n; row++ ) {
			const Value& coord_array = line_array[ row ];
			int n_points = coord_array.Size();

			if( n_points <= 1 ) {
				Rcpp::stop("mis-specified geometry");
			}

			if( n_points > max_cols ) {
				max_cols = n_points;
			}
			//Rcpp::Rcout << "n_points: " << n_points << std::endl;

			Rcpp::NumericVector nv( 4 );  // initialise with ZM , we remove later
			get_numeric_points( coord_array, n_points, nv, bbox );
			nm( row, Rcpp::_ ) = nv;
		}

		nm = nm( Rcpp::_, Rcpp::Range(0, ( max_cols - 1 ) ) );

		if ( requires_attribute ) {
			std::string dim = sfheaders::sfg::sfg_dimension( max_cols );
			nm.attr("class") = sfg_attributes( dim, attribute );
		}
		sfc[i] = nm;
		//
		// 		break;
		// 	}
		// 	default: {
		// 		Rcpp::stop("unknown coordinate type");
		// 	}
		// 	}

	}

	inline void get_multi_line_string(
			const Value& multi_line_array,
			Rcpp::NumericVector& bbox,
			Rcpp::List& sfc,
			int& i,
			bool requires_attribute,
			std::string attribute
  ) {

		int n = multi_line_array.Size();
		Rcpp::List ml( n );
		int j;
		int max_dimension = 2;
		for ( j = 0; j < n; j++ ) {
			int max_cols = 2;
			geojsonsf::validate::validate_array( multi_line_array[j] );
			get_line_string( multi_line_array[j], bbox, ml, j, false, attribute, max_cols );
			if( max_cols > max_dimension ) {
				max_dimension = max_cols;
			}
		}
		if( requires_attribute ) {
			std::string dim = sfheaders::sfg::sfg_dimension( max_dimension );
			ml.attr("class") = sfg_attributes( dim, attribute );
		}
		sfc[i] = ml;
	}

	inline void get_polygon(
			const Value& polygon_array,
			Rcpp::NumericVector& bbox,
			Rcpp::List& sfc,
			int& i,
			bool requires_attribute,
			std::string attribute
  ) {

		int n = polygon_array.Size();
		Rcpp::List pl( n );
		int j;
		int max_dimension = 2;
		for ( j = 0; j < n; j++ ) {
			int max_cols = 2;
			geojsonsf::validate::validate_array( polygon_array[j] );
			get_line_string( polygon_array[j], bbox, pl, j, false, "", max_cols );
			if ( max_cols > max_dimension ) {
				max_dimension = max_cols;
			}
		}


		if( requires_attribute ) {
			std::string dim = sfheaders::sfg::sfg_dimension( max_dimension );
			pl.attr("class") = sfg_attributes( dim, attribute );
		}
		sfc[i] = pl;
	}

	inline void get_multi_polygon(
			const Value& multi_polygon_array,
			Rcpp::NumericVector& bbox,
			Rcpp::List& sfc,
			int& i,
			bool requires_attribute,
			std::string attribute
  ) {

		int n = multi_polygon_array.Size();
		Rcpp::List mp( n );
		int j, k;
		int max_dimension = 2;

		for ( j = 0; j < n; j++ ) {
			const Value& polygon_array = multi_polygon_array[j];
			geojsonsf::validate::validate_array( polygon_array );
			int np = polygon_array.Size();
			Rcpp::List p( np );

			for ( k = 0; k < np; k++ ) {
				int max_cols = 2;
				geojsonsf::validate::validate_array( polygon_array[k] );
				get_line_string( polygon_array[k], bbox, p, k, false, "", max_cols );
				if( max_cols > max_dimension ) {
					max_dimension = max_cols;
				}
			}
			mp[j] = p;
		}

		if( requires_attribute ) {
			std::string dim = sfheaders::sfg::sfg_dimension( max_dimension );
			mp.attr("class") = sfg_attributes( dim, attribute );
		}
		sfc[i] = mp;
	}

	inline void create_null_sfg(
			Rcpp::List& sfc,
			std::unordered_set< std::string >& geometry_types,
			int& nempty
  ) {
		std::string geom_type;
		std::string dim = "XY";
		if (geometry_types.size() == 0) {
			geom_type = "Point";
		} else {
			geom_type = *geometry_types.begin();
			// the 'set' stores the geometries alphabetically
			// If there are more than one geometries, does it really matter which one is
			// selected?
			// if there is only one type, we want to use that one, so selecting the 'begin'
			// is as good a method as any
		}
		geometry_types.insert(geom_type);
		transform(geom_type.begin(), geom_type.end(), geom_type.begin(), toupper);

		if (geom_type == "POINT" ) {

			Rcpp::NumericVector nullObj(2, NA_REAL);
			nullObj.attr("class") = sfg_attributes(dim, geom_type);
			sfc[0] = nullObj;

		} else if (geom_type == "MULTIPOINT" || geom_type == "LINESTRING") {

			Rcpp::NumericMatrix nullObj;
			nullObj.attr("class") = sfg_attributes(dim, geom_type);
			sfc[0] = nullObj;

		} else {

			Rcpp::List nullObj;
			nullObj.attr("class") = geojsonsf::sfg::sfg_attributes(dim, geom_type);
			sfc[0] = nullObj;
		}
		nempty++;
	}


} // namespace sfg
} // namespace geojsonsf

#endif
