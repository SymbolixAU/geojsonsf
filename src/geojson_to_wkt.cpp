
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/sf/sfc/geojson_sfc.hpp"
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_to_sf.hpp"
#include "geojsonsf/geojson/geojson_validate.hpp"
#include "geojsonsf/geojson/geojson_properties.hpp"
#include "geojsonsf/wkt/geojson_wkt.hpp"

#include "sfheaders/sfg/sfg_attributes.hpp"

using namespace rapidjson;

void parse_geometry_object_wkt(
		Rcpp::List& sfc,
		R_xlen_t i,
    const Value& geometry,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    R_xlen_t& coord_dim
) {

  geojsonsf::validate::validate_type(geometry, wkt_objects);
	geojsonsf::validate::validate_coordinates(geometry, wkt_objects);
	geojsonsf::validate::validate_array(geometry["coordinates"], wkt_objects);

  std::string geom_type = geometry["type"].GetString();
  const Value& coord_array = geometry["coordinates"];
  geometry_types.insert(geom_type);

	std::ostringstream os;
	Rcpp::StringVector wkt;
	//int coord_dim = 0;
	//begin_wkt(os, geom_type);

  if (geom_type == "Point") {
    point_to_wkt(os, coord_array, coord_dim );

  } else if (geom_type == "MultiPoint") {
    multi_point_to_wkt(os, coord_array, coord_dim);

  } else if (geom_type == "LineString") {
    line_string_to_wkt(os, coord_array, coord_dim);

  } else if (geom_type == "MultiLineString") {
    multi_line_string_to_wkt(os, coord_array, coord_dim);

  } else if (geom_type == "Polygon") {
    polygon_to_wkt(os, coord_array, coord_dim);

  } else if (geom_type == "MultiPolygon") {
    multi_polygon_to_wkt(os, coord_array, coord_dim);

  } else {
    Rcpp::stop("unknown sfg type");
  }

  std::ostringstream os_begin; // call AFTER we know the XYZM dimension
  begin_wkt( os_begin, geom_type, coord_dim );
  os_begin << os.str();
	end_wkt(os_begin, geom_type);

  wkt = os_begin.str();
  transform(geom_type.begin(), geom_type.end(), geom_type.begin(), ::toupper);

  std::string dim = sfheaders::sfg::sfg_dimension( coord_dim );
  //wkt.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);
  wkt.attr("class") = Rcpp::CharacterVector::create("wkt", dim, geom_type);

  sfc[i] = wkt;
}


Rcpp::List parse_geometry_collection_object_wkt(
		const Value& val,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    R_xlen_t& coord_dim
	) {

  std::string geom_type;

  geojsonsf::validate::validate_geometries(val, wkt_objects);
  auto geometries = val["geometries"].GetArray();
  R_xlen_t n = geometries.Size();
  R_xlen_t i;

  Rcpp::List geom_collection(n);
  Rcpp::List geom_collection_wkt(1);

  for (i = 0; i < n; ++i) {
    const Value& gcval = geometries[i];
  	geojsonsf::validate::validate_type(gcval, wkt_objects);
    geom_type = gcval["type"].GetString();
    parse_geometry_object_wkt(geom_collection, i, gcval, geometry_types, wkt_objects, coord_dim);
  }

  // collapse into a single WKT string
  std::ostringstream os;
  os << "GEOMETRYCOLLECTION (";
  for (i = 0; i < n; ++i) {
    std::string g = geom_collection[i];
    os << g;
    coord_separator(os, i, n);
  }
  os << ")";

  Rcpp::StringVector wkt = os.str();

  //geom_collection_wkt = os.str();

  std::string dim = sfheaders::sfg::sfg_dimension( coord_dim );
  std::string attribute = "GEOMETRYCOLLECTION";
  // //geom_collection_wkt.attr("class") = sfheaders::sfg::sfg_attributes( dim, attribute );
  //geom_collection_wkt.attr("class") = Rcpp::CharacterVector::create("wkt", dim, attribute );

  wkt.attr("class") = Rcpp::CharacterVector::create("wkt", dim, attribute);

  geom_collection_wkt[0] = wkt;
  return geom_collection_wkt;
}


