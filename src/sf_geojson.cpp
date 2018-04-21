#include "geojsonsf.h"
#include "geojson_wkt.h"
#include "sf_geojson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <Rcpp.h>
using namespace Rcpp;

template <int RTYPE>
Rcpp::CharacterVector sfClass(Vector<RTYPE> v) {
	return v.attr("class");
}

Rcpp::CharacterVector getSfClass(SEXP sf) {
	switch( TYPEOF(sf) ) {
	case REALSXP:
		return sfClass<REALSXP>(sf);
	case VECSXP:
		return sfClass<VECSXP>(sf);
	case INTSXP:
		return sfClass<INTSXP>(sf);
	default: Rcpp::stop("unknown sf type");
	}
	return "";
}


void get_column_type(Rcpp::List& sf, Rcpp::StringVector& property_names,
                     Rcpp::StringVector& column_types) {

	//int counter = 0;
	//for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {
	for (int i = 0; i < property_names.size(); i++) {

		Rcpp::String col = property_names[i];
		SEXP vec = sf[col];

		switch(TYPEOF(vec)) {
		case REALSXP:
			//Rcpp::Rcout << "REAL Number" << std::endl;
			column_types[i] = "Number";
			break;
		//case VECSXP:
		//	Rcpp::Rcout << "Number" << std::endl;
		//	break;
		case INTSXP:
			//Rcpp::Rcout << "INT Number" << std::endl;
			column_types[i] = "Number";
			break;
		case LGLSXP:
			//Rcpp::Rcout << "LGL Logical" << std::endl;
			column_types[i] = "Logical";
			break;
		default: {
				//Rcpp::Rcout << "default: String" << std::endl;
				column_types[i] = "String";
				break;
		}
		}
	}
}

void begin_geojson_geometry(Rcpp::String& geojson, std::string& geom_type) {
    Rcpp::List sfc;
	  begin_geojson_geometry(geojson, sfc, geom_type);
}

void begin_geojson_geometry(Rcpp::String& geojson, Rcpp::List& sfc, std::string& geom_type) {
	//os << "{\"type\" : ";
	geojson += "{\"type\":";
	if (geom_type == "POINT") {
 		//os <<  "\"Point\" , \"coordinates\" : ";
 		geojson +=  "\"Point\",\"coordinates\":";
	} else if (geom_type == "MULTIPOINT") {
		//os << "\"MultiPoint\" , \"coordinates\" : [";
		geojson += "\"MultiPoint\",\"coordinates\":[";
	} else if (geom_type == "LINESTRING") {
		//os << "\"LineString\" , \"coordinates\" : [";
		geojson += "\"LineString\",\"coordinates\":[";
	} else if (geom_type == "MULTILINESTRING") {
		//os << "\"MultiLineString\" , \"coordinates\" : [[";
		geojson += "\"MultiLineString\",\"coordinates\":[[";
	} else if (geom_type == "POLYGON") {
		//os << "\"Polygon\" , \"coordinates\" : [[";
    geojson += "\"Polygon\",\"coordinates\":[[";
	} else if (geom_type == "MULTIPOLYGON") {
		//os << "\"MultiPolygon\" , \"coordinates\" : [[[";
		geojson += "\"MultiPolygon\",\"coordinates\":[[[";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		//add_geometrycollection_to_stream(os, sfc);
		//os << "\"GeometryCollection\" , \"geometries\" : [";
		geojson += "\"GeometryCollection\",\"geometries\":[";
	}
}

void end_geojson_geometry(Rcpp::String& geojson, std::string& geom_type) {
	if (geom_type == "POINT") {
		//os << "}";
		geojson += "}";
	} else if (geom_type == "MULTIPOINT") {
		//os << "]}";
		geojson += "]}";
	} else if (geom_type == "LINESTRING") {
		//os << "]}";
		geojson += "]}";
	} else if (geom_type == "MULTILINESTRING") {
		//os << "]]}";
		geojson += "]]}";
	} else if (geom_type == "POLYGON") {
		//os << "]]}";
		geojson += "]]}";
	} else if (geom_type == "MULTIPOLYGON") {
		//os << "]]]}";
		geojson += "]]]}";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		//os << "]}";
		geojson += "]}";
	}
}

void coord_separator(Rcpp::String& geojson, int i, int n) {
	if (i < (n - 1) ) {
		geojson += ",";
	}
}

void line_separator_geojson(Rcpp::String& geojson, int i, int n) {
	if (i < (n - 1) ) {
		geojson += "],[";
	}
}

void polygon_separator_geojson(Rcpp::String& geojson, int i, int n) {
	if (i < (n - 1) ) {
		geojson += "]],[[";
	}
}

void add_lonlat_to_stream(Rcpp::String& geojson, Rcpp::NumericVector& points) {

	points.attr("dim") = Dimension(points.size() / 2, 2);
	Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix >(points);

	for (int i = 0; i < m.nrow(); i++) {
		geojson += "[";
		geojson += m(i,0);
		geojson += ",";
		geojson += m(i,1);
		geojson += "]";
		coord_separator(geojson, i, m.nrow());
	}
}

