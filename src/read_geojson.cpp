#include <Rcpp.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geojson_to_sf.h"
#include "geojsonsf/geojson_sfc.h"
#include "geojsonsf/geojson_sfg.h"
#include "geojsonsf/geojson_properties.h"
#include <fstream>

using namespace Rcpp;
using namespace rapidjson;

Rcpp::StringVector buffer_string(std::string file) {
  std::ifstream ifs(file);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

// [[Rcpp::export]]
Rcpp::List rcpp_read_sfc_file(std::string file, bool flatten_geometries) {
  return create_sfc(buffer_string(file), flatten_geometries);
}


// [[Rcpp::export]]
Rcpp::List rcpp_read_sf_file(std::string file, bool flatten_geometries) {
  return generic_geojson_to_sf(buffer_string(file), flatten_geometries);
}

