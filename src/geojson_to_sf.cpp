#include "rapidjson/document.h"

#include <algorithm>
#include <Rcpp.h>
#include "geojson_to_sf.h"
#include "geojson_sfc.h"
#include "geojson_sfg.h"

using namespace Rcpp;

void parse_geometry_object(Rcpp::List& sfc,
                           int i,
                           const Value& geometry,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types,
                           int& sfg_objects) {

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

Rcpp::List parse_feature_object(const Value& feature,
                                Rcpp::NumericVector& bbox,
                                std::set< std::string >& geometry_types,
                                int& sfg_objects) {
	// A feature MUST have
	// - type
	// - geometry
	// - properties

	// TODO:
	// error if there is no member called '"type": "Feature"
	const Value& geometry = feature["geometry"];
	Rcpp::List sfc(1);
	parse_geometry_object(sfc, 0, geometry, bbox, geometry_types, sfg_objects);

	// TODO:
	// parse properties

	return sfc;
}


Rcpp::List parse_feature_collection_object(const Value& fc,
                                           Rcpp::NumericVector& bbox,
                                           std::set< std::string >& geometry_types,
                                           int& sfg_objects) {
	// a FeatureCollection MUST have members called features,
	// which is an array

	// TODO:
	// - error handle if 'features' not present
	auto features = fc["features"].GetArray();

	int n = features.Size(); // number of features
	Rcpp::List feature_collection(n);
	std::string geom_type = "FeatureCollection";

	for (int i = 0; i < n; i++) {
		const Value& feature = features[i];
		feature_collection[i] = parse_feature_object(feature, bbox, geometry_types, sfg_objects);
	}

	return feature_collection;
}

void parse_geojson(const Value& v,
                   Rcpp::List& sfc,
                   Rcpp::List& properties,
                   int i,
                   Rcpp::NumericVector& bbox,
                   std::set< std::string >& geometry_types,
                   int& sfg_objects) {

	//TODO: checks if fields exist

	Rcpp::List res(1);
	std::string geom_type;

	if (v.HasMember("type") == FALSE) Rcpp::stop("No 'type' member - invalid GeoJSON");

	geom_type = v["type"].GetString();

	if (geom_type == "Feature") {

		res = parse_feature_object(v, bbox, geometry_types, sfg_objects);
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfg_objects++;
		res.attr("geo_type") = "FEATURE";
		sfc[i] = res;

	} else if (geom_type == "FeatureCollection") {

		res = parse_feature_collection_object(v, bbox, geometry_types, sfg_objects);
		//Rcpp::Rcout << "debug: featurecollection size: " << res.size() << std::endl;
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfg_objects += res.length();
		res.attr("geo_type") = "FEATURECOLLECTION";

		//std::string tmp = res.attr("geo_type");
		//Rcpp::Rcout << "debug: tmp " <<  tmp << std::endl;

		sfc[i] = res;

	} else if (geom_type == "GeometryCollection") {

		res = parse_geometry_collection_object(v, bbox, geometry_types, sfg_objects);
		//attach_sfc_attributes(res, geom_type, bbox, geometry_types);
		sfg_objects++;
		//res.attr("geo_type") = "GEOMETRYCOLLECTION";
		sfc[i] = res;

	} else {

		parse_geometry_object(sfc, i, v, bbox, geometry_types, sfg_objects);
		sfg_objects++;
		//attach_sfc_attributes(sfc, geom_type, bbox, geometry_types);
	}
	//attach_sfc_attributes(sfc, geom_type, bbox, geometry_types);
}

void parse_geojson_object(Document& d,
                          Rcpp::List& sfc,
                          Rcpp::List& properties,
                          Rcpp::NumericVector& bbox,
                          std::set< std::string >& geometry_types,
                          int& sfg_objects) {
	const Value& v = d;
	parse_geojson(v, sfc, properties, 0, bbox, geometry_types, sfg_objects);
}

void parse_geojson_array(Document& d,
                         Rcpp::List& sfc,
                         Rcpp::List& properties,
                         int i,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types,
                         int& sfg_objects) {
	const Value& v = d[i];
	parse_geojson(v, sfc, properties, i, bbox, geometry_types, sfg_objects);
}

Rcpp::List construct_sfc(int& sfg_objects,
                         Rcpp::List& sfc,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {

	Rcpp::List sfc_output(sfg_objects);
	std::string geom_attr;
	//Rcpp::Rcout << "list size: " << sfc.length() << std::endl;

	int counter = 0;

	for (int i = 0; i < sfc.length(); i++) {
		Rcpp::List ele = sfc[i];

		if (Rf_isNull(ele.attr("geo_type"))){
			//Rcpp::Rcout << "debug: geometry" << std::endl;
			geom_attr = "GEOMETRY";
			sfc_output[counter] = sfc[0];
			counter++;

		} else {
			std::string tmp_attr = ele.attr("geo_type");
  		geom_attr = tmp_attr;
			// it's a geometry
			if (geom_attr == "FEATURECOLLECTION") {
			  //Rcpp::Rcout << "debug: geometry - FEATURECOLLECTION" << std::endl;
  			// 2 level sdeep
  			Rcpp::List fc(ele.size());
  			//Rcpp::Rcout << "fc size: " << ele.size() << std::endl;
  			for (int j = 0; j < ele.size(); j++) {
  				Rcpp::List tmp = ele[j];
  				sfc_output[counter] = tmp[0];
  				counter++;
  			}


	  	} else if (geom_attr == "FEATURE" ) {
  			//Rcpp::Rcout << "debug: geometry - FEATURE" << std::endl;
	  		sfc_output[counter] = ele[0];
	  		counter++;
	  	}
		}
	}

	std::string gt = "GEOMETRY";
	attach_sfc_attributes(sfc_output, gt, bbox, geometry_types);

	return sfc_output;
}

Rcpp::List geojson_to_sf(const char* geojson,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {

	// TODO:
	// only start building the result sf when we are inside the final array


	Document d;
	d.Parse(geojson);
	Rcpp::List sf(1);
	Rcpp::List sfc(1);
	Rcpp::List properties(1);

	int sfg_objects = 0;  // keep track of number of objects

	if (d.IsObject() ) {
		Rcpp::Rcout << "debug: is OBJECT" << std::endl;

	  //Rcpp::List sfg(1);
		parse_geojson_object(d, sfc, properties, bbox, geometry_types, sfg_objects);
		//sf[0] = sfg;

//	} else if (d.IsArray()) {
//		Rcpp::Rcout << "debug: is ARRAY" << std::endl;
//
//		Rcpp::List sfc(d.Size());
//
//		for (int i = 0; i < d.Size(); i++) {
//			parse_geojson_array(d, sfc, i, bbox, geometry_types);
//		}
//
//		sf[0] = sfc;
	}
	Rcpp::List res = construct_sfc(sfg_objects, sfc, bbox, geometry_types);

//	Rcpp::Rcout << "sfg_objects: " << sfg_objects << std::endl;

	return res;
}

// TODO:
// A fector of goejson strings should be come sfgs...?
//
// - geometry becomes sfg
// - feature becomes sf
// - feature collection become sf



// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_sf(const char* geojson) {

	// iterate over the geojson
	//int n = geojson.size();

	// iff a vector, collapse to an array...


	// Attributes to keep track of along the way
	Rcpp::NumericVector bbox = start_bbox();
	std::set< std::string > geometry_types = start_geometry_types();
	//Rcpp::StringVector sfc_classes = start_sfc_classes(n);

	Rcpp::List sf = geojson_to_sf(geojson, bbox, geometry_types);


	//Rcpp::List sfc(n);
  //
	//for (int i = 0; i < n; i++ ){
	//	sfc[i] = geojson_to_sf(geojson[i], bbox, geometry_types);
	//}

	return sf;
}
