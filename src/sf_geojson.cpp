#include "geojson_wkt.h"

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

// Stream an SF object to GeoJSON
void begin_geojson_geometry(std::ostringstream& os, std::string& geom_type) {
	os << "{\"type\" : ";
	if (geom_type == "POINT") {
		os <<  "\"Point\" , \"coordinates\" : ";
	} else if (geom_type == "MULTIPOINT") {
		os << "\"MultiPoint\" , \"coordinates\" : [";
	} else if (geom_type == "LINESTRING") {
		os << "\"LineString\" , \"coordinates\" : [";
	} else if (geom_type == "MULTILINESTRING") {
		os << "\"MultiLineString\" , \"coordinates\" : [[";
	} else if (geom_type == "POLYGON") {
		os << "\"Polygon\" , \"coordinates\" : [[";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "\"MultiPolygon\" , \"coordinates\" : [[[";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		os << "\"GeometryCollection\" , \"geometries\" : [";
	}
}

void end_geojson_geometry(std::ostringstream& os, std::string& geom_type) {
	if (geom_type == "POINT") {
		os << "}";
	} else if (geom_type == "MULTIPOINT") {
		os << "]}";
	} else if (geom_type == "LINESTRING") {
		os << "]}";
	} else if (geom_type == "MULTILINESTRING") {
		os << "]]}";
	} else if (geom_type == "POLYGON") {
		os << "]]}";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "]]]}";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		os << "]}";
	}
}

void add_lonlat_to_stream(std::ostringstream& os, Rcpp::NumericVector& points) {

  //Rcpp::Rcout << "Debug point size: " << points.size() << std::endl;
	// a matrix is a vector with a dimension attribute...

	//Rcpp::Rcout << "debug: points size: " << points.size() << std::endl;
	//Rcpp::Rcout << points << std::endl;

	points.attr("dim") = Dimension(points.size() / 2, 2);
	Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix >(points);

	//Rcpp::Rcout << "debug: m rows: " << m.nrow() << std::endl;
	//Rcpp::Rcout << "debug: m cols: " << m.ncol() << std::endl;

	for (int i = 0; i < m.nrow(); i++) {
		os << "[" << m(i, 0) << "," << m(i, 1) << "]";
		coord_separator(os, i, m.nrow());
	}
}

void fetch_coordinates(std::ostringstream& os, Rcpp::List& sfc) {

	//Rcpp::Rcout << "debug: sfc size: " << sfc.size() << std::endl;
	//os << "[";
	//bracket_counter++;
	//Rcpp::Rcout << "type sfc: " << TYPEOF(sfc) << std::endl;
	Rcpp::CharacterVector cls;
	std::string geom_type;

	for (Rcpp::List::iterator it = sfc.begin(); it != sfc.end(); it++) {
		switch( TYPEOF(*it) ) {
		case VECSXP: {
			Rcpp::List tmp = as<Rcpp::List>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {
				cls = getSfClass(tmp);
				geom_type = cls[1];
				begin_geojson_geometry(os, geom_type);
			  fetch_coordinates(os, tmp);
			  end_geojson_geometry(os, geom_type);
			}
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {
				cls = getSfClass(tmp);
				geom_type = cls[1];
				begin_geojson_geometry(os, geom_type);
			  add_lonlat_to_stream(os, tmp);
			  end_geojson_geometry(os, geom_type);
			}
			break;
		}
		case INTSXP: {
			//Rcpp::IntegerVector tmp = as<Rcpp::IntegerVector>(*it);
			//add_lonlat_to_stream(os, tmp);
			break;
		}
		default: {
			Rcpp::stop("Coordinates could not be found");
		}
	  }
	}
}


void add_geometry_to_stream(std::ostringstream& os, Rcpp::List& sfc) {

	// recurse into list to find 'sfg'
	// each recursion adds a bracket '('
	// need to keep track of closing braces
  fetch_coordinates(os, sfc);
}

void sfg_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {
	Rcpp::CharacterVector cls;
	std::string geom_type;
	Rcpp::List sfci(1);

	//Rcpp::Rcout << "sfc.size; " << sfc.size() << std::endl;

	for (int i = 0; i < sfc.size(); i++) {

		// recurse into each geometry
		// if it's a list, AND has a class/attribute, 'begin GEOJSON string', recurse again to get the vec/matrix/obj
		// if if's not a list, get the obj & 'begin GEOJSON string'
		// - get the obj & convert to GEOJSON
		//
		// move the 'getSfClass' into the recursing bit, 'begin' the stream if the sfg class exists
		// recurse again to get the objects (if it's a list, it will recurse once more)
		// - just need to make sure to close of geometrycollection objects...?
		// keep track of inner-objects? like a counter

			sfci[0] = sfc[i];
			add_geometry_to_stream(os, sfci);
	}
}

void sfc_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {
	sfg_to_geojson(os, sfc);
}

Rcpp::StringVector rcpp_sfg_to_geojson(Rcpp::List sfg) {
	std::ostringstream os;
	sfg_to_geojson(os, sfg);
	return os.str();
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sfc_to_geojson(Rcpp::List sfc) {
	std::ostringstream os;
	sfc_to_geojson(os, sfc);
	return os.str();
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson(Rcpp::List sf) {

	// If it contains properties
	// it's a 'feature' (or featureCollection)
	//
	// if 'atomise', return one object per row
	std::ostringstream os;
	std::string geom_column = sf.attr("sf_column");
	Rcpp::List sfc = sf[geom_column];

	sfc_to_geojson(os, sfc);
	//for (int i = 0; i < sf.size(); i++) {
	//	Rcpp::List sfc = sf[i];
	//	Rcpp::CharacterVector cls_attr = getSfClass(sfc);
	//	add_geometry_to_stream(os, sfc);
	//}

	Rcpp::StringVector res = os.str();

	return res;
}


