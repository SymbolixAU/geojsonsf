#ifndef GEOJSON_TO_SF_H
#define GEOJSON_TO_SF_H


#include <algorithm>
#include <Rcpp.h>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geojson/geojson_to_sf.hpp"
#include "geojsonsf/sf/sf/construct.hpp"
#include "geojsonsf/sf/sfc/geojson_sfc.hpp"
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_validate.hpp"
#include "geojsonsf/geojson/geojson_properties.hpp"
#include "geojsonsf/geojson/parse.hpp"

using namespace rapidjson;

namespace geojsonsf {
namespace sf {

  inline Rcpp::List geojson_to_sf(const char* geojson,
	                         Rcpp::NumericVector& bbox,
	                         std::unordered_set< std::string >& geometry_types,
	                         int& sfg_objects,
	                         std::unordered_set< std::string >& property_keys,
	                         Document& doc_properties,
	                         std::unordered_map< std::string, std::string>& property_types,
	                         bool& expand_geometries,
	                         int& nempty) {

		Document d;
		geojsonsf::validate::safe_parse(d, geojson);
		Rcpp::List sf(1);
		Rcpp::List sfc(1);
		Rcpp::List properties(1);
		unsigned int doc_ele;

		if (d.IsObject()) {
			Rcpp::List sfg(1);
			geojsonsf::geojson::parse::parse_geojson_object(
				d, sfg, properties, bbox, geometry_types, sfg_objects, property_keys,
				doc_properties, property_types, expand_geometries, nempty
			);
			sfc[0] = sfg;

		} else if (d.IsArray()) {

			Rcpp::List sfgs(d.Size());

			for (doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
				geojsonsf::geojson::parse::parse_geojson_array(
					d, sfgs, properties, doc_ele, bbox, geometry_types, sfg_objects,
					property_keys, doc_properties, property_types, expand_geometries, nempty
				);
			}
			sfc[0] = sfgs;
		}
		return sfc;
	}

  inline Rcpp::List create_sfc(Rcpp::StringVector geojson, bool& expand_geometries) {
		// iterate over the geojson
		int n = geojson.size();
		int sfg_objects = 0;  // keep track of number of objects
		int nempty = 0;
		//int row_index;

		// Attributes to keep track of along the way
		Rcpp::NumericVector bbox = geojsonsf::sfc::utils::start_bbox();
		std::unordered_set< std::string > geometry_types;
		std::unordered_set< std::string > property_keys;   // storing all the 'key' values from 'properties'
		std::unordered_map< std::string, std::string> property_types;

		Document doc_properties;    // Document to store the 'properties'
		doc_properties.SetObject();
		Rcpp::List sfc(n);

		for (int geo_ele = 0; geo_ele < n; geo_ele++ ){
			sfc[geo_ele] = geojson_to_sf(
				geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys,
				doc_properties, property_types, expand_geometries, nempty
			);
		}

		return geojsonsf::sfc::construct_sfc(sfg_objects, sfc, bbox, geometry_types, nempty);
	}

  inline Rcpp::List generic_geojson_to_sf(Rcpp::StringVector geojson, bool& expand_geometries) {
		// iterate over the geojson
		int n = geojson.size();
		int sfg_objects = 0;  // keep track of number of objects
		int row_index = 0;
		int nempty = 0;

		// Attributes to keep track of along the way
		Rcpp::NumericVector bbox = geojsonsf::sfc::utils::start_bbox();
		std::unordered_set< std::string > geometry_types;
		std::unordered_set< std::string > property_keys;   // storing all the 'key' values from 'properties'
		std::unordered_map< std::string, std::string > property_types;

		Document doc_properties;    // Document to store the 'properties'
		doc_properties.SetObject();
		Rcpp::List sfc( n );

		for ( int geo_ele = 0; geo_ele < n; geo_ele++ ){
			sfc[geo_ele] = geojson_to_sf(
				geojson[geo_ele], bbox, geometry_types, sfg_objects, property_keys,
				doc_properties, property_types, expand_geometries, nempty
			);
		}

		Rcpp::List res = geojsonsf::sfc::construct_sfc( sfg_objects, sfc, bbox, geometry_types, nempty );
		return geojsonsf::sf::construct_sf( res, property_keys, property_types, doc_properties, sfg_objects, row_index );
	}

} // namesapce sf
} // namespace geojsonsf

#endif
