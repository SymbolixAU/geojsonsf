#include <Rcpp.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geojson/geojson_to_sf.hpp"
#include "geojsonsf/sf/sfc/geojson_sfc.hpp"
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_properties.hpp"
#include <fstream>

using namespace rapidjson;

Rcpp::StringVector buffer_string(std::string file) {
  std::ifstream ifs(file);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

// [[Rcpp::export]]
Rcpp::List rcpp_read_sfc_file(std::string file, bool flatten_geometries) {
  return geojsonsf::sf::create_sfc(buffer_string(file), flatten_geometries);
}


// [[Rcpp::export]]
Rcpp::List rcpp_read_sf_file(std::string file, bool flatten_geometries) {
  return geojsonsf::sf::generic_geojson_to_sf(buffer_string(file), flatten_geometries);
}

