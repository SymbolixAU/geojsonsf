#include <Rcpp.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <rapidjson/filereadstream.h>

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

Rcpp::List rcpp_read_sf_file_stream( std::string file, bool flatten_geometries ) {

  FILE* fp = fopen(file, "rb"); // TODO - windows uses "r"
  char readBuffer[65536];
  FileReadStream is(fp, readBuffer, sizeof(readBuffer));

  Document d;
  d.ParseStream(is);

  fclose(fp);
  return geojsonsf::sf::generic_geojson_to_sf( d, flatten_geometries );
}

// [[Rcpp::export]]
Rcpp::List rcpp_read_sfc_file(std::string file, bool flatten_geometries) {
  return geojsonsf::sf::create_sfc(buffer_string(file), flatten_geometries);
}


// [[Rcpp::export]]
Rcpp::List rcpp_read_sf_file(std::string file, bool flatten_geometries) {
  return geojsonsf::sf::generic_geojson_to_sf(buffer_string(file), flatten_geometries);
}