void fetch_coordinates(Rcpp::String& geojson, Rcpp::List& sfc, int& object_counter) {

	Rcpp::CharacterVector cls;
	std::string geom_type;

	for (Rcpp::List::iterator it = sfc.begin(); it != sfc.end(); it++) {

		if (object_counter > 0) {
			geojson += ",";
		}

		switch( TYPEOF(*it) ) {
		case VECSXP: {
			Rcpp::List tmp = as<Rcpp::List>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {

				cls = getSfClass(tmp);
				geom_type = cls[1];    // TODO: error handle (there should aways be 3 elements as we're workgin wtih sfg objects)
				begin_geojson_geometry(geojson, tmp, geom_type);
				fetch_coordinates(geojson, tmp, object_counter);
				end_geojson_geometry(geojson, geom_type);
			} else {
				// if no class attribute, go further into the list to try and find one
				fetch_coordinates(geojson, tmp, object_counter);
			}
			object_counter++;
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {
				//Rcpp::Rcout << "debug vector " << std::endl;
				cls = getSfClass(tmp);
				geom_type = cls[1];
				begin_geojson_geometry(geojson, geom_type);
				add_lonlat_to_stream(geojson, tmp);
				end_geojson_geometry(geojson, geom_type);
			} else {
				add_lonlat_to_stream(geojson, tmp);
			}
			object_counter++;
			break;
		}
		case INTSXP: {
			break;
		}
		default: {
			Rcpp::stop("Coordinates could not be found");
		}
		}
	}
}

Rcpp::String add_geometry_to_stream(Rcpp::List& sfg) {

  Rcpp::String geojson;
	int object_counter = 0;
	fetch_coordinates(geojson, sfg, object_counter);

	return geojson;
}

// if only one object with properties, it's a 'feature'
// if only one object without properties, it's a 'geometry'
// if many objects it's a 'featurecollection'


rapidjson::Value get_json_value(SEXP s, rapidjson::Document::AllocatorType& allocator) {
	// TODO:
	// switch on R type and return the rapidjson equivalent
	rapidjson::Value v1;
	switch (TYPEOF(s)) {
	case VECSXP: {
		rapidjson::Value v(rapidjson::kStringType);
		std::string st = as< std::string >(s);
		v.SetString(st.c_str(), allocator);
		return v;
		}
	default: {
		rapidjson::Value v(rapidjson::kStringType);
		std::string st = as< std::string >(s);
		v.SetString(st.c_str(), allocator);
		return v;
	}
	}
	return v1;
}



// TODO:
// For each column construct a JSON array of objects.
// and add the array to the document.
// Then reconstruct each array?
// the arrays will have nrow() members
void vector_to_json(Rcpp::StringVector& sv, std::string& this_type, std::string& this_name) {
	std::string this_value;

	if (this_type == "Number") {
		for (int j = 0; j < sv.size(); j++) {
			sv[j] = "\"" + this_name + "\"" + ":" + sv[j];
		}
	} else if (this_type == "Logical") {
    // convert to lower
    for (int j = 0; j < sv.size(); j++) {
      this_value = sv[j];
	  	transform(this_value.begin(), this_value.end(), this_value.begin(), tolower);
	  	sv[j] = "\"" + this_name + "\"" + ":" + this_value;
    }
	} else {
		for (int j = 0; j < sv.size(); j++) {
			sv[j] = "\"" + this_name + "\"" + ":" + "\"" + sv[j] + "\"";
		}
	}
}

void geometry_vector_to_geojson(Rcpp::StringVector& geometry_json, Rcpp::List& sfc) {
	Rcpp::List sfg(1);
  for (int i = 0; i < sfc.size(); i++) {
  	sfg[0] = sfc[i];
  	geometry_json[i] = add_geometry_to_stream(sfg);
  }
}

// [[Rcpp::export]]
Rcpp::StringMatrix rcpp_sf_to_geojson(Rcpp::List sf) {

	//std::ostringstream os;
	Rcpp::List sf_copy = clone(sf);
	// If it contains properties
	// it's a 'feature' (or featureCollection)
	//
	// if 'atomise', return one object per row

	Rcpp::StringVector column_types(sf_copy.size() - 1);
	//get_column_type(sf, column_types);
	Rcpp::StringVector property_names(sf_copy.size() - 1);

	std::string geom_column = sf_copy.attr("sf_column");
	Rcpp::StringVector col_names = sf_copy.names();

	// fill 'property_names' with all the columns which aren't 'sf_column'
	int property_counter = 0;
	for (int i = 0; i < sf.length(); i++) {
		if (col_names[i] != geom_column) {
			property_names[property_counter] = col_names[i];
			property_counter++;
		}
	}

	get_column_type(sf_copy, property_names, column_types);
	Rcpp::List sfc = sf_copy[geom_column];
	Rcpp::List properties;

	// TODO:
	// construct a StringMatrix with the dimensions of sf
	// then I can fill a column at a time with a string of JSON...
	// then can manipulate it as I want at the end; either atomising or combining
	Rcpp::StringMatrix json_mat(sfc.length(), col_names.size()); // row x cols
	std::string this_name;
	std::string this_type;
	std::string this_value;
	Rcpp::StringVector this_vector;

	for (int i = 0; i < property_names.length(); i++) {
		// iterate the list elements
		this_name = property_names[i];
		this_type = column_types[i];
		this_vector = as< Rcpp::StringVector >(sf_copy[this_name]);

		vector_to_json(this_vector, this_type, this_name);
		//this_vector = "{\"properties\":{" + this_vector + "}";
		json_mat(_, i) = this_vector;

		// TODO: what if there's a mssing element?
	}

	Rcpp::StringVector geometry_json(sfc.length());
	geometry_vector_to_geojson(geometry_json, sfc);
	json_mat(_, (json_mat.ncol() - 1) ) = geometry_json;

	return json_mat;
}


/// DESIGN:
/// should work for both properties & non-property sf
// result vector res(nrow(sf));
// property_columns();
// property_column_types();
// for (i = 0; i < nrow(sf); i++) {
//   for (j = 0; j < ncol(properties); j++){
//      stream each column into "properties": { }
//   }
//   if (ncol(properties) > 0) {
//      needs to be a {"type":"Feature", ...}
//   then create "geometry":{"type" :"geom","coordinates":[]}
// }
// result will be a vector of JSON.
// can combine or keep 'atomic'.
