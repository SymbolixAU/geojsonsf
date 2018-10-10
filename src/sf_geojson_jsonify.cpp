
#include <Rcpp.h>
#include "geojsonsf.h"
#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

// TODO
// - sfc
// - atomize
// - sf (properties)

#define XYUNKNOWN 0
#define XY        2
#define XYZ       3
#define XYM       3
#define XYZM      4

void make_dim_divisor(const char *cls, int *d) {
	int divisor = 2;
	if (strcmp(cls, "XY") == 0)
		divisor = XY;
	else if (strcmp(cls, "XYZ") == 0)
		divisor = XYZ;
	else if (strcmp(cls, "XYM") == 0)
		divisor = XYM;
	else if (strcmp(cls, "XYZM") == 0)
		divisor = XYZM;
	else
		Rcpp::stop("Unknown dimension attribute");
	*d = divisor;
}

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



void test_write_geojson(Rcpp::String& geojson, SEXP sfg,
                   std::string& geom_type, Rcpp::CharacterVector& cls) {

	//geometry_json[i] = add_geometry_to_stream(sfg);
	if (geom_type == "POINT") {

		Rcpp::NumericVector point = as< Rcpp::NumericVector >(sfg);
		//point_to_geojson(geojson, point);

	} else if (geom_type == "MULTIPOINT") {

		Rcpp::NumericVector multipoint = as<Rcpp::NumericVector>(sfg);
		//multi_point_to_geojson(geojson, multipoint);
	} else if (geom_type == "LINESTRING") {

		Rcpp::NumericVector line = as<Rcpp::NumericVector>(sfg);
		//line_string_to_geojson(geojson, line);
	} else if (geom_type == "MULTILINESTRING") {

		Rcpp::List multiline = as<Rcpp::List>(sfg);
		//multi_line_string_to_geojson(geojson, multiline);
	} else if (geom_type == "POLYGON") {

		Rcpp::List polygon = as<Rcpp::List>(sfg);
		//polygon_to_geojson(geojson, polygon);
	} else if (geom_type == "MULTIPOLYGON") {

		Rcpp::List multipolygon = as<Rcpp::List>(sfg);
		//multi_polygon_to_geojson(geojson, multipolygon);
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



template< typename Writer>
void vector_type(Writer& writer, Rcpp::List& sfc, int i) {

	//Rcpp::Rcout << "sfc size: " << sfc.size() << std::endl;

	SEXP sfg = sfc[ i ];

	Rcpp::CharacterVector cls = getSfClass(sfg);
	Rcpp::String g = cls[1];
	std::string geom_type = g;

	Rcpp::Rcout << "geom type: " << geom_type << std::endl;

	int dim_divisor;
	make_dim_divisor( cls[0], &dim_divisor );

	Rcpp::Rcout << "divisor: " << dim_divisor << std::endl;

	int sfglength = test_get_sexp_length( sfg );
	Rcpp::Rcout << "length: " << sfglength << std::endl;
	if ( sfglength == 0 ) {
		writer.Null();
	} else {
		// writer.StartObject();

		// writer.EndObject();
	}

	//write_geometry(sfg, geojson);
	//geometry_json[i] = geojson;
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
		vector_type( writer, sfc, i );

		// writer.EndObject();

	}

	writer.EndArray();
	writer.EndObject();

	return jsonify::utils::finalise_json( sb );
}
