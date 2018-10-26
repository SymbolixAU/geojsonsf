
#ifndef GEOJSONSF_WKT_H
#define GEOJSONSF_WKT_H

#include "rapidjson/document.h"
using namespace rapidjson;

void coord_separator(std::ostringstream& os, int i, int n);

void begin_wkt(std::ostringstream& os, std::string& geom_type);

void end_wkt(std::ostringstream& os, std::string& geom_type);

void point_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_point_to_wkt(std::ostringstream& os, const Value& coord_array);

void line_string_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_line_string_to_wkt(std::ostringstream& os, const Value& coord_array);

void polygon_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_polygon_to_wkt(std::ostringstream& os, const Value& coord_array);

#endif

