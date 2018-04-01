
#include "rapidjson/document.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace rapidjson;

void geojson_object_error(std::string key, int sfg_number) {
	std::string err = "No '" + key + "' member at object index " + std::to_string(sfg_number) + " - invalid GeoJSON";
	Rcpp::stop(err);
}

void validate_type(const Value& v, int& sfg_objects) {
	if (v.HasMember("type") == FALSE) {
		geojson_object_error("type", sfg_objects);
	}
}

void validate_features(const Value& v, int& sfg_objects) {
	if (v.HasMember("features") == FALSE) {
		geojson_object_error("features", sfg_objects);
	}
}

void validate_feature(const Value& v, int& sfg_objects) {
	if (v.HasMember("feature") == FALSE) {
		geojson_object_error("feature", sfg_objects);
	}
}

void validate_properties(const Value& v, int& sfg_objects) {
	if (v.HasMember("properties") == FALSE) {
		geojson_object_error("properties", sfg_objects);
	}
}

void validate_geometry(const Value& v, int& sfg_objects) {
	if (v.HasMember("geometry") == FALSE) {
		geojson_object_error("geometry", sfg_objects);
	}
}


