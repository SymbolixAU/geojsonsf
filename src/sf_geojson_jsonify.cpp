
#include <Rcpp.h>
#include "geojsonsf.h"
#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

// TODO
// - sfc
// - atomize
// - sf (properties)

// #define XYUNKNOWN 0
// #define XY        2
// #define XYZ       3
// #define XYM       3
// #define XYZM      4
//
// void make_dim_divisor(const char *cls, int *d) {
// 	int divisor = 2;
// 	if (strcmp(cls, "XY") == 0)
// 		divisor = XY;
// 	else if (strcmp(cls, "XYZ") == 0)
// 		divisor = XYZ;
// 	else if (strcmp(cls, "XYM") == 0)
// 		divisor = XYM;
// 	else if (strcmp(cls, "XYZM") == 0)
// 		divisor = XYZM;
// 	else
// 		Rcpp::stop("Unknown dimension attribute");
// 	*d = divisor;
// }

template <int RTYPE>
int test_sexp_length(Vector<RTYPE> v) {
	return v.length();
}

int test_get_sexp_length(SEXP s) {
	switch( TYPEOF(s) ) {
	case REALSXP:
		return test_sexp_length<REALSXP>(s);
	case VECSXP:
		return test_sexp_length<VECSXP>(s);
	case INTSXP:
		return test_sexp_length<INTSXP>(s);
	default: Rcpp::stop("unknown sf type");
	}
	return 0;
}

template< typename Writer >
void write_coordinate_string( Writer& writer ) {
	writer.String("coordinates");
}

template< typename Writer >
void begin_geojson_geometry(Writer& writer, std::string& geom_type) {

	//geojson += "{\"type\":";
	writer.StartObject();
	writer.String("type");
	if (geom_type == "POINT") {
		writer.String("Point");
		write_coordinate_string( writer );
	} else if (geom_type == "MULTIPOINT") {
		writer.String("MultiPoint");
		write_coordinate_string( writer );
		writer.StartArray();
	} else if (geom_type == "LINESTRING") {
		writer.String("LineString");
		write_coordinate_string( writer );
		writer.StartArray();
	} else if (geom_type == "MULTILINESTRING") {
		writer.String("MultiLineString");
		write_coordinate_string( writer );
		writer.StartArray();
		writer.StartArray();
	} else if (geom_type == "POLYGON") {
		writer.String("Polygon");
		write_coordinate_string( writer );
		writer.StartArray();
		writer.StartArray();
	} else if (geom_type == "MULTIPOLYGON") {
		writer.String("MultiPolygon");
		write_coordinate_string( writer );
		writer.StartArray();
		writer.StartArray();
		writer.StartArray();
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		writer.String("GeometryCollection");
		writer.String("geometries");
		writer.StartArray();
	}
}

template< typename Writer >
void end_geojson_geometry(Writer& writer, std::string& geom_type) {
	if (geom_type == "POINT") {
		writer.EndObject();
		//geojson += "}";
	} else if (geom_type == "MULTIPOINT") {
		writer.EndArray();
		writer.EndObject();
	} else if (geom_type == "LINESTRING") {
		writer.EndArray();
		writer.EndObject();
	} else if (geom_type == "MULTILINESTRING") {
		writer.EndArray();
		writer.EndArray();
		writer.EndObject();
	} else if (geom_type == "POLYGON") {
		writer.EndArray();
		writer.EndArray();
		writer.EndObject();
	} else if (geom_type == "MULTIPOLYGON") {
		writer.EndArray();
		writer.EndArray();
		writer.EndArray();
		writer.EndObject();
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		writer.EndArray();
		writer.EndObject();
	}
}


template< typename Writer >
void points_to_geojson( Writer& writer, Rcpp::NumericVector& point ) {

	int n = point.size();
	int i;
	writer.StartArray();
	for ( i = 0; i < n; i++ ) {
		writer.Double( point[i] );
	}
	writer.EndArray();
}

template< typename Writer >
void linestring_to_geojson( Writer& writer, Rcpp::NumericMatrix& line ) {
  int i;
	int nrow = line.nrow();
	for ( i = 0; i < nrow; i++ ) {
		Rcpp::NumericVector this_row = line(i, Rcpp::_ );
		points_to_geojson( writer, this_row );
	}
}

template< typename Writer >
void polygon_to_geojson( Writer& writer, Rcpp::List& sfg ) {
	int i;
	int n = sfg.size();
	for ( i = 0; i < n; i++ ) {
		Rcpp::NumericMatrix sfgi = sfg[i];
		linestring_to_geojson( writer, sfgi );
	}
}

