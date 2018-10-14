
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_to_sf.h"
#include "geojson_validate.h"
#include "geojson_properties.h"
#include "geojson_wkt.h"

using namespace rapidjson;
using namespace Rcpp;

void parse_geometry_object_wkt(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           std::unordered_set< std::string >& geometry_types,
                           int& wkt_objects) {

  validate_type(geometry, wkt_objects);
  validate_coordinates(geometry, wkt_objects);
  validate_array(geometry["coordinates"], wkt_objects);

  std::string geom_type = geometry["type"].GetString();
  const Value& coord_array = geometry["coordinates"];
  geometry_types.insert(geom_type);

	std::ostringstream os;
	Rcpp::StringVector wkt;
	begin_wkt(os, geom_type);

  if (geom_type == "Point") {
    point_to_wkt(os, coord_array);

  } else if (geom_type == "MultiPoint") {
    multi_point_to_wkt(os, coord_array);

  } else if (geom_type == "LineString") {
    line_string_to_wkt(os, coord_array);

  } else if (geom_type == "MultiLineString") {
    multi_line_string_to_wkt(os, coord_array);

  } else if (geom_type == "Polygon") {
    polygon_to_wkt(os, coord_array);

  } else if (geom_type == "MultiPolygon") {
    multi_polygon_to_wkt(os, coord_array);

  } else {
    Rcpp::stop("unknown sfg type");
  }

	end_wkt(os, geom_type);

  wkt = os.str();
  transform(geom_type.begin(), geom_type.end(), geom_type.begin(), ::toupper);

  // TODO( dimension )
  std::string dim = "XY";

  wkt.attr("class") = sfg_attributes(dim, geom_type);
  sfc[i] = wkt;
}


Rcpp::List parse_geometry_collection_object_wkt(const Value& val,
                                            std::unordered_set< std::string >& geometry_types,
                                            int& wkt_objects) {

  std::string geom_type;

  validate_geometries(val, wkt_objects);
  auto geometries = val["geometries"].GetArray();
  unsigned int n = geometries.Size();
  unsigned int i;

  Rcpp::List geom_collection(n);
  Rcpp::List geom_collection_wkt(1);

  for (i = 0; i < n; i++) {
    const Value& gcval = geometries[i];
    validate_type(gcval, wkt_objects);
    geom_type = gcval["type"].GetString();
    parse_geometry_object_wkt(geom_collection, i, gcval, geometry_types, wkt_objects);
  }

  // collapse into a single WKT string
  std::ostringstream os;
  os << "GEOMETRYCOLLECTION (";
  for (i = 0; i < n; i++) {
    std::string g = geom_collection[i];
    os << g;
    coord_separator(os, i, n);
  }
  os << ")";

  geom_collection_wkt = os.str();
  // TODO( dimension );
  std::string dim = "XY";
  std::string attribute = "GEOMETRYCOLLECTION";
  geom_collection_wkt.attr("class") = sfg_attributes( dim, attribute );
  return geom_collection_wkt;
}


Rcpp::List parse_feature_object_wkt(const Value& feature,
                                std::unordered_set< std::string >& geometry_types,
                                int& wkt_objects,
                                std::unordered_set< std::string >& property_keys,
                                Document& doc_properties,
                                std::unordered_map< std::string, std::string>& property_types) {

  validate_geometry(feature, wkt_objects);
  validate_properties(feature, wkt_objects);

  const Value& geometry = feature["geometry"];

  Rcpp::List sfc(1);

  if (geometry.Size() > 0) {
  	validate_type(geometry, wkt_objects);
  	std::string geom_type = geometry["type"].GetString();

  	if (geom_type == "GeometryCollection") {
  		Rcpp::List gc = parse_geometry_collection_object_wkt(geometry, geometry_types, wkt_objects);
  		sfc[0] = gc;
  	} else {
  		parse_geometry_object_wkt(sfc, 0, geometry, geometry_types, wkt_objects);
  	}

  } else {
  	Rcpp::StringVector wkt = "POINT EMPTY";
  	std::string dim = "XY";
  	std::string attribute = "POINT";
  	wkt.attr("class") = sfg_attributes( dim, attribute );
  	sfc[0] = wkt;
  }

  wkt_objects++;
  // get property keys
  const Value& p = feature["properties"];
  get_property_keys(p, property_keys);
  get_property_types(p, property_types);

  //https://stackoverflow.com/a/33473321/5977215
  std::string s = std::to_string(wkt_objects);
  Value n(s.c_str(), doc_properties.GetAllocator());

  // TODO: is this method deep-cloning?
  Value properties(feature["properties"], doc_properties.GetAllocator());
  doc_properties.AddMember(n, properties, doc_properties.GetAllocator());

  return sfc;
}


