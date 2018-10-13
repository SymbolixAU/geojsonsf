#include "rapidjson/document.h"

#include <Rcpp.h>
#include "geojson_sfg.h"
#include "geojson_sfc.h"
#include "geojson_validate.h"

using namespace Rcpp;
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes( std::string& dimension, std::string& geom_type ) {
  return Rcpp::CharacterVector::create( dimension, geom_type, "sfg" );
}

double get_lon(const Value& coord_array) {
	validate_point(coord_array[0]);
	return coord_array[0].GetDouble();
}

double get_lat(const Value& coord_array) {
	validate_point(coord_array[1]);
	return coord_array[1].GetDouble();
}

// TODO( this will iterate along a long LINESTRING... )
// int make_type( const Value& coord_array ) {
// 	int n = coord_array.Size();
// 	int i;
//   //const Value& v = coord_array[ elem ];
//   for ( i = 0; i < n; i++ ) {
//   	if( coord_array[i].IsDouble() ) {
//   		return REALSXP;
//   	}
//   }
//   return INTSXP;

	// if( v.IsInt()  || v.IsUint() || v.IsUint64() || v.IsInt64() ) {
	// 	*r_type = INTSXP;
	// } else if ( v.IsDouble() ) {
	// 	*r_type = REALSXP;
	// } else {
	// 	Rcpp::stop("Unknown coordinate type");
	// }
// }



// Rcpp::NumericVector parse_point(const Value& coord_array, Rcpp::NumericVector& bbox) {
// 	validate_points(coord_array);
//   Rcpp::NumericVector point(2);
//   point[0] = get_lon(coord_array);
//   point[1] = get_lat(coord_array);
//   calculate_bbox(bbox, point);
//   return point;
// }
//
// Rcpp::NumericVector get_point(const Value& point_array, Rcpp::NumericVector& bbox) {
//   Rcpp::NumericVector point = parse_point(point_array, bbox);
//   return point;
// }

std::string make_dimension( int n ) {
	switch( n ) {
	case 2: {
	return "XY";
	break;
}
	case 3: {
		return "XYZ";
		break;
	}
	case 4: {
		return "XYZM";
		break;
	}
	default: {
		Rcpp::stop("unknown dimension attribute");
	}
	}
	return "XY"; // never reached
}

void get_integer_points( const Value& point_array, int& n, Rcpp::IntegerVector iv ) {
	int i;
	for ( i = 0; i < n; i++ ) {
		iv[i] = point_array[i].GetDouble();
	}
}

void get_numeric_points( const Value& point_array, int& n, Rcpp::NumericVector nv,
                         Rcpp::NumericVector& bbox ) {
	int i;
	for ( i = 0; i < n; i++ ) {
		nv[i] = point_array[i].GetDouble();
	}
	calculate_bbox(bbox, nv);
}