template< typename Writer >
void multi_polygon_to_geojson( Writer& writer, Rcpp::List& sfg ) {
	int i;
	int n = sfg.size();
	for ( i = 0; i < n; i++ ) {
		Rcpp::List sfgi = sfg[i];
		polygon_to_geojson( writer, sfgi );
	}
}


template< typename Writer >
void test_write_geojson(Writer& writer, SEXP sfg,
                   std::string& geom_type, Rcpp::CharacterVector& cls ) {

	//geometry_json[i] = add_geometry_to_stream(sfg);
	if (geom_type == "POINT") {

		Rcpp::NumericVector point = as< Rcpp::NumericVector >( sfg );
		points_to_geojson( writer, point );

	} else if (geom_type == "MULTIPOINT") {

		Rcpp::NumericMatrix multipoint = as< Rcpp::NumericMatrix >( sfg );
		linestring_to_geojson( writer, multipoint );

	} else if (geom_type == "LINESTRING") {
		Rcpp::NumericMatrix line = as< Rcpp::NumericMatrix >( sfg );
		linestring_to_geojson( writer, line );

	} else if (geom_type == "MULTILINESTRING") {

		Rcpp::List multiline = as< Rcpp::List >( sfg );
		polygon_to_geojson( writer, multiline );

	} else if (geom_type == "POLYGON") {

		Rcpp::List polygon = as< Rcpp::List >(sfg);
		polygon_to_geojson( writer, polygon );

	} else if (geom_type == "MULTIPOLYGON") {

		Rcpp::List multipolygon = as< Rcpp::List >( sfg );
		multi_polygon_to_geojson( writer, multipolygon );

	} else if (geom_type == "GEOMETRYCOLLECTION") {

		Rcpp::List gc = as<Rcpp::List>(sfg);
		Rcpp::List sfgi(1);
		for (int i = 0; i < gc.size(); i++) {
			sfgi[0] = gc[i];
			//make_gc_type(geojson, sfgi, geom_type, cls);
			//coord_separator(geojson, i, gc.size());
		}
	}
}

template< typename Writer >
void write_geometry(Writer& writer, Rcpp::List& sfc, int i) {

	SEXP sfg = sfc[ i ];

	std::string geom_type;
	Rcpp::CharacterVector cls = getSfClass(sfg);
	Rcpp::String g = cls[1];
	geom_type = g;

	// int dim_divisor;
	// make_dim_divisor( cls[0], &dim_divisor );
	// Rcpp::Rcout << "divisor: " << dim_divisor << std::endl;

	// need to keep track of GEOMETRYCOLLECTIONs so we can correctly close them
	bool isGeometryCollection = (geom_type == "GEOMETRYCOLLECTION") ? true : false;

	int sfglength = test_get_sexp_length(sfg);

	if (sfglength == 0) {
		//geojson += "null";
		writer.Null();
	} else {
		begin_geojson_geometry(writer, geom_type);
		test_write_geojson(writer, sfg, geom_type, cls );

		geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
		end_geojson_geometry(writer, geom_type);
	}
}



// [[Rcpp::export]]
Rcpp::StringVector test_sf_to_json( Rcpp::DataFrame& sf ) {
	rapidjson::StringBuffer sb;
	rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

	std::string geom_column = sf.attr("sf_column");

	size_t n_cols = sf.ncol();
	size_t n_properties = n_cols - 1;
	size_t n_rows = sf.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = sf.names();
	Rcpp::StringVector property_names(sf.size() - 1);

	int property_counter = 0;
	for (int i = 0; i < sf.length(); i++) {
		if (column_names[i] != geom_column) {
			property_names[property_counter] = column_names[i];
			property_counter++;
		}
	}

	writer.StartObject();
	writer.String("type");
	writer.String("FeatureCollection");
	writer.String("features");

	writer.StartArray();

	for( i = 0; i < n_rows; i++ ) {
		writer.StartObject();

		writer.String("type");
		writer.String("Feature");
		writer.String("properties");

		writer.StartObject();

		for( j = 0; j < n_properties; j++ ) {

			// TODO( do properties first, then sfc );

			const char *h = property_names[ j ];

			SEXP this_vec = sf[ h ];

			jsonify::writers::write_value( writer, h );
			jsonify::dataframe::dataframe_cell( writer, this_vec, i );
		}

		writer.EndObject();

		// now do property column
		writer.String("geometry");
		// writer.StartObject();

		Rcpp::List sfc = sf[ geom_column ];
		write_geometry( writer, sfc, i );

		// writer.EndObject();

	}

	writer.EndArray();
	writer.EndObject();

	return jsonify::utils::finalise_json( sb );
}
