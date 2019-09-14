
#include "rapidjson/document.h"
#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_validate.hpp"

using namespace rapidjson;

std::string wkt_dim( int n ) {
	switch( n ) {
	case 3: {
		return " Z";
	}
	case 4: {
			return " ZM";
		}
	default: {
		return "";
	}
	}
}

void begin_wkt(std::ostringstream& os, std::string& geom_type, R_xlen_t& coord_dim ) {
	std::string dim = wkt_dim( coord_dim );
	//std::string dim = wkt_dim(0);

  if (geom_type == "Point") {
    os << "POINT" << dim << " (";
  } else if (geom_type == "MultiPoint") {
    os << "MULTIPOINT" << dim << " (";
  } else if (geom_type == "LineString") {
    os << "LINESTRING" << dim << " (";
  } else if (geom_type == "MultiLineString") {
    os << "MULTILINESTRING" << dim << " ((";
  } else if (geom_type == "Polygon") {
    os << "POLYGON" << dim << " ((";
  } else if (geom_type == "MultiPolygon") {
    os << "MULTIPOLYGON" << dim << " (((";
  } else if (geom_type == "GeometryCollection") {
    os << "GEOMETRYCOLLECTION" << dim << " (";
  }
}

void end_wkt(std::ostringstream& os, std::string& geom_type) {

  if (geom_type == "Point") {
    os << ")";
  } else if (geom_type == "MultiPoint") {
    os << ")";
  } else if (geom_type == "LineString") {
    os << ")";
  } else if (geom_type == "MultiLineString") {
    os << "))";
  } else if (geom_type == "Polygon") {
    os << "))";
  } else if (geom_type == "MultiPolygon") {
    os << ")))";
  } else if (geom_type == "GeometryCollection") {
    os << ")";
  }
}

void object_separator(std::ostringstream& os) {
	os << ",";
}

void coord_separator(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << ",";
  }
}

void line_separator_wkt(std::ostringstream& os, int i, int n) {
  if (i < (n - 1) ) {
    os << "),(";
  }
}

void polygon_separate_wkt(std::ostringstream& os, int i, int n) {
	if (i < (n - 1) ) {
    os << ")),((";
	}
}

void add_coordinate_to_wkt_stream(std::ostringstream& os, double coord ) {
	os << coord;
}

void add_lonlat_to_wkt_stream(std::ostringstream& os, double lon, double lat ) {
  os << lon << " " << lat;
}

void point_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim ) {
	R_xlen_t n = coord_array.Size();
	if( coord_dim == 0 ) {
		// coord_dim hasn't been set yet
		// so take the first coordinate to define the dimension

		// iff n == 0; we've got an empty obj.
		// so set coord_dim to 2 so it doens't fail sfg::sfg_dimension() check
	  //coord_dim = n == 0 ? 2 : std::max( coord_dim, n );

	  if( n == 0 ) {
	  	coord_dim = 2;
	  } else if( n > coord_dim ) {
	  	coord_dim = n;
	  }


	} else if ( coord_dim != n ) {
		Rcpp::stop("geojsonsf - different coordinate dimensions found");
	}
	//Rcpp::Rcout << "max coord dim: " << coord_dim << std::endl;
	R_xlen_t i;
	for( i = 0; i < n; i++ ) {
		if( i > 0 ) {
			os << " ";
		}
		add_coordinate_to_wkt_stream( os, coord_array[i].GetDouble() );
	}
  // Rcpp::NumericVector point(2);
  // point[0] = geojsonsf::sfg::get_lon(coord_array);
  // point[1] = geojsonsf::sfg::get_lat(coord_array);
  // add_lonlat_to_wkt_stream(os, point[0], point[1]);
}


void multi_point_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim ) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
    geojsonsf::validate::validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i], coord_dim );
    coord_separator(os, i, n);
  }
}

void line_string_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
  	geojsonsf::validate::validate_array(coord_array[i]);
    point_to_wkt(os, coord_array[i], coord_dim );
    coord_separator(os, i, n);
  }
}

void multi_line_string_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
  	geojsonsf::validate::validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i], coord_dim );
    line_separator_wkt(os, i, n);
  }
}

void polygon_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
  	geojsonsf::validate::validate_array(coord_array[i]);
    line_string_to_wkt(os, coord_array[i], coord_dim );
    line_separator_wkt(os, i, n);
  }
}

void multi_polygon_to_wkt(std::ostringstream& os, const Value& coord_array, R_xlen_t& coord_dim) {
  size_t n = coord_array.Size();
	unsigned int i;
  for (i = 0; i < n; i++) {
  	geojsonsf::validate::validate_array(coord_array[i]);
    polygon_to_wkt(os, coord_array[i], coord_dim);
    polygon_separate_wkt(os, i, n);
  }
}