void get_points( const Value& point_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                bool requires_attribute, std::string attribute ) {
	int n = point_array.Size();

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
		  std::string dim = make_dimension( n );
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

// Rcpp::NumericMatrix parse_line(const Value& coord_array, Rcpp::NumericVector& bbox) {
//   size_t n = coord_array.Size();
//   Rcpp::NumericMatrix line_string(n, 2);
//   unsigned int i;
//   for (i = 0; i < n; i++) {
//     validate_array(coord_array[i]);
//     line_string(i, _) = parse_point(coord_array[i], bbox);
//   }
//   return line_string;
// }
//
//
// Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array, Rcpp::NumericVector& bbox) {
//   Rcpp::NumericMatrix multi_point = parse_line(multi_point_array, bbox);
//   return multi_point;
// }

void get_line_string( const Value& line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                      bool requires_attribute, std::string attribute, int& max_cols ) {
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
 			// Rcpp::Rcout << "linestring n_points: " << n_points << std::endl;
 			// Rcpp::Rcout << "linestring max_cols: " << max_cols << std::endl;
			if( n_points > max_cols ) {
				max_cols = n_points;
			}
 			Rcpp::NumericVector nv( 4 );  // initialise with ZM , we remove later
			//Rcpp::Rcout << "n_points: " << n_points << std::endl;
 			get_numeric_points( coord_array, n_points, nv, bbox );
 			nm( row, Rcpp::_ ) = nv;
 		}

    nm = nm( Rcpp::_, Rcpp::Range(0, ( max_cols - 1 ) ) );

		//Rcpp::Rcout << "nm: " << nm << std::endl;

		if ( requires_attribute ) {
		  std::string dim = make_dimension( max_cols );
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

// Rcpp::NumericMatrix get_line_string(const Value& line_array, Rcpp::NumericVector& bbox) {
//   Rcpp::NumericMatrix line_string = parse_line(line_array, bbox);
//   return line_string;
// }

// TODO( overload the 'get_() functions with SEXP, Numeric and Int )





void get_multi_line_string( const Value& multi_line_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                           bool requires_attribute, std::string attribute ) {
	int n = multi_line_array.Size();
	Rcpp::List ml( n );
	int j;
	int max_dimension = 2;
	for ( j = 0; j < n; j++ ) {
		int max_cols = 2;
		validate_array( multi_line_array[j] );
		//const Value& line_array = multi_line_array[j];
		get_line_string( multi_line_array[j], bbox, ml, j, false, attribute, max_cols );
		if( max_cols > max_dimension ) {
			// Rcpp::Rcout << "max_cols: " << max_cols << std::endl;
			// Rcpp::Rcout << "max_dimension: " << max_dimension << std::endl;
			max_dimension = max_cols;
		}
	}
	if( requires_attribute ) {
		//Rcpp::Rcout << "multi linestring dim: " << max_dimension << std::endl;
		std::string dim = make_dimension( max_dimension );
	  ml.attr("class") = sfg_attributes( dim, attribute );
	}
	//Rcpp::List lst(1);
	//lst[0] = ml;
	//sfc[i] = lst;
	sfc[i] = ml;
}



// Rcpp::List get_multi_line_string(const Value& multi_line_array, Rcpp::NumericVector& bbox) {
//   size_t n = multi_line_array.Size();
//   Rcpp::List multi_line(n);
//   unsigned int i;
//
//   for (i = 0; i < n; i++) {
//     validate_array(multi_line_array[i]);
//     multi_line[i] = parse_line(multi_line_array[i], bbox);
//   }
//   return multi_line;
// }

void get_polygon( const Value& polygon_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                  bool requires_attribute, std::string attribute ) {

	int n = polygon_array.Size();
	Rcpp::List pl( n );
	int j;
	int max_dimension = 2;
	for ( j = 0; j < n; j++ ) {
		int max_cols = 2;
	 	validate_array( polygon_array[j] );
		//Rcpp::Rcout << "polygon size n: " << n << std::endl;
	 	get_line_string( polygon_array[j], bbox, pl, j, false, "", max_cols );
	 	if ( max_cols > max_dimension ) {
	 		max_dimension = max_cols;
	 	}
	}


	if( requires_attribute ) {
		std::string dim = make_dimension( max_dimension );
		pl.attr("class") = sfg_attributes( dim, attribute );
	}
	//Rcpp::List lst(1);
	//lst[0] = pl;
	//sfc[i] = lst;
	sfc[i] = pl;
}



//
// Rcpp::List get_polygon(const Value& polygon_array, Rcpp::NumericVector& bbox) {
//   size_t n = polygon_array.Size();
//   Rcpp::List polygon(n);
//   unsigned int i;
//
//   for (i = 0; i < n; i++) {
//     validate_array(polygon_array[i]);
//     polygon[i] = parse_line(polygon_array[i], bbox);
//   }
//   return polygon;
// }

void get_multi_polygon( const Value& multi_polygon_array, Rcpp::NumericVector& bbox, Rcpp::List& sfc, int& i,
                        bool requires_attribute, std::string attribute ) {
	int n = multi_polygon_array.Size();
	Rcpp::List mp( n );
	int j, k;
	int max_dimension = 2;
	for ( j = 0; j < n; j++ ) {
		const Value& polygon_array = multi_polygon_array[j];
		validate_array( polygon_array );
		int np = polygon_array.Size();
		Rcpp::List p( np );

		for ( k = 0; k < np; k++ ) {
			int max_cols = 2;
			Rcpp::Rcout << "multi polygon max_cols " << max_cols << std::endl;
			Rcpp::Rcout << "multi polygon max_dimension " << max_dimension << std::endl;
			validate_array( polygon_array[k] );
			//Rcpp::Rcout << "k: " << k << ", np: " << np <<  std::endl;
			//const Value& v = polygon_array[k];
			get_line_string( polygon_array[k], bbox, p, k, false, "", max_cols );
			if( max_cols > max_dimension ) {
				max_dimension = max_cols;
			}
			//get_polygon( polygon_array[k], bbox, p, k, false, "");
		}
		mp[j] = p;
	}

	if( requires_attribute ) {
		std::string dim = make_dimension( max_dimension );
		mp.attr("class") = sfg_attributes( dim, attribute );
	}
	//Rcpp::List lst(1);
	// lst[0] = mp;
	// sfc[i] = lst;
	sfc[i] = mp;
}



// Rcpp::List get_multi_polygon(const Value& multi_polygon_array, Rcpp::NumericVector& bbox) {
//   size_t n = multi_polygon_array.Size();
//   Rcpp::List multi_polygon(n);
//   unsigned int i;
//   unsigned int j;
//
//   for (i = 0; i < n; i++) {
//     validate_array(multi_polygon_array[i]);
//     size_t np = multi_polygon_array[i].Size();
//     Rcpp::List polygon(np);
//     const Value& polygon_array = multi_polygon_array[i];
//
//     for (j = 0; j < np; j++) {
//       validate_array(polygon_array[j]);
//       polygon[j] = parse_line(polygon_array[j], bbox);
//     }
//     multi_polygon[i] = polygon;
//   }
//   return multi_polygon;
// }


