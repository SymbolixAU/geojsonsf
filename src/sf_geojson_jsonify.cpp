
#include <Rcpp.h>
#include "geojsonsf.h"
#include "sf_geojson_test.hpp"
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

		// TODO( NULL TEST )
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
void polygon_separator( Writer& writer, int i, int n ) {
	if (i < ( n - 1 ) ) {
		writer.EndArray();
		writer.EndArray();
		writer.StartArray();
		writer.StartArray();
	}
}

template< typename Writer >
void line_separator( Writer& writer, int i, int n) {
	if ( i < ( n - 1 ) ) {
		writer.EndArray();
		writer.StartArray();
	}
}

void number_type( SEXP sfg ) {
	switch( TYPEOF( sfg ) ) {
	case INTSXP: {
		Rcpp::Rcout << "integer" << std::endl;
		break;
	}
	case REALSXP: {
		Rcpp::Rcout << "numeric" << std::endl;
		break;
	}
	}
}

template< typename Writer >
void points_to_geojson( Writer& writer, Rcpp::IntegerVector& point ) {
	int n = point.size();
	int i;
	writer.StartArray();
	for ( i = 0; i < n; i++ ) {
		writer.Int( point[i] );
	}
	writer.EndArray();
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
void points_to_geojson( Writer& writer, SEXP& point ) {
  switch( TYPEOF( point ) ) {
  case INTSXP: {
  	Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( point );
  	points_to_geojson( writer, iv );
  	break;
  }
  case REALSXP: {
  	Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( point );
  	points_to_geojson( writer, nv );
  	break;
  }
  }
}

template< typename Writer >
void linestring_to_geojson( Writer& writer, Rcpp::IntegerMatrix& line ) {
  int i;
	int nrow = line.nrow();
	for ( i = 0; i < nrow; i++ ) {
		Rcpp::IntegerVector this_row = line(i, Rcpp::_ );
		points_to_geojson( writer, this_row );
	}
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
void linestring_to_geojson( Writer& writer, SEXP& line ) {
	switch( TYPEOF( line ) ) {
	case INTSXP: {
		Rcpp::IntegerMatrix iv = Rcpp::as< Rcpp::IntegerMatrix >( line );
		linestring_to_geojson( writer, iv );
		break;
	}
	case REALSXP: {
		Rcpp::NumericMatrix nv = Rcpp::as< Rcpp::NumericMatrix >( line );
		linestring_to_geojson( writer, nv );
		break;
	}
	}
}

template< typename Writer >
void polygon_to_geojson( Writer& writer, Rcpp::List& sfg ) {
	int i;
	int n = sfg.size();
	for ( i = 0; i < n; i++ ) {
		Rcpp::NumericMatrix sfgi = sfg[i];
		linestring_to_geojson( writer, sfgi );
		line_separator( writer, i, n );
	}
}

template< typename Writer >
void multi_polygon_to_geojson( Writer& writer, Rcpp::List& sfg ) {
	int i;
	int n = sfg.size();
	for ( i = 0; i < n; i++ ) {
		Rcpp::List sfgi = sfg[i];
		polygon_to_geojson( writer, sfgi );
		polygon_separator( writer, i, n );
	}
}

template< typename Writer >
void test_write_geojson(Writer& writer, SEXP sfg,
                   std::string& geom_type, Rcpp::CharacterVector& cls ) {

	//number_type( sfg );

	//geometry_json[i] = add_geometry_to_stream(sfg);
	if (geom_type == "POINT") {
		//Rcpp::NumericVector point = Rcpp::as< Rcpp::NumericVector >( sfg );
		points_to_geojson( writer, sfg );

	} else if (geom_type == "MULTIPOINT") {

		//Rcpp::NumericMatrix multipoint = Rcpp::as< Rcpp::NumericMatrix >( sfg );
		linestring_to_geojson( writer, sfg );

	} else if (geom_type == "LINESTRING") {
		//Rcpp::NumericMatrix line = Rcpp::as< Rcpp::NumericMatrix >( sfg );
		linestring_to_geojson( writer, sfg );

	} else if (geom_type == "MULTILINESTRING") {

		Rcpp::List multiline = Rcpp::as< Rcpp::List >( sfg );
		polygon_to_geojson( writer, multiline );

	} else if (geom_type == "POLYGON") {

		Rcpp::List polygon = Rcpp::as< Rcpp::List >(sfg);
		polygon_to_geojson( writer, polygon );

	} else if (geom_type == "MULTIPOLYGON") {

		Rcpp::List multipolygon = Rcpp::as< Rcpp::List >( sfg );
		multi_polygon_to_geojson( writer, multipolygon );

	} else if (geom_type == "GEOMETRYCOLLECTION") {

		Rcpp::List gc = Rcpp::as< Rcpp::List >( sfg );
		Rcpp::List sfgi(1);
		for (int i = 0; i < gc.size(); i++) {
			sfgi[0] = gc[i];
			make_gc_type(writer, sfgi, geom_type, cls);
		}
	}
}

bool is_null_geometry( SEXP& sfg, std::string& geom_type ) {
	int n = test_get_sexp_length( sfg );
	if( geom_type == "POINT" ) {
		Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
		if (ISNAN( nv[0] ) ) {
			return true;
		}
	} else if ( n == 0 ) {
		return true;
	}
	return false;
}

template< typename Writer >
void make_gc_type(Writer& writer, Rcpp::List& sfg,
                  std::string& geom_type, Rcpp::CharacterVector& cls) {

	bool isnull = false;

	for (Rcpp::List::iterator it = sfg.begin(); it != sfg.end(); it++) {

		switch( TYPEOF( *it ) ) {
		case VECSXP: {
			Rcpp::List tmp = Rcpp::as< Rcpp::List >(*it);
			if (!Rf_isNull(tmp.attr("class"))) {

				cls = tmp.attr("class");
				// TODO: error handle (there should aways be 3 elements as we're workgin wtih sfg objects)
				geom_type = cls[1];

				SEXP tst = *it;
				isnull = is_null_geometry( tst, geom_type );
				if (isnull ) {
					//writer.String("geometry");
					writer.Null();
				} else {
					begin_geojson_geometry(writer, geom_type);
					test_write_geojson(writer, tmp, geom_type, cls);
					end_geojson_geometry(writer, geom_type);
				}
			} else {
				make_gc_type(writer, tmp, geom_type, cls);
			}
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = Rcpp::as< Rcpp::NumericVector >( *it );
			if (!Rf_isNull(tmp.attr("class"))) {

				cls = tmp.attr("class");
				geom_type = cls[1];

				SEXP tst = *it;
				isnull = is_null_geometry( tst, geom_type );
				if ( isnull ) {
					//writer.String("geometry");
					writer.Null();
				} else {
					begin_geojson_geometry(writer, geom_type);
					test_write_geojson(writer, tmp, geom_type, cls);
					end_geojson_geometry(writer, geom_type);
				}
			}
			break;
		}
		default: {
			Rcpp::stop("Coordinates could not be found");
		}
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

	int sfglength = test_get_sexp_length( sfg );

	//Rcpp::Rcout << "sfglength: " << sfglength << std::endl;

	if (sfglength == 0) {
		writer.Null();
	} else {

		bool isnull = is_null_geometry( sfg, geom_type );
		if ( isnull ) {
			writer.Null();
		} else {
			begin_geojson_geometry(writer, geom_type);
			test_write_geojson(writer, sfg, geom_type, cls );

			geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
			end_geojson_geometry( writer, geom_type );
		}
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

	  // properties first, then sfc
		for( j = 0; j < n_properties; j++ ) {


			const char *h = property_names[ j ];

			SEXP this_vec = sf[ h ];

			jsonify::writers::write_value( writer, h );
			jsonify::dataframe::dataframe_cell( writer, this_vec, i );
		}

		writer.EndObject();

		// now geometries
		writer.String("geometry");

		Rcpp::List sfc = sf[ geom_column ];
		write_geometry( writer, sfc, i );

		writer.EndObject();
	}

	writer.EndArray();
	writer.EndObject();

	return jsonify::utils::finalise_json( sb );
}
