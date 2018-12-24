#ifndef GEOJSONSF_H
#define GEOJSONSF_H

#include <Rcpp.h>

// [[Rcpp::depends(rapidjsonr)]]

namespace geojsonsf {
  const int EPSG = 4326;
  const std::string PROJ4STRING = "+proj=longlat +datum=WGS84 +no_defs";


  template <int RTYPE>
  inline Rcpp::CharacterVector sfClass(Rcpp::Vector<RTYPE> v) {
  	return v.attr("class");
  }

  inline Rcpp::CharacterVector getSfClass(SEXP sf) {

  	switch( TYPEOF(sf) ) {
  	case REALSXP:
  		return sfClass<REALSXP>(sf);
  	case VECSXP:
  		return sfClass<VECSXP>(sf);
  	case INTSXP:
  		return sfClass<INTSXP>(sf);
  	default: Rcpp::stop("unknown sf type");
  	}
  	return "";
  }

  inline void attach_class( Rcpp::StringVector& geojson ) {
  	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
  }
}

#define UNKNOWN            0
#define POINT              1
#define MULTIPOINT         2
#define LINESTRING         3
#define MULTILINESTRING    4
#define POLYGON            5
#define MULTIPOLYGON       6
#define GEOMETRYCOLLECTION 7

#endif
