#include <Rcpp.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "geojsonsf.h"
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_properties.h"
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
Rcpp::List rcpp_read_sfc_file(std::string file) {
  return create_sfc(buffer_string(file));
}


// [[Rcpp::export]]
Rcpp::List rcpp_read_sf_file(std::string file) {
  return generic_geojson_to_sf(buffer_string(file));

  //IStreamWrapper isw(ifs);
  //Document d;
  //d.ParseStream(isw);

}

