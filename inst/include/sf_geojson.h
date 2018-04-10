#ifndef SFGEOJSON_H
#define SFGEOJSON_H

#include <Rcpp.h>
using namespace Rcpp;


//void add_geometrycollection_to_stream(std::ostringstream& os, Rcpp::List& gc);

void begin_geojson_geometry(std::ostringstream& os, std::string& geom_type);

void begin_geojson_geometry(std::ostringstream& os, Rcpp::List& sfc, std::string& geom_type);

void end_geojson_geometry(std::ostringstream& os, std::string& geom_type);

void add_lonlat_to_stream(std::ostringstream& os, Rcpp::NumericVector& points);

void fetch_coordinates(std::ostringstream& os, Rcpp::List& sfc, int& object_counter);

#endif
