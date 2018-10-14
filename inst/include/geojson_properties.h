#ifndef GEOJSONSF_PROPERTIES_H
#define GEOJSONSF_PROPERTIES_H

#include "rapidjson/document.h"
#include <Rcpp.h>
using namespace rapidjson;
using namespace Rcpp;

void vector_to_string(Rcpp::List& lst, std::string& key);

//template <typename T>
//std::string any_to_string(const T& obj);

template <typename T>
std::string any_to_string(const T& obj) {
	std::stringstream ss;
	ss << obj;
	return ss.str();
}

void sort_property_names( Rcpp::List& properties, std::unordered_set< std::string >& property_keys);

void get_property_types(const Value& v, std::unordered_map< std::string, std::string>& property_types);

void get_property_keys(const Value& v, std::unordered_set< std::string >& property_keys);

void update_string_vector(Rcpp::List& sf, std::string& key, const std::string& value, const int& row_index);

void update_logical_vector(Rcpp::List& sf, std::string& key, const bool& value, const int& row_index);

void update_numeric_vector(Rcpp::List& sf, std::string& key, double& value, const int& row_index);

Rcpp::NumericVector na_numeric_vector(const size_t& n_elements);

Rcpp::StringVector na_string_vector(const size_t& n_elements);

Rcpp::LogicalVector na_logical_vector(const size_t& n_elements);

#endif


