#include "rapidjson/document.h"
//include "rapidjson/stringbuffer.h"
//#include "rapidjson/writer.h"

#include <algorithm>
#include <Rcpp.h>
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"
#include "geojson_validate.h"

using namespace Rcpp;

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

	} else if (geom_type == "MultiLinestring") {
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

void get_property_keys(const Value& v, std::set< std::string >& property_keys) {
	for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter){
		property_keys.insert(iter->name.GetString());
	}
}

Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects,
                                std::set< std::string >& property_keys,
                                Document& doc_properties) {

	validate_geometry(feature, sfg_objects);
	validate_properties(feature, sfg_objects);

	const Value& geometry = feature["geometry"];
	Rcpp::List sfc(1);
	parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);
	sfg_objects++;
	// get property keys
	//const Value& properties = feature["properties"];
	//get_property_keys(p, property_keys);

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
                                           Document& doc_properties) {
	// a FeatureCollection MUST have members called features,
	// which is an array
	validate_features(fc, sfg_objects);

	auto features = fc["features"].GetArray();

	int n = features.Size(); // number of features
	Rcpp::List feature_collection(n);
	std::string geom_type = "FeatureCollection";

	for (int i = 0; i < n; i++) {
		const Value& feature = features[i];
		feature_collection[i] = parse_feature_object(feature, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
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
                   Document& doc_properties) {

	Rcpp::List res(1);
	std::string geom_type;

	validate_type(v, sfg_objects);

	geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		res = parse_feature_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
		//sfg_objects++;
		res.attr("geo_type") = "FEATURE";
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
		sfg_objects += res.length();
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
                          Document& doc_properties) {
	const Value& v = d;
	parse_geojson(v, sfc, properties, 0, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
}

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties) {
	const Value& v = d[i];
	parse_geojson(v, sfc, properties, i, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
}

Rcpp::List geojson_to_sf(const char* geojson,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects,
                         std::set< std::string >& property_keys,
                         Document& doc_properties) {

	Document d;
	safe_parse(d, geojson);
	Rcpp::List sf(1);
	Rcpp::List sfc(1);
	Rcpp::List properties(1);

	if (d.IsObject() ) {

	  Rcpp::List sfg(1);
		parse_geojson_object(d, sfg, properties, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
		sfc[0] = sfg;

	} else if (d.IsArray()) {

		Rcpp::List sfgs(d.Size());
		Rcpp::LogicalVector doc_ele_properties(d.Size());

		for (int doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
			parse_geojson_array(d, sfgs, properties, doc_ele, bbox, geometry_types, sfg_objects, property_keys, doc_properties);
		}
		sfc[0] = sfgs;
	}

	return sfc;
}

void add_vector_to_list(Rcpp::List& properties, std::string key, std::string type, int& sfg_objects) {

	if (type == "number") {
		properties[key] = Rcpp::NumericVector(sfg_objects);
	} else if (type == "boolean") {
		properties[key] = Rcpp::LogicalVector(sfg_objects);
	} else {
		properties[key] = Rcpp::StringVector(sfg_objects);
	}

}


// [[Rcpp::export]]
Rcpp::DataFrame rcpp_geojson_to_sf(Rcpp::StringVector geojson) {

	// iterate over the geojson
	int n = geojson.size();
	int sfg_objects = 0;  // keep track of number of objects

	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	std::set< std::string > property_keys;   // storing all the 'key' values from 'properties'

	// TODO:
	// keep track of which 'geo_ele' contain 'properties'
	// keep track of which 'doc_ele' contain 'properties'

	Document doc_properties;    // Document to store the 'properties'
	doc_properties.SetObject();

	Rcpp::LogicalVector geo_ele_properties(n);

	Rcpp::List sf(n);
	for (int geo_ele = 0; geo_ele < n; geo_ele++ ){
		sf[geo_ele] = geojson_to_sf(geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys, doc_properties);
	}

  Rcpp::List res = construct_sfc(sfg_objects, sf, bbox, geometry_types);

	//property_keys.insert("test key");
	Rcpp::List properties(property_keys.size() + 1);

	/*
	Rcpp::Rcout << "debug: keys" << std::endl;
	for (auto keys_it = property_keys.begin(); keys_it != property_keys.end(); keys_it++) {
		std::cout << *keys_it << std::endl;
	}
	*/
	property_keys.insert("geometry");
	properties.names() = property_keys;
	properties["geometry"] = res;

	// create and insert vectors for each 'key' (other than 'geometry')

	for (auto keys_it = property_keys.begin(); keys_it != property_keys.end(); keys_it++) {
		std::string this_key = *keys_it;
		if (this_key != "geometry") {
		  properties[this_key] = Rcpp::CharacterVector(sfg_objects);
		}
	}

	//doc_properties.Accept()

	//StringBuffer buffer;
	//Writer<StringBuffer> writer(buffer);
	//doc_properties.Accept(writer);
	//const char* output = buffer.GetString();


	// iterate back through the GeoJSON and get all the property values
	// --
	for (int i = 0; i < n; i++) {
		//
	}
	Rcpp::Rcout << "debug: doc_properties size: " << doc_properties.Size() << std::endl;


	int tempCounter =0;
	//for (int i = 0; i < doc_properties.Size(); i++ ) {
  for (int i = 0; i < sfg_objects; i++ ) {

  	//const Value& tmp = doc_properties[i].GetObject();
  	//std::cout << tmp.Size() << std::endl;

		//std::cout << tempCounter << std::endl;
		//tempCounter++;
		//const Value& prop = doc_properties[i];
		//std::cout << prop.Size() << std::endl;
		//std::cout << "property is obj: " << b << std::endl;
		//if (doc_properties[i].IsObject()) {

		//} else {
		//  std::string s = doc_properties[i].GetString();
		//	std::cout << s << std::endl;
		//}
	}



//	for (auto keys_it = doc_properties.begin(); keys_it != doc_properties.end(); keys_it++) {
//		std::cout << *keys_it << std::endl;
//	}


	Rcpp::DataFrame df(properties);
	df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
	df.attr("sf_column") = "geometry";

	// TODO (properties):
	// get properties
	// create vectors / lists entries for each key

	return df;
	//return properties;
	//return res;
}
