#include "rapidjson/document.h"

#include <algorithm>
#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"
#include "geojson_sf.h"

using namespace Rcpp;

// TODO:
// - handle incorrectly formed geometry type
// -- e.g., MultiPoint with only one-nested array


void parse_geometry_object(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types,
                           int& sfg_objects) {

	validate_type(geometry, sfg_objects);
	validate_coordinates(geometry, sfg_objects);

	std::string geom_type = geometry["type"].GetString();
	const Value& coord_array = geometry["coordinates"];
	geometry_types.insert(geom_type);

	if (geom_type == "Point") {
		sfc[i] = get_point(coord_array, bbox);
		//sfc_classes[counter] = "POINT";

	} else if (geom_type == "MultiPoint") {
		sfc[i] = get_multi_point(coord_array, bbox);
		//sfc_classes[counter] = "MULTIPOINT";

	} else if (geom_type == "LineString") {
		sfc[i] = get_line_string(coord_array, bbox);
		//sfc_classes[counter] = "LINESTRING";

	} else if (geom_type == "MultiLineString") {
		sfc[i] = get_multi_line_string(coord_array, bbox);
		//sfc_classes[counter] = "MULTILINESTRING";

	} else if (geom_type == "Polygon") {
		sfc[i] = get_polygon(coord_array, bbox);
		//sfc_classes[counter] = "POLYGON";

	} else if (geom_type == "MultiPolygon") {
		sfc[i] = get_multi_polygon(coord_array, bbox);
		//sfc_classes[counter] = "MULTIPOLYGON";

	} else {
		Rcpp::stop("unknown sfg type");
	}
}

Rcpp::List parse_geometry_collection_object(const Value& val,
                                            Rcpp::NumericVector& bbox,
                                            std::set< std::string >& geometry_types,
                                            int& sfg_objects) {
	std::string geom_type;

	auto geometries = val["geometries"].GetArray();
	int n = geometries.Size();

	Rcpp::List geom_collection(n);

	for (int i = 0; i < n; i++) {
		const Value& gcval = geometries[i];
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
	Rcpp::List sfc(1);
	parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);
	sfg_objects++;
	// get property keys
	const Value& p = feature["properties"];
	get_property_keys(p, property_keys);
	get_property_types(p, property_types);

	// TODO:
	// parse properties
	// https://github.com/Tencent/rapidjson/blob/master/doc/faq.md
	// DOM and SAX


  //https://stackoverflow.com/a/33473321/5977215
  //std::string s = std::to_string(sfg_objects);
  //Value index(s.c_str(), s.size(), doc_properties.GetAllocator()); // copy string

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
	// a FeatureCollection MUST have members called features,
	// which is an array
	validate_features(fc, sfg_objects);

	auto features = fc["features"].GetArray();

	int n = features.Size(); // number of features
	Rcpp::List feature_collection(n);
	std::string geom_type = "FeatureCollection";

	for (int i = 0; i < n; i++) {
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
	std::string geom_type;

	validate_type(v, sfg_objects);

	geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		res = parse_feature_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
		//sfg_objects++;
		res.attr("geo_type") = "FEATURE";
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
		//sfg_objects += res.length();

		//Rcpp::Rcout << "feature collection length: " << res.length() << std::endl;
		//Rcpp::Rcout << "sfg_objects : " << sfg_objects << std::endl;

		res.attr("geo_type") = "FEATURECOLLECTION";

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

	if (d.IsObject() ) {

	  Rcpp::List sfg(1);
		parse_geojson_object(d, sfg, properties, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
		sfc[0] = sfg;

	} else if (d.IsArray()) {

		Rcpp::List sfgs(d.Size());
		Rcpp::LogicalVector doc_ele_properties(d.Size());

		for (int doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
			parse_geojson_array(d, sfgs, properties, doc_ele, bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
		}
		sfc[0] = sfgs;
	}

	return sfc;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sfc(Rcpp::StringVector geojson) {
  Rcpp::List lst;

  return lst;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	int sfg_objects = 0;  // keep track of number of objects
	int row_index;

	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	std::set< std::string > property_keys;   // storing all the 'key' values from 'properties'
	std::map< std::string, std::string> property_types;

	Document doc_properties;    // Document to store the 'properties'
	doc_properties.SetObject();
	Rcpp::List sf(n);

	for (int geo_ele = 0; geo_ele < n; geo_ele++ ){
		sf[geo_ele] = geojson_to_sf(geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys, doc_properties, property_types);
	}

  Rcpp::List res = construct_sfc(sfg_objects, sf, bbox, geometry_types);

	Rcpp::List properties(property_keys.size() + 1);  // expand to include geometry

	property_keys.insert("geometry");
	properties.names() = property_keys;
	properties["geometry"] = res;

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

	for (auto& m : doc_properties.GetObject()) {
  	row_index = std::stoi(m.name.GetString());

  	for (auto& p : m.value.GetObject() ) {

  		std::string key = p.name.GetString();
  		std::string type = property_types[key];

  		// TODO:
  		// if the actual type of the property object is different,
  		// need to extract it using the correct `GetType()` method,
  		// then convert it to String
  		std::string value_type = geojsonsf::ARRAY_TYPES[p.value.GetType()];

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
  			// TODO: convert to string?

  		} else if (value_type == "Array") {
  			// TODO: convert to string?

  		} else {
  			Rcpp::stop("unknown column data type " + type);
  		}

  		/*
  		if (type == "String") {

  			std::string value = p.value.GetString();
  	    update_string_vector(properties, key, value, row_index-1);

  		} else if (type == "Number") {

  			double value = p.value.GetDouble();
  			update_numeric_vector(properties, key, value, row_index-1);

  		} else if (type == "False" || type == "True") {

  			bool value = p.value.GetBool();
  			update_logical_vector(properties, key, value, row_index-1);

  		} else if (type == "Null") {
  			// don't do anything...
  		} else if (type == "Object") {
  			// TODO: convert to string?

  		} else if (type == "Array") {
  			// TODO: convert to string?

  		} else {
  			Rcpp::stop("unknown column data type " + type);
  		}
  		*/
  	}
  }

	Rcpp::IntegerVector nv = seq(1, sfg_objects);
  properties.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
  properties.attr("sf_column") = "geometry";
  properties.attr("row.names") = nv;
  return properties;

	//Rcpp::DataFrame df(properties);
	//df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
	//df.attr("sf_column") = "geometry";

	//return df;
}
