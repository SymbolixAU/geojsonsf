
#ifndef GEOJSON_WKT_H
#define GEOJSON_WKT_H

#include "rapidjson/document.h"

void coordSeparateWKT(std::ostringstream& os, int i, int n);

void lineSeparateWKT(std::ostringstream& os, int i, int n);

void polygonSeparateWKT(std::ostringstream& os, int i, int n);

void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat );

void beginWKT(std::ostringstream& os, std::string& geom_type);

void endWKT(std::ostringstream& os, std::string& geom_type);

void point_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_point_to_wkt(std::ostringstream& os, const Value& coord_array);

void line_string_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_line_string_to_wkt(std::ostringstream& os, const Value& coord_array);

void polygon_to_wkt(std::ostringstream& os, const Value& coord_array);

void multi_polygon_to_wkt(std::ostringstream& os, const Value& coord_array);

#endif

