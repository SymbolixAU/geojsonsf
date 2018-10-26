#ifndef GEOJSON_TO_SF_H
#define GEOJSON_TO_SF_H

#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes( std::string& dimension, std::string& geom_type );

void setup_property_vectors(std::unordered_map< std::string, std::string>& property_types,
                            Rcpp::List& properties, int& sfg_objects);

void fill_property_vectors(Document& doc_properties,
                           std::unordered_map< std::string, std::string>& property_types,
                           Rcpp::List& properties,
                           int& row_index);

Rcpp::List construct_sf(Rcpp::List& lst, std::unordered_set< std::string >& property_keys,
                        std::unordered_map< std::string, std::string>& property_types,
                        Document& doc_properties,
                        int& sfg_objects,
                        int& row_index);

Rcpp::List generic_geojson_to_sf(Rcpp::StringVector geojson, bool& expand_geometries);

Rcpp::List create_sfc(Rcpp::StringVector geojson, bool& expand_geometries);

#endif
