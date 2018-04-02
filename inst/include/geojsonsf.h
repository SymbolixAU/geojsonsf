#ifndef GEOJSONSF_H
#define GEOJSONSF_H

// [[Rcpp::depends(rapidjsonr)]]

#include <Rcpp.h>
using namespace Rcpp;

namespace geojsonsf {
  const int EPSG = 4326;
  const std::string PROJ4STRING = "+proj=longlat +datum=WGS84 +no_defs";

  static const char* ARRAY_TYPES[] =
  	{ "Null", "False", "True", "Object", "Array", "String", "Number" };

}



#endif
