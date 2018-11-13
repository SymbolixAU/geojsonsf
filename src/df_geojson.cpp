
#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"

#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/utils/where/where.hpp"
#include "geojsonsf/writers/writers.hpp"
#include "geojsonsf/geometrycollection/geometrycollection.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"


template< typename Writer >
void write_geometry(Writer& writer, SEXP sfg, Rcpp::CharacterVector& cls ) {

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
			write_geojson(writer, sfg, geom_type, cls );
			geojsonsf::writers::end_geojson_geometry( writer, geom_type );
		}
	}
}

template< typename Writer >
void write_geojson(Writer& writer, SEXP sfg, std::string& geom_type, Rcpp::CharacterVector& cls ) {

	if (geom_type == "POINT") {
		geojsonsf::writers::points_to_geojson( writer, sfg );
	} else {
		Rcpp::stop("df unknown geometry");
	}
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_df_to_geojson_atomise(
		Rcpp::DataFrame& df,
		const char* lon,
		const char* lat ) {

	size_t n_cols = df.ncol();
	size_t n_properties = n_cols - 2; // LON & LAT columns
	size_t n_rows = df.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = df.names();
	Rcpp::StringVector property_names(df.size() - 1);

	Rcpp::StringVector geojson( n_rows );

	// the sfc_POINT
	Rcpp::NumericVector nv_lon = df[lon];
	Rcpp::NumericVector nv_lat = df[lat];

	Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XY", "POINT", "sfg");

	int property_counter = 0;
	for (int i = 0; i < df.length(); i++) {
		if ( column_names[i] != lon && column_names[i] != lat ) {
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
				jsonify::dataframe::dataframe_cell( writer, this_vec, i );
			}
			writer.EndObject();
		}

		// now geometries
		if( n_properties > 0 ) {
			writer.String("geometry");
		}

		SEXP sfg = Rcpp::NumericVector::create(nv_lon[i], nv_lat[i]);
		write_geometry( writer, sfg, cls );

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
		Rcpp::DataFrame& sf,
		Rcpp::StringVector& geometry_columns ) {

	// TODO change the lon & lat to be character / string vector specifying the columns to use
	// so we can dynmically use Z&M attributes where appropriate.
	// and change the cls accordingly

	rapidjson::StringBuffer sb;
	rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

	//std::string geom_column = sf.attr("sf_column");

	size_t n_cols = sf.ncol();
	//size_t n_properties = n_cols - 2;  // LON & LAT columns
	size_t n_rows = sf.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = sf.names();

	// the sfc_POINT
	size_t n_geometry_columns = geometry_columns.size();
	Rcpp::List geometry_vectors( n_geometry_columns );

	size_t n_properties = n_cols - n_geometry_columns;
	Rcpp::StringVector property_names( n_properties );

	// Rcpp::Rcout << "n_geometry_columns: " << n_geometry_columns << std::endl;

	for ( i = 0; i < n_geometry_columns; i++ ) {
		Rcpp::String this_geometry = geometry_columns[i];
		geometry_vectors[i] = sf[ this_geometry ];
	}
	// Rcpp::NumericVector nv_lon = sf[lon];
	// Rcpp::NumericVector nv_lat = sf[lat];

	std::string dim = geojsonsf::utils::make_dimension( n_geometry_columns );
	// Rcpp::Rcout << "dim: " << dim << std::endl;
	Rcpp::CharacterVector cls = Rcpp::CharacterVector::create( dim , "POINT", "sfg");

	int property_counter = 0;

	for ( int i = 0; i < sf.length(); i++ ) {

		Rcpp::String this_column = column_names[i];
		int idx = geojsonsf::utils::where::where_is( this_column, geometry_columns );

		// Rcpp::Rcout << "this_column: " << this_column.get_cstring() << std::endl;
		// Rcpp::Rcout << "idx: " << idx << std::endl;

		//if ( column_names[i] != lon && column_names[i] != lat ) {
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
			SEXP this_vec = sf[ h ];

			jsonify::writers::write_value( writer, h );
			jsonify::dataframe::dataframe_cell( writer, this_vec, i );
		}
		writer.EndObject();

		writer.String("geometry");

		//SEXP sfg = Rcpp::NumericVector::create(nv_lon[i], nv_lat[i]);

		Rcpp::NumericVector geom( n_geometry_columns );
		for ( j = 0; j < n_geometry_columns; j++ ) {
			Rcpp::NumericVector this_geometry_vector = geometry_vectors[j];
			geom[j] = this_geometry_vector[i];
		}
		SEXP sfg = geom;
		write_geometry( writer, sfg, cls );

		writer.EndObject();
	}

	writer.EndArray();
	writer.EndObject();

	Rcpp::StringVector geojson = sb.GetString();
	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}