Rcpp::List parse_feature_object_wkt(
		const Value& feature,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string>& property_types,
    R_xlen_t& coord_dim
	) {

	geojsonsf::validate::validate_geometry(feature, wkt_objects);
	geojsonsf::validate::validate_properties(feature, wkt_objects);

  const Value& geometry = feature["geometry"];

  Rcpp::List sfc(1);

  if (geometry.Size() > 0) {
  	geojsonsf::validate::validate_type(geometry, wkt_objects);
  	std::string geom_type = geometry["type"].GetString();

  	if (geom_type == "GeometryCollection") {
  		Rcpp::List gc = parse_geometry_collection_object_wkt(geometry, geometry_types, wkt_objects, coord_dim);
  		sfc[0] = gc;
  	} else {
  		parse_geometry_object_wkt(sfc, 0, geometry, geometry_types, wkt_objects, coord_dim);
  	}

  } else {
  	Rcpp::StringVector wkt = "POINT EMPTY";
  	coord_dim = 2; // so it pasess sfheaders::sfg::sfg_dimension() checks
  	std::string dim = sfheaders::sfg::sfg_dimension( coord_dim );
  	std::string attribute = "POINT";
  	//wkt.attr("class") = sfheaders::sfg::sfg_attributes( dim, attribute );
  	wkt.attr("class") = Rcpp::CharacterVector::create("wkt", dim, attribute );
  	sfc[0] = wkt;
  }

  wkt_objects++;
  // get property keys
  const Value& p = feature["properties"];
  geojsonsf::geojson_properties::get_property_keys(p, property_keys);
  geojsonsf::geojson_properties::get_property_types(p, property_types);

  //https://stackoverflow.com/a/33473321/5977215
  std::string s = std::to_string(wkt_objects);
  Value n(s.c_str(), doc_properties.GetAllocator());

  // TODO: is this method deep-cloning?
  Value properties(feature["properties"], doc_properties.GetAllocator());
  doc_properties.AddMember(n, properties, doc_properties.GetAllocator());

  return sfc;
}


Rcpp::List parse_feature_collection_object_wkt(
		const Value& fc,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string>& property_types,
    R_xlen_t& coord_dim
	) {
  // a FeatureCollection MUST have members (arrays) called features,
  geojsonsf::validate::validate_features(fc, wkt_objects);

  auto features = fc["features"].GetArray();

  R_xlen_t n = features.Size(); // number of features
  R_xlen_t i;
  Rcpp::List feature_collection(n);

  for (i = 0; i < n; ++i) {
    const Value& feature = features[i];
    feature_collection[i] = parse_feature_object_wkt(
    	feature, geometry_types, wkt_objects, property_keys, doc_properties,
    	property_types, coord_dim
    	);
  }
  return feature_collection;
}


void parse_geojson_wkt(
		const Value& v,
    Rcpp::List& sfc,
    Rcpp::List& properties,
    R_xlen_t i,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string >& property_types,
    R_xlen_t& coord_dim
  ) {
  Rcpp::List res(1);
	geojsonsf::validate::validate_type(v, wkt_objects);

  std::string geom_type = v["type"].GetString();

  if (geom_type == "Feature") {

    res = parse_feature_object_wkt(
    	v, geometry_types, wkt_objects, property_keys, doc_properties,
    	property_types, coord_dim
  	);
    sfc[i] = res;

  } else if (geom_type == "FeatureCollection") {

    res = parse_feature_collection_object_wkt(
    	v, geometry_types, wkt_objects, property_keys, doc_properties,
    	property_types, coord_dim
  	);
    sfc[i] = res;

  } else if (geom_type == "GeometryCollection") {

    res = parse_geometry_collection_object_wkt(v, geometry_types, wkt_objects, coord_dim);
    wkt_objects++;
    sfc[i] = res;

  } else {

    parse_geometry_object_wkt(sfc, i, v, geometry_types, wkt_objects, coord_dim);
    wkt_objects++;
  }
}

void parse_geojson_object_wkt(
		Document& d,
    Rcpp::List& sfc,
    Rcpp::List& properties,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string >& property_types,
    R_xlen_t& coord_dim
 ) {
  const Value& v = d;
  parse_geojson_wkt(
  	v, sfc, properties, 0, geometry_types, wkt_objects, property_keys,
  	doc_properties, property_types, coord_dim
  	);
}

void parse_geojson_array_wkt(
		Document& d,
    Rcpp::List& sfc,
    Rcpp::List& properties,
    R_xlen_t i,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string>& property_types,
    R_xlen_t& coord_dim
  ) {
  const Value& v = d[i];
  parse_geojson_wkt(
  	v, sfc, properties, i, geometry_types, wkt_objects, property_keys,
  	doc_properties, property_types, coord_dim
  	);
}