Rcpp::List parse_feature_collection_object_wkt(const Value& fc,
                                           std::unordered_set< std::string >& geometry_types,
                                           int& wkt_objects,
                                           std::unordered_set< std::string >& property_keys,
                                           Document& doc_properties,
                                           std::unordered_map< std::string, std::string>& property_types) {
  // a FeatureCollection MUST have members (arrays) called features,
  validate_features(fc, wkt_objects);

  auto features = fc["features"].GetArray();

  unsigned int n = features.Size(); // number of features
  unsigned int i;
  Rcpp::List feature_collection(n);

  for (i = 0; i < n; i++) {
    const Value& feature = features[i];
    feature_collection[i] = parse_feature_object_wkt(feature, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
  }
  return feature_collection;
}


void parse_geojson_wkt(const Value& v,
                       Rcpp::List& sfc,
                       Rcpp::List& properties,
                       int i,
                       std::unordered_set< std::string >& geometry_types,
                       int& wkt_objects,
                       std::unordered_set< std::string >& property_keys,
                       Document& doc_properties,
                       std::unordered_map< std::string, std::string >& property_types
                         ) {
  Rcpp::List res(1);
  validate_type(v, wkt_objects);

  std::string geom_type = v["type"].GetString();

  if (geom_type == "Feature") {

    res = parse_feature_object_wkt(v, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
    sfc[i] = res;

  } else if (geom_type == "FeatureCollection") {

    res = parse_feature_collection_object_wkt(v, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
    sfc[i] = res;

  } else if (geom_type == "GeometryCollection") {

    res = parse_geometry_collection_object_wkt(v, geometry_types, wkt_objects);
    wkt_objects++;
    sfc[i] = res;

  } else {

    parse_geometry_object_wkt(sfc, i, v, geometry_types, wkt_objects);
    wkt_objects++;
  }
}

void parse_geojson_object_wkt(Document& d,
                              Rcpp::List& sfc,
                              Rcpp::List& properties,
                              std::unordered_set< std::string >& geometry_types,
                              int& wkt_objects,
                              std::unordered_set< std::string >& property_keys,
                              Document& doc_properties,
                              std::unordered_map< std::string, std::string >& property_types
                                ) {
  const Value& v = d;
  parse_geojson_wkt(v, sfc, properties, 0, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
}

void parse_geojson_array_wkt(Document& d,
                             Rcpp::List& sfc,
                             Rcpp::List& properties,
                             int i,
                             std::unordered_set< std::string >& geometry_types,
                             int& wkt_objects,
                             std::unordered_set< std::string >& property_keys,
                             Document& doc_properties,
                             std::unordered_map< std::string, std::string>& property_types
                               ) {
  const Value& v = d[i];
  parse_geojson_wkt(v, sfc, properties, i, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
}

Rcpp::List geojson_to_wkt(const char* geojson,
                          std::unordered_set< std::string >& geometry_types,
                          int& wkt_objects,
                          std::unordered_set< std::string >& property_keys,
                          Document& doc_properties,
                          std::unordered_map< std::string, std::string >& property_types
                            ) {

  Document d;
  safe_parse(d, geojson);
  Rcpp::List sf(1);
  Rcpp::List sfc(1);
  Rcpp::List properties(1);
  unsigned int doc_ele;

  std::ostringstream os;
  // Need to 'recurse' into the GeoJSON like what i did for geo_sf
  // because it can be arrays, objects, vectors.
  if (d.IsObject()) {

    Rcpp::List sfg(1);
    parse_geojson_object_wkt(d, sfg, properties, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
    sfc[0] = sfg;

  } else if (d.IsArray()) {
    Rcpp::List sfgs(d.Size());

    for (doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
      parse_geojson_array_wkt(d, sfgs, properties, doc_ele, geometry_types, wkt_objects, property_keys, doc_properties, property_types);
    }
    sfc[0] = sfgs;
  }
  return sfc;
}

Rcpp::List construct_wkt(int& sfg_objects,
                         Rcpp::List& sf,
                         std::unordered_set< std::string >& geometry_types) {

  Rcpp::List sfc_output(sfg_objects);
  std::string geom_attr;

  int sfg_counter = 0;
  fetch_geometries(sf, sfc_output, sfg_counter);
  return sfc_output;
}


Rcpp::List construct_wkt_df(Rcpp::List& lst, std::unordered_set< std::string >& property_keys,
                        std::unordered_map< std::string, std::string>& property_types,
                        Document& doc_properties,
                        int& wkt_objects,
                        int& row_index) {

  Rcpp::List properties(property_keys.size() + 1);  // expand to include geometry

  property_keys.insert("geometry");
  properties.names() = property_keys;

  sort_property_names(properties, property_keys);

  properties["geometry"] = lst;

  setup_property_vectors(property_types, properties, wkt_objects);
  fill_property_vectors(doc_properties, property_types, properties, row_index);

  Rcpp::IntegerVector nv = seq(1, wkt_objects);
  properties.attr("class") = Rcpp::CharacterVector::create("data.frame");
  properties.attr("wkt_column") = "geometry";
  properties.attr("row.names") = nv;

  return properties;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_wkt(Rcpp::StringVector geojson) {

  // iterate over the geojson
  int n = geojson.size();
  int wkt_objects = 0;  // keep track of number of objects
  int row_index;

  // Attributes to keep track of along the way
  //std::unordered_set< std::string > geometry_types = start_geometry_types();
  std::unordered_set< std::string > geometry_types;
  std::unordered_set< std::string > property_keys;   // storing all the 'key' values from 'properties'
  std::unordered_map< std::string, std::string> property_types;

  Document doc_properties;    // Document to store the 'properties'
  doc_properties.SetObject();
  Rcpp::List sfc(n);

  for (int geo_ele = 0; geo_ele < n; geo_ele++) {
    sfc[geo_ele] = geojson_to_wkt(geojson[geo_ele], geometry_types, wkt_objects, property_keys, doc_properties, property_types);
  }

  Rcpp::List res = construct_wkt(wkt_objects, sfc, geometry_types);
  Rcpp::List wkt = construct_wkt_df(res, property_keys, property_types, doc_properties, wkt_objects, row_index);

  return wkt;
}

