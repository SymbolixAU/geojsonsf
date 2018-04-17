
#include "rapidjson/document.h"
#include <Rcpp.h>
#include <sstream>
#include "geojsonsf.h"
using namespace rapidjson;
using namespace Rcpp;



/*
 * Updates a list element to string
 */
void vector_to_string(Rcpp::List& lst, std::string& key) {
  Rcpp::StringVector sv = as<Rcpp::StringVector>(lst[key]);
  lst[key] = sv;
}



void get_property_types(const Value& v, std::map< std::string, std::string>& property_types) {

	// TODO: move to a header??
	static const char* ARRAY_TYPES[] =
		{ "Null", "False", "True", "Object", "Array", "String", "Number" };

  for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter){
    std::string property = iter->name.GetString();

    std::string type = ARRAY_TYPES[iter->value.GetType()];

    // check if key exists
    if (property_types.count(property) == 1) {
      // it exists
      std::string existing_type = property_types[property];

      if (existing_type == "String") {
        // if it's already a 'String' (JSON type), exit

      } else if (existing_type != type) {
        // if it's different, update to be a 'String'
        property_types[property] = "String";

      }
			// if it's not different, exit
    } else {
      // doesn't exist
      property_types[property] = type;

    }
    // if it doesn't exist, add the key / type to the map
  }
}




void get_property_keys(const Value& v, std::set< std::string >& property_keys) {
  for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter){
  property_keys.insert(iter->name.GetString());
  }
}

void update_string_vector(Rcpp::List& sf, std::string& key, const std::string& value, const int& row_index) {
  Rcpp::StringVector sv = sf[key];
  sv[row_index] = value;
  sf[key] = sv;
}

void update_logical_vector(Rcpp::List& sf, std::string& key, const bool& value, const int& row_index) {
  Rcpp::LogicalVector lv = sf[key];
  lv[row_index] = value;
  sf[key] = lv;
}

void update_numeric_vector(Rcpp::List& sf, std::string& key, double& value, const int& row_index) {
  Rcpp::NumericVector nv = sf[key];
  nv[row_index] = value;
  sf[key] = nv;
}

Rcpp::NumericVector na_numeric_vector(const size_t& n_elements) {
  Rcpp::NumericVector nv(n_elements, NA_REAL);
  return nv;
}

Rcpp::StringVector na_string_vector(const size_t& n_elements) {
  Rcpp::StringVector sv(n_elements, Rcpp::StringVector::get_na());
  return sv;
}

Rcpp::LogicalVector na_logical_vector(const size_t& n_elements) {
  Rcpp::LogicalVector lv(n_elements, NA_LOGICAL);
  return lv;
}

