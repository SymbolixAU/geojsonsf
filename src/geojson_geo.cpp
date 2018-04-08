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
	if (geom_type == "POINT") {
		os << "\"Point\" :";
	} else if (geom_type == "MULTIPOIT") {
		os << "\"MultiPoint\" : [";
	} else if (geom_type == "LINESTRING") {
		os << "\"LineString\" : [";
	} else if (geom_type == "MULTILINESTRING") {
		os << "\"MultiLineString\" : [[";
	} else if (geom_type == "POLYGON") {
		os << "\"Polygon\" : [[";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "\"MultiPolygon\" : [[[";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		os << "\"GeometryCollection\" : [";
	}
}

void end_geojson_geometry(std::ostringstream& os, std::string& geom_type) {
	if (geom_type == "POINT") {
		os << "";
	} else if (geom_type == "MULTIPOINT") {
		os << "]";
	} else if (geom_type == "LINESTRING") {
		os << "]";
	} else if (geom_type == "MULTILINESTRING") {
		os << "]] ";
	} else if (geom_type == "POLYGON") {
		os << "]]";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "]]]";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		os << "]";
	}
}

void add_lonlat_to_stream(std::ostringstream& os, Rcpp::NumericVector& points) {

  //Rcpp::Rcout << "Debug point size: " << points.size() << std::endl;
	// a matrix is a vector with a dimension attribute...

	Rcpp::Rcout << "debug: points size: " << points.size() << std::endl;

	Rcpp::Rcout << points << std::endl;

	points.attr("dim") = Dimension(points.size() / 2, 2);
	Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix >(points);

	Rcpp::Rcout << "debug: m rows: " << m.nrow() << std::endl;
	Rcpp::Rcout << "debug: m cols: " << m.ncol() << std::endl;

	for (int i = 0; i < m.nrow(); i++) {
		os << "[" << m(i, 0) << "," << m(i, 1) << "]";
		coord_separator(os, i, m.nrow());
	}
}

void fetch_coordinates(std::ostringstream& os, Rcpp::List& sfc) {

	//Rcpp::Rcout << "debug: sfc size: " << sfc.size() << std::endl;
	//os << "[";
	//bracket_counter++;

	for (Rcpp::List::iterator it = sfc.begin(); it != sfc.end(); it++) {
		switch( TYPEOF(*it) ) {
		case VECSXP: {
			//Rcpp::Rcout << "debug: list" << std::endl;
			Rcpp::List tmp = as<Rcpp::List>(*it);
				fetch_coordinates(os, tmp);
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
			add_lonlat_to_stream(os, tmp);
			break;
		}
		case INTSXP: {
			Rcpp::IntegerVector tmp = as<Rcpp::IntegerVector>(*it);
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

void sfc_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {
	Rcpp::CharacterVector cls;
	std::string geom_type;

  for (int i = 0; i < sfc.size(); i++) {

  	//Rcpp::List sfci = as< Rcpp::List>(sfc[i]);
  	cls = getSfClass(sfc[i]);

  	Rcpp::Rcout << cls << std::endl;
  	geom_type = cls[1];

  	begin_geojson_geometry(os, geom_type);
  	//add_geometry_to_stream(os, sfc[i]);
  	end_geojson_geometry(os, geom_type);
  }
}

void sfg_to_geojson() {

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


