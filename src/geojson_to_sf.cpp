
#include <algorithm>
#include <Rcpp.h>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "geojsonsf.h"
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"
#include "geojson_properties.h"

using namespace Rcpp;

void parse_geometry_object(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types,
                           int& sfg_objects) {

  validate_type(geometry, sfg_objects);
  validate_coordinates(geometry, sfg_objects);
  validate_array(geometry["coordinates"], sfg_objects);

  std::string geom_type = geometry["type"].GetString();
  const Value& coord_array = geometry["coordinates"];
  geometry_types.insert(geom_type);


  if (geom_type == "Point") {
    Rcpp::NumericVector point = get_point(coord_array, bbox);
    point.attr("class") = sfg_attributes("POINT");
    sfc[i] = point;

  } else if (geom_type == "MultiPoint") {
    Rcpp::NumericMatrix multi_point = get_multi_point(coord_array, bbox);
    multi_point.attr("class") = sfg_attributes("MULTIPOINT");
    sfc[i] = multi_point;

  } else if (geom_type == "LineString") {
    Rcpp::NumericMatrix line_string = get_line_string(coord_array, bbox);
    line_string.attr("class") = sfg_attributes("LINESTRING");
    sfc[i] = line_string;

  } else if (geom_type == "MultiLineString") {
    Rcpp::List multi_line = get_multi_line_string(coord_array, bbox);
    multi_line.attr("class") = sfg_attributes("MULTILINESTRING");
    sfc[i] = multi_line;

  } else if (geom_type == "Polygon") {
    Rcpp::List polygon = get_polygon(coord_array, bbox);
    polygon.attr("class") = sfg_attributes("POLYGON");
    sfc[i] = polygon;

  } else if (geom_type == "MultiPolygon") {
    Rcpp::List multi_polygon = get_multi_polygon(coord_array, bbox);
    multi_polygon.attr("class") = sfg_attributes("MULTIPOLYGON");
    sfc[i] = multi_polygon;

  } else {
    Rcpp::stop("unknown sfg type");
  }
}

