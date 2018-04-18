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


// [[Rcpp::export]]
Rcpp::List read_json(std::string file) {

  std::ifstream ifs(file);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  Rcpp::StringVector geojson = buffer.str();

  return generic_geojson_to_sf(geojson);

  //IStreamWrapper isw(ifs);
  //Document d;
  //d.ParseStream(isw);

}
