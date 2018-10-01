#ifndef GEOJSON_TO_SF_H
#define GEOJSON_TO_SF_H

#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes(std::string geom_type);

void parse_geometry_object(Rcpp::List& sfc, int i, const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types,
                           int& sfg_objects);

Rcpp::List parse_geometry_collection_object(const Value& val,
                                            Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types,
                                            int& sfg_objects,
                                            bool& expand_geometries);

Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects,
                                std::set< std::string >& property_keys,
                                Document& doc_properties,
                                std::unordered_map< std::string, std::string>& property_types,
                                bool& expand_geometries,
                                int& nempty);

Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types,
                                           int& sfg_objects,
                                           std::set< std::string >& property_keys,
                                           Document& doc_properties,
                                           std::unordered_map< std::string, std::string>& property_types,
                                           bool& expand_geometries);

void parse_geojson(const Value& v,
                   Rcpp::List& sfc,
                   Rcpp::List& properties,
                   int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types,
                   int& sfg_objects,
                   std::set< std::string >& property_keys,
                   Document& doc_properties,
                   std::unordered_map< std::string, std::string>& property_types,
                   bool& expand_geometries);

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::unordered_map< std::string, std::string>& property_types,
                         bool& expand_geometries);

void parse_geojson_object(Document& d,
                          Rcpp::List& sfc,
                          Rcpp::List& properties,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types,
                          int& sfg_objects,
                          std::set< std::string >& property_keys,
                          Document& doc_properties,
                          std::unordered_map< std::string, std::string>& property_types,
                          bool& expand_geometries);

Rcpp::List geojson_to_sf(const char* geojson, Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::unordered_map< std::string, std::string>& property_types,
                         bool& expand_geometries);

void setup_property_vectors(std::unordered_map< std::string, std::string>& property_types,
                            Rcpp::List& properties, int& sfg_objects);

void fill_property_vectors(Document& doc_properties,
                           std::unordered_map< std::string, std::string>& property_types,
                           Rcpp::List& properties,
                           int& row_index);

Rcpp::List construct_sf(Rcpp::List& lst, std::set< std::string >& property_keys,
                        std::unordered_map< std::string, std::string>& property_types,
                        Document& doc_properties,
                        int& sfg_objects,
                        int& row_index);

Rcpp::List generic_geojson_to_sf(Rcpp::StringVector geojson, bool& expand_geometries);

Rcpp::List create_sfc(Rcpp::StringVector geojson, bool& expand_geometries);

#endif
