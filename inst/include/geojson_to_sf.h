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

Rcpp::List parse_geometry_collection_object(const Value& val, Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types,
                                            int& sfg_objects);

Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects,
                                std::set< std::string >& property_keys,
                                Document& doc_properties,
                                std::map< std::string, std::string>& property_types);

Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types,
                                           int& sfg_objects,
                                           std::set< std::string >& property_keys,
                                           Document& doc_properties,
                                           std::map< std::string, std::string>& property_types);

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::map< std::string, std::string>& property_types);

void parse_geojson_object(Document& d,
                          Rcpp::List& sfc,
                          Rcpp::List& properties,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types,
                          int& sfg_objects,
                          std::set< std::string >& property_keys,
                          Document& doc_properties,
                          std::map< std::string, std::string>& property_types);

void parse_geojson(const Value& v,
                   Rcpp::List& sfc,
                   Rcpp::List& properties,
                   int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types,
                   int& sfg_objects,
                   std::set< std::string >& property_keys,
                   Document& doc_properties,
                   std::map< std::string, std::string>& property_types);

Rcpp::List geojson_to_sf(const char* geojson, Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::map< std::string, std::string>& property_types);

#endif
