#ifndef GEOJSONSF_UTILS_H
#define GEOJSONSF_UTILS_H

#include <Rcpp.h>

namespace geojsonsf {
namespace utils {

  template <int RTYPE>
  inline int sexp_length(Rcpp::Vector<RTYPE> v) {
    return v.length();
  }

  inline int get_sexp_length( SEXP s ) {
    switch( TYPEOF(s) ) {
    case REALSXP:
      return sexp_length< REALSXP >( s );
    case VECSXP:
      return sexp_length< VECSXP >( s );
    case INTSXP:
      return sexp_length< INTSXP >( s );
    default: Rcpp::stop("unknown sf type");
    }
    return 0;
  }

  inline bool is_null_geometry( SEXP& sfg, std::string& geom_type ) {
    int n = get_sexp_length( sfg );
    if( geom_type == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      if (ISNAN( nv[0] ) ) {
        return true;
      }
    } else if ( n == 0 ) {
      return true;
    }
    return false;
  }

  // inline std::string make_dimension( int n ) {
  // 	switch( n ) {
  // 	case 2: {
  // 	  return "XY";
  // 	  break;
  // 	}
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

} // namespace utils
} // namespace geojsonsf

#endif
