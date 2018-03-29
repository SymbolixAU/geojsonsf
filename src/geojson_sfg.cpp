// [[Rcpp::depends(rapidjsonr)]]

#include "rapidjson/document.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/writer.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace rapidjson;

Rcpp::CharacterVector sfg_attributes(std::string geom_type) {
	return Rcpp::CharacterVector::create("XY", geom_type, "sfg");
}

// TODO:
// get different types (int, float, ...)
double get_lon(const Value& coord_array) { return coord_array[0].GetDouble(); }
double get_lat(const Value& coord_array) { return coord_array[1].GetDouble(); }

Rcpp::NumericVector get_point(const Value& point_array) {
  Rcpp::NumericVector point(2);
  point[0] = get_lon(point_array);
  point[1] = get_lat(point_array);
  point.attr("class") = sfg_attributes("POINT");
  return point;
}

Rcpp::NumericMatrix get_multi_point(const Value& multi_point_array) {
  size_t n = multi_point_array.Size();
  Rcpp::NumericMatrix multi_point(n, 2);

  for (int i = 0; i < n; i++) {
    multi_point(i, 0) = get_lon(multi_point_array[i]);
    multi_point(i, 1) = get_lat(multi_point_array[i]);
  }
  multi_point.attr("class") = sfg_attributes("MULTIPOINT");
  return multi_point;
}

Rcpp::NumericMatrix get_line_string(const Value& line_array) {
  size_t n = line_array.Size();
  Rcpp::NumericMatrix line(n, 2);

  for (int i = 0; i < n; i++) {
    line(i, 0) = get_lon(line_array[i]);
    line(i, 1) = get_lat(line_array[i]);
  }
  line.attr("class") = sfg_attributes("LINESTRING");
  return line;
}

Rcpp::List get_multi_line_string(const Value& multi_line_array) {
  size_t n = multi_line_array.Size();
  Rcpp::List multi_line(n);

  for (int i = 0; i < n; i++) {
    multi_line[i] = get_line_string(multi_line_array[i]);
  }
  multi_line.attr("class") = sfg_attributes("MULTILINESTRING");
  return multi_line;
}

Rcpp::List get_polygon(const Value& polygon_array) {
  size_t n = polygon_array.Size();
  Rcpp::List polygon(n);
  for (int i = 0; i < n; i++) {
    polygon[i] = get_line_string(polygon_array[i]);
  }
  polygon.attr("class") = sfg_attributes("POLYGON");
  return polygon;
}

Rcpp::List get_multi_polygon(const Value& multi_polygon_array) {
  size_t n = multi_polygon_array.Size();
  Rcpp::List multi_polygon(n);
  for (int i = 0; i < n; i++) {
    multi_polygon[i] = get_polygon(multi_polygon_array[i]);
  }
  multi_polygon.attr("class") = sfg_attributes("MULTIPOLYGON");
  return multi_polygon;
}

void parse_geometry_object(Rcpp::List& sfc, int i, const Value &val) {

	std::string geom_type = val["type"].GetString();
	const Value& coord_array = val["coordinates"];

	if (geom_type == "Point") {
		sfc[i] = get_point(coord_array);

	} else if (geom_type == "MultiPoint") {
		sfc[i] = get_multi_point(coord_array);

	} else if (geom_type == "LineString") {
		sfc[i] = get_line_string(coord_array);

	} else if (geom_type == "MultiLinestring") {
		sfc[i] = get_multi_line_string(coord_array);

	} else if (geom_type == "Polygon") {
		sfc[i] = get_polygon(coord_array);

	} else if (geom_type == "MultiPolygon") {
		sfc[i] = get_multi_polygon(coord_array);

	} else {
		Rcpp::stop("unknown sfg type");
	}

}

Rcpp::List parse_geometry_collection_object(const Value& val) {
	Rcpp::List geom_collection(val.Size());
	std::string geom_type;

	for (int i = 0; i < val.Size(); i++) {
		const Value& gcval = val[i];
		geom_type = gcval["type"].GetString();
		parse_geometry_object(geom_collection, i, gcval);
	}
	geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");
}


void parse_geojson(Document& d, const Value& v, Rcpp::List& sfc, int i) {
  std::string geom_type;

  if (v.HasMember("type") == FALSE) Rcpp::stop("No 'type' member - invalid GeoJSON");

  geom_type = v["type"].GetString();

  if (geom_type == "Feature") {
  	const Value& geom = v["geometry"];
  	//TODO: implement check geometry exists
  	// bool b = geom.HasMember("geometry");
  	parse_geometry_object(sfc, i, geom);

  } else if (geom_type == "FeatureCollection") {
  	// TODO:

  } else if (geom_type == "GeometryCollection") {
  	const Value& gc = v["geometries"];
  	sfc[i] = parse_geometry_collection_object(gc);

  } else {
  	parse_geometry_object(sfc, i, v);
  }
}

void parse_geojson_object(Document& d, Rcpp::List& sfg) {
  const Value& v = d;
  parse_geojson(d, v, sfg, 0);
}

void parse_geojson_array(Document& d, Rcpp::List& sfc, int i) {
  const Value& v = d[i];
  parse_geojson(d, v, sfc, i);
}

Rcpp::List geojson_to_sf(const char* geojson) {

	Document d;
	d.Parse(geojson);
	Rcpp::List sfg(1);

	if (d.IsObject() ) {
		parse_geojson_object(d, sfg);
		return sfg;
	} else if (d.IsArray()) {

		Rcpp::List sfc(d.Size());
		for (int i = 0; i < d.Size(); i++) {
			parse_geojson_array(d, sfc, i);
		}
		return sfc;
	}
	return sfg;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	Rcpp::List lst(n);

	for (int i = 0; i < n; i++ ){
		lst[i] = geojson_to_sf(geojson[i]);
	}
	return lst;
}




