#ifndef GEOJSONSF_H
#define GEOJSONSF_H

#include <Rcpp.h>

// [[Rcpp::depends(rapidjsonr)]]

namespace geojsonsf {
  const int EPSG = 4326;
  const std::string PROJ4STRING = "+proj=longlat +datum=WGS84 +no_defs";
}

template <int RTYPE>
Rcpp::CharacterVector sfClass(Rcpp::Vector<RTYPE> v);

Rcpp::CharacterVector getSfClass(SEXP sf);

#define UNKNOWN            0
#define POINT              1
#define MULTIPOINT         2
#define LINESTRING         3
#define MULTILINESTRING    4
#define POLYGON            5
#define MULTIPOLYGON       6
#define GEOMETRYCOLLECTION 7

#endif