Rcpp::List parse_geometry_collection_object(const Value& val,
                                            Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types,
                                            int& sfg_objects) {
  std::string geom_type;

  validate_geometries(val, sfg_objects);
  auto geometries = val["geometries"].GetArray();
  unsigned int n = geometries.Size();
  unsigned int i;

  Rcpp::List geom_collection(n);

  for (i = 0; i < n; i++) {
    const Value& gcval = geometries[i];
    validate_type(gcval, sfg_objects);
    geom_type = gcval["type"].GetString();
    parse_geometry_object(geom_collection, i, gcval, bbox, geometry_types, sfg_objects);
  }
  geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");

  return geom_collection;
}


Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects,
                                std::set< std::string >& property_keys,
                                Document& doc_properties,
                                std::map< std::string, std::string>& property_types) {

  validate_geometry(feature, sfg_objects);
  validate_properties(feature, sfg_objects);

  const Value& geometry = feature["geometry"];
  validate_type(geometry, sfg_objects);
  std::string type = geometry["type"].GetString();
  Rcpp::List sfc(1);

  if (type == "GeometryCollection") {
  	sfc[0] = parse_geometry_collection_object(geometry, bbox, geometry_types, sfg_objects);
  } else {
    parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);
  }

  sfg_objects++;

  const Value& p = feature["properties"];
  get_property_keys(p, property_keys);
  get_property_types(p, property_types);

  //https://stackoverflow.com/a/33473321/5977215
  std::string s = std::to_string(sfg_objects);
  Value n(s.c_str(), doc_properties.GetAllocator());

  // TODO: is this method deep-cloning?
  Value properties(feature["properties"], doc_properties.GetAllocator());
  doc_properties.AddMember(n, properties, doc_properties.GetAllocator());

  return sfc;
}


Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types,
                                           int& sfg_objects,
                                           std::set< std::string >& property_keys,
                                           Document& doc_properties,
                                           std::map< std::string, std::string>& property_types) {
  // a FeatureCollection MUST have members (array) called features,
  validate_features(fc, sfg_objects);

  auto features = fc["features"].GetArray();

  unsigned int n = features.Size(); // number of features
  unsigned int i;
  Rcpp::List feature_collection(n);
  //std::string geom_type = "FeatureCollection";

  for (i = 0; i < n; i++) {
    const Value& feature = features[i];
    feature_collection[i] = parse_feature_object(feature, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
  }
  return feature_collection;
}



void parse_geojson(const Value& v,
                   Rcpp::List& sfc,
                   Rcpp::List& properties,
                   int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types,
                   int& sfg_objects,
                   std::set< std::string >& property_keys,
                   Document& doc_properties,
                   std::map< std::string, std::string>& property_types) {

  Rcpp::List res(1);
  validate_type(v, sfg_objects);

  std::string geom_type = v["type"].GetString();

  if (geom_type == "Feature") {
    res = parse_feature_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
    sfc[i] = res;

  } else if (geom_type == "FeatureCollection") {

    res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
    sfc[i] = res;

  } else if (geom_type == "GeometryCollection") {

    res = parse_geometry_collection_object(v, bbox, geometry_types, sfg_objects);
    sfg_objects++;
    sfc[i] = res;

  } else {

    parse_geometry_object(sfc, i, v, bbox, geometry_types, sfg_objects);
    sfg_objects++;
  }
}

void parse_geojson_object(Document& d,
                          Rcpp::List& sfc,
                          Rcpp::List& properties,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types,
                          int& sfg_objects,
                          std::set< std::string >& property_keys,
                          Document& doc_properties,
                          std::map< std::string, std::string>& property_types) {
  const Value& v = d;
  parse_geojson(v, sfc, properties, 0, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
}

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::map< std::string, std::string>& property_types) {
  const Value& v = d[i];
  parse_geojson(v, sfc, properties, i, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
}

Rcpp::List geojson_to_sf(const char* geojson,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties,
                         std::map< std::string, std::string>& property_types) {

  Document d;
  safe_parse(d, geojson);
  Rcpp::List sf(1);
  Rcpp::List sfc(1);
  Rcpp::List properties(1);
  unsigned int doc_ele;

  if (d.IsObject()) {
    Rcpp::List sfg(1);
    parse_geojson_object(d, sfg, properties, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
    sfc[0] = sfg;

  } else if (d.IsArray()) {

    Rcpp::List sfgs(d.Size());

    for (doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
      parse_geojson_array(d, sfgs, properties, doc_ele, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
    }
    sfc[0] = sfgs;
  }
  return sfc;
}

void setup_property_vectors(std::map< std::string, std::string>& property_types,
                            Rcpp::List& properties, int& sfg_objects) {

  for (auto keys_it = property_types.begin(); keys_it != property_types.end(); keys_it++) {
    std::string this_key = keys_it->first;
    std::string this_type = keys_it->second;

    if (this_type == "False" || this_type == "True" ) {
      properties[this_key] = na_logical_vector(sfg_objects);
    } else if (this_type == "Number") {
      properties[this_key] = na_numeric_vector(sfg_objects);
    } else {
      properties[this_key] = na_string_vector(sfg_objects);
    }
  }
}


void nested_json_to_string(rapidjson::Value& v,
                           std::string& type,
                           Rcpp::List& properties,
                           int& row_index,
                           std::string& key) {

  StringBuffer sb;
  Writer<StringBuffer> writer(sb);
  v.Accept(writer);
  std::string this_value = sb.GetString();

  if (type != "String") {
    std::string value = any_to_string(this_value);
    update_string_vector(properties, key, value, row_index-1);
  } else {
    std::string value = this_value;
    update_string_vector(properties, key, value, row_index-1);
  }
}

void fill_property_vectors(Document& doc_properties,
                           std::map< std::string, std::string>& property_types,
                           Rcpp::List& properties,
                           int& row_index) {

	static const char* ARRAY_TYPES[] =
		{ "Null", "False", "True", "Object", "Array", "String", "Number" };

  for (auto& m : doc_properties.GetObject()) {
    row_index = std::stoi(m.name.GetString());

    for (auto& p : m.value.GetObject() ) {

      std::string key = p.name.GetString();
      std::string type = property_types[key];

      std::string value_type = ARRAY_TYPES[p.value.GetType()];

      if (value_type == "String") {
        std::string this_value = p.value.GetString();

        if (type != "String") {
          std::string value = any_to_string(this_value);
          update_string_vector(properties, key, value, row_index-1);
        } else {
          std::string value = this_value;
          update_string_vector(properties, key, value, row_index-1);
        }

      } else if (value_type == "Number") {

        double this_value = p.value.GetDouble();

        if (type != "Number") {
          std::string value = any_to_string(this_value);
          update_string_vector(properties, key, value, row_index-1);
        } else {
          double value = p.value.GetDouble();
          update_numeric_vector(properties, key, value, row_index-1);
        }

      } else if (value_type == "False") {

        bool this_value = p.value.GetBool();
        if (type != "False") {
          std::string value = any_to_string(this_value);
          update_string_vector(properties, key, value, row_index-1);
        } else {
          bool value = p.value.GetBool();
          update_logical_vector(properties, key, value, row_index-1);
        }

      } else if (value_type == "True") {

        bool this_value = p.value.GetBool();
        if (type != "True") {
          std::string value = any_to_string(this_value);
          update_string_vector(properties, key, value, row_index-1);
        } else {
          bool value = p.value.GetBool();
          update_logical_vector(properties, key, value, row_index-1);
        }

      } else if (value_type == "Null") {
        // don't do anything...
      } else if (value_type == "Object") {

        Value v = p.value.GetObject();
        nested_json_to_string(v, type, properties, row_index, key);

      } else if (value_type == "Array") {

        Value v = p.value.GetArray();
        nested_json_to_string(v, type, properties, row_index, key);

      } else {
        Rcpp::stop("unknown column data type " + type);
      }
    }
  }
}

Rcpp::List create_sfc(Rcpp::StringVector geojson) {
	// iterate over the geojson
  int n = geojson.size();
  int sfg_objects = 0;  // keep track of number of objects
  //int row_index;

  // Attributes to keep track of along the way
  Rcpp::NumericVector bbox = start_bbox();
  std::set< std::string > geometry_types = start_geometry_types();
  std::set< std::string > property_keys;   // storing all the 'key' values from 'properties'
  std::map< std::string, std::string> property_types;

  Document doc_properties;    // Document to store the 'properties'
  doc_properties.SetObject();
  Rcpp::List sfc(n);

  for (int geo_ele = 0; geo_ele < n; geo_ele++ ){
    sfc[geo_ele] = geojson_to_sf(geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
  }

  return construct_sfc(sfg_objects, sfc, bbox, geometry_types);
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sfc(Rcpp::StringVector geojson) {
	return create_sfc(geojson);
}

Rcpp::List construct_sf(Rcpp::List& lst, std::set< std::string >& property_keys,
                     std::map< std::string, std::string>& property_types,
                     Document& doc_properties,
                     int& sfg_objects,
                     int& row_index) {

  Rcpp::List properties(property_keys.size() + 1);  // expand to include geometry

  property_keys.insert("geometry");
  properties.names() = property_keys;
  properties["geometry"] = lst;

  setup_property_vectors(property_types, properties, sfg_objects);
  fill_property_vectors(doc_properties, property_types, properties, row_index);

  Rcpp::IntegerVector nv = seq(1, sfg_objects);
  properties.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
  properties.attr("sf_column") = "geometry";
  properties.attr("row.names") = nv;

  return properties;
}

Rcpp::List generic_geojson_to_sf(Rcpp::StringVector geojson) {
	// iterate over the geojson
	int n = geojson.size();
	int sfg_objects = 0;  // keep track of number of objects
	int row_index;

	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	std::set< std::string > property_keys;   // storing all the 'key' values from 'properties'
	std::map< std::string, std::string > property_types;

	Document doc_properties;    // Document to store the 'properties'
	doc_properties.SetObject();
	Rcpp::List sfc(n);

	for (int geo_ele = 0; geo_ele < n; geo_ele++ ){
		sfc[geo_ele] = geojson_to_sf(geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
	}


	Rcpp::List res = construct_sfc(sfg_objects, sfc, bbox, geometry_types);
	return construct_sf(res, property_keys, property_types, doc_properties, sfg_objects, row_index);
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {
	return generic_geojson_to_sf(geojson);
}