Rcpp::List geojson_to_wkt(
		const char* geojson,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& wkt_objects,
    std::unordered_set< std::string >& property_keys,
    Document& doc_properties,
    std::unordered_map< std::string, std::string >& property_types,
    R_xlen_t& coord_dim
  ) {

  Document d;
	geojsonsf::validate::safe_parse(d, geojson);
  Rcpp::List sf(1);
  Rcpp::List sfc(1);
  Rcpp::List properties(1);
  R_xlen_t doc_ele;

  std::ostringstream os;
  // Need to 'recurse' into the GeoJSON like what i did for geo_sf
  // because it can be arrays, objects, vectors.
  if (d.IsObject()) {

    Rcpp::List sfg(1);
    parse_geojson_object_wkt(
    	d, sfg, properties, geometry_types, wkt_objects, property_keys,
    	doc_properties, property_types, coord_dim
    	);
    sfc[0] = sfg;

  } else if (d.IsArray()) {
    Rcpp::List sfgs(d.Size());

    for (doc_ele = 0; doc_ele < d.Size(); doc_ele++) {
      parse_geojson_array_wkt(
      	d, sfgs, properties, doc_ele, geometry_types, wkt_objects, property_keys,
      	doc_properties, property_types, coord_dim
    	);
    }
    sfc[0] = sfgs;
  }
  return sfc;
}

Rcpp::List construct_wkt(
		R_xlen_t& sfg_objects,
    Rcpp::List& sf,
    std::unordered_set< std::string >& geometry_types,
    R_xlen_t& coord_dim
	) {

  Rcpp::List sfc_output(sfg_objects);
  std::string geom_attr;

  R_xlen_t sfg_counter = 0;
  geojsonsf::sfc::utils::fetch_geometries(sf, sfc_output, sfg_counter);
  return sfc_output;
}


Rcpp::List construct_wkt_df(
		Rcpp::List& lst, std::unordered_set< std::string >& property_keys,
    std::unordered_map< std::string, std::string>& property_types,
    Document& doc_properties,
    R_xlen_t& wkt_objects,
    R_xlen_t& row_index,
    R_xlen_t& coord_dim
	) {

  Rcpp::List properties(property_keys.size() + 1);  // expand to include geometry

  property_keys.insert("geometry");
  properties.names() = property_keys;

  geojsonsf::geojson_properties::sort_property_names(properties, property_keys);

  properties["geometry"] = lst;

  geojsonsf::geojson_properties::setup_property_vectors(property_types, properties, wkt_objects);
  geojsonsf::geojson_properties::fill_property_vectors(doc_properties, property_types, properties, row_index);

  Rcpp::IntegerVector nv = Rcpp::seq(1, wkt_objects);
  properties.attr("class") = Rcpp::CharacterVector::create("data.frame");
  properties.attr("wkt_column") = "geometry";
  properties.attr("row.names") = nv;

  return properties;
}

// [[Rcpp::export]]
Rcpp::List rcpp_geojson_to_wkt(Rcpp::StringVector geojson) {

  // iterate over the geojson
  R_xlen_t n = geojson.size();
	R_xlen_t wkt_objects = 0;  // keep track of number of objects
	R_xlen_t coord_dim = 0;    // for correctly setting the DIM XYZM attributes
	R_xlen_t row_index;

  // Attributes to keep track of along the way
  //std::unordered_set< std::string > geometry_types = start_geometry_types();
  std::unordered_set< std::string > geometry_types;
  std::unordered_set< std::string > property_keys;   // storing all the 'key' values from 'properties'
  std::unordered_map< std::string, std::string> property_types;

  Document doc_properties;    // Document to store the 'properties'
  doc_properties.SetObject();
  Rcpp::List sfc(n);
  R_xlen_t geo_ele;

  for (geo_ele = 0; geo_ele < n; geo_ele++) {
    sfc[geo_ele] = geojson_to_wkt(
    	geojson[geo_ele], geometry_types, wkt_objects, property_keys,
    	doc_properties, property_types, coord_dim
  	);
  }

  Rcpp::List res = construct_wkt(wkt_objects, sfc, geometry_types, coord_dim);
  Rcpp::List wkt = construct_wkt_df(
  	res, property_keys, property_types, doc_properties, wkt_objects, row_index, coord_dim
  	);

  return wkt;
}

