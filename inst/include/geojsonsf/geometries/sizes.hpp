#ifndef GEOJSONSF_GEOMETRY_SIZES_H
#define GEOJSONSF_GEOMETRY_SIZES_H

#include <Rcpp.h>

namespace geojsonsf {
namespace sizes {

  // determines the size of teh geometry for MULTI objects
  // MULTIPOINT - number of points (vector size)
  // MULTILINESTRING - number of lines ( matrix rows )
  // MULTIPOLYGON - number of polygons ( list size? )
  int geometry_size(SEXP& sfg, std::string& geom_type, Rcpp::CharacterVector& cls) {

  	if (geom_type == "MULTIPOINT") {
  		Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
  		return mat.nrow();

  	} else if (geom_type == "MULTILINESTRING") {
  		Rcpp::List multiline = Rcpp::as< Rcpp::List >( sfg );
  		return multiline.size();

  	} else if (geom_type == "MULTIPOLYGON") {
  		Rcpp::List multipolygon = Rcpp::as< Rcpp::List >( sfg );
  		// int multiplier = 1;
  		// for ( int i = 0; i < multipolygon.size(); i++ ) {
  		// 	Rcpp::List poly = multipolygon[i];
  		// 	multiplier = multiplier + poly.size();
  		// }

  		// int multiplier = 1;
  		// for( int i = 0; i < multipolygon.size(); i++ ) {
  		// 	Rcpp::List poly = multipolygon[ i ];
  		// 	multiplier = multiplier + poly.size();
  		// }
  		// Rcpp::Rcout << "multiplier: " << multiplier << std::endl;
  		//Rcpp::List poly = multipolygon[0];
  		return multipolygon.size();
  	}

  	// } else if (geom_type == "GEOMETRYCOLLECTION") {
  	// 	Rcpp::List gc = Rcpp::as< Rcpp::List >( sfg );
  	// 	Rcpp::List sfgi(1);
  	// 	for (int i = 0; i < gc.size(); i++) {
  	// 		sfgi[0] = gc[i];
  	// 		//make_gc_type(writer, sfgi, geom_type, cls);
  	// 	}
  	// }
  	return 1;
  }

} // namespace sizes
} //namespace geojsonsf


#endif
