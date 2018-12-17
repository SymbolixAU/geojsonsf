
#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"

#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/utils/where/where.hpp"
#include "geojsonsf/writers/writers.hpp"
#include "geojsonsf/geometrycollection/geometrycollection.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"


template< typename Writer >
void write_geometry(Writer& writer, SEXP sfg, Rcpp::CharacterVector& cls, int& digits ) {

	std::string geom_type;
	geom_type = cls[1];

	int sfglength = geojsonsf::utils::get_sexp_length( sfg );

	if (sfglength == 0) {
		writer.Null();
	} else {

		bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
		if ( isnull ) {
			writer.Null();
		} else {
			geojsonsf::writers::begin_geojson_geometry(writer, geom_type);
			write_geojson(writer, sfg, geom_type, cls, digits );
			geojsonsf::writers::end_geojson_geometry( writer, geom_type );
		}
	}
}

template< typename Writer >
void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type, Rcpp::CharacterVector& cls, int& digits ) {

	if (geom_type == "POINT") {
		geojsonsf::writers::points_to_geojson( writer, sfg, digits );
	} else {
		Rcpp::stop("df unknown geometry");
	}
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_df_to_geojson_atomise(
		Rcpp::DataFrame& df,
		Rcpp::StringVector& geometry_columns,
		int& digits) {

	size_t n_cols = df.ncol();
	size_t n_rows = df.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = df.names();

	Rcpp::StringVector geojson( n_rows );


	size_t n_geometry_columns = geometry_columns.size();
	Rcpp::List geometry_vectors( n_geometry_columns );

	size_t n_properties = n_cols - n_geometry_columns;
	Rcpp::StringVector property_names( n_properties );

	for ( i = 0; i < n_geometry_columns; i++ ) {
		Rcpp::String this_geometry = geometry_columns[i];
		geometry_vectors[i] = df[ this_geometry ];
	}

	std::string dim = geojsonsf::utils::make_dimension( n_geometry_columns );
	Rcpp::CharacterVector cls = Rcpp::CharacterVector::create( dim , "POINT", "sfg");

	int property_counter = 0;
	for (int i = 0; i < df.length(); i++) {

		Rcpp::String this_column = column_names[i];
		int idx = geojsonsf::utils::where::where_is( this_column, geometry_columns );

		if ( idx == -1 ) {  // i.e. it's not in the vector

			property_names[property_counter] = column_names[i];
			property_counter++;
		}
	}


	for( i = 0; i < n_rows; i++ ) {

		rapidjson::StringBuffer sb;
		rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

		if ( n_properties > 0 ) {
			writer.StartObject();
			geojsonsf::writers::start_features( writer );
			geojsonsf::writers::start_properties( writer );

			writer.StartObject();

			// properties first, then sfc
			for( j = 0; j < n_properties; j++ ) {
				const char *h = property_names[ j ];

				SEXP this_vec = df[ h ];

				jsonify::writers::write_value( writer, h );
				jsonify::dataframe::dataframe_cell( writer, this_vec, i, -1);
			}
			writer.EndObject();
		}

		// now geometries
		if( n_properties > 0 ) {
			writer.String("geometry");
		}

		Rcpp::NumericVector geom( n_geometry_columns );
		for ( j = 0; j < n_geometry_columns; j++ ) {
			Rcpp::NumericVector this_geometry_vector = geometry_vectors[j];
			geom[j] = this_geometry_vector[i];
		}
		SEXP sfg = geom;
		write_geometry( writer, sfg, cls, digits );

		if( n_properties > 0 ) {
			writer.EndObject();
		}
		geojson[i] = sb.GetString();
	}

	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_df_to_geojson(
		Rcpp::DataFrame& df,
		Rcpp::StringVector& geometry_columns,
		int& digits ) {

	rapidjson::StringBuffer sb;
	rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

	size_t n_cols = df.ncol();
	size_t n_rows = df.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = df.names();

	// the sfc_POINT
	size_t n_geometry_columns = geometry_columns.size();
	Rcpp::List geometry_vectors( n_geometry_columns );

	size_t n_properties = n_cols - n_geometry_columns;
	Rcpp::StringVector property_names( n_properties );

	for ( i = 0; i < n_geometry_columns; i++ ) {
		Rcpp::String this_geometry = geometry_columns[i];
		geometry_vectors[i] = df[ this_geometry ];
	}

	std::string dim = geojsonsf::utils::make_dimension( n_geometry_columns );
	Rcpp::CharacterVector cls = Rcpp::CharacterVector::create( dim , "POINT", "sfg");

	int property_counter = 0;

	for ( int i = 0; i < df.length(); i++ ) {

		Rcpp::String this_column = column_names[i];
		int idx = geojsonsf::utils::where::where_is( this_column, geometry_columns );

		if ( idx == -1 ) {  // i.e. it's not in the vector
			property_names[property_counter] = column_names[i];
			property_counter++;
		}
	}

	writer.StartObject();
	geojsonsf::writers::start_feature_collection( writer );

	writer.StartArray();

	for( i = 0; i < n_rows; i++ ) {

		writer.StartObject();

		geojsonsf::writers::start_features( writer );
		geojsonsf::writers::start_properties( writer );
		writer.StartObject();
		// properties first, then sfc

		for( j = 0; j < n_properties; j++ ) {
			const char *h = property_names[ j ];
			SEXP this_vec = df[ h ];

			jsonify::writers::write_value( writer, h );
			jsonify::dataframe::dataframe_cell( writer, this_vec, i, -1 );
		}
		writer.EndObject();

		writer.String("geometry");

		Rcpp::NumericVector geom( n_geometry_columns );
		for ( j = 0; j < n_geometry_columns; j++ ) {
			Rcpp::NumericVector this_geometry_vector = geometry_vectors[j];
			geom[j] = this_geometry_vector[i];
		}
		SEXP sfg = geom;
		write_geometry( writer, sfg, cls, digits );

		writer.EndObject();
	}

	writer.EndArray();
	writer.EndObject();

	Rcpp::StringVector geojson = sb.GetString();
	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}
