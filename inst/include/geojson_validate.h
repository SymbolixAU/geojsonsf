
#ifndef GEOJSONSF_VALIDATE_H
#define GEOJSONSF_VALIDATE_H

#include "rapidjson/document.h"

using namespace rapidjson;

void safe_parse(Document& d, const char* geojson);

void validate_type(const Value& v, int& sfg_objects);

void validate_array(const Value& v);

void validate_array(const Value& v, int& sfg_objects);

void validate_features(const Value& v, int& sfg_objects);

void validate_feature(const Value& v, int& sfg_objects);

void validate_properties(const Value& v, int& sfg_objects);

void validate_geometry(const Value& v, int& sfg_objects);

void validate_geometries(const Value& v, int& sfg_objects);

void validate_coordinates(const Value& v, int& sfg_objects);

#endif
