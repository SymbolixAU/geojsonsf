
#include <Rcpp.h>
#include "geojsonsf/geojsonsf.h"

#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/writers/writers.hpp"
#include "geojsonsf/geometrycollection/geometrycollection.hpp"

#include "geojsonsf/write_geojson.hpp"

#include "geojsonsf/geometries/sizes.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

template< typename Writer >
void write_geometry(Writer& writer, Rcpp::List& sfc, int i) {

	SEXP sfg = sfc[ i ];

	std::string geom_type;
	Rcpp::CharacterVector cls = geojsonsf::getSfClass(sfg);
	geom_type = cls[1];

	// need to keep track of GEOMETRYCOLLECTIONs so we can correctly close them
	bool isGeometryCollection = (geom_type == "GEOMETRYCOLLECTION") ? true : false;

	int sfglength = geojsonsf::utils::get_sexp_length( sfg );

	if (sfglength == 0) {
		writer.Null();
	} else {

		bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
		if ( isnull ) {
			writer.Null();
		} else {

			geojsonsf::writers::begin_geojson_geometry( writer, geom_type );
			write_geojson( writer, sfg, geom_type, cls );

			geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
			geojsonsf::writers::end_geojson_geometry( writer, geom_type );
		}
	}
}

/*
 * for down-casting MULTI objects
 */
template< typename Writer >
void write_geometry(Writer& writer, Rcpp::List& sfc, int i, int geometry,
                    std::string& geom_type, Rcpp::CharacterVector& cls ) {

	SEXP sfg = sfc[ i ];

	std::string downcast_geometry;

	// TODO( if MULTI* - extract the 'geoemtry' looped element )
	if ( geom_type == "MULTIPOINT") {
		downcast_geometry = "POINT";
	} else if ( geom_type == "MULTILINESTRING" ) {
		downcast_geometry = "LINESTRING";
	} else if ( geom_type == "MULTIPOLYGON" ) {
		downcast_geometry = "POLYGON";
	} else {
		downcast_geometry = geom_type;
	}

	// need to keep track of GEOMETRYCOLLECTIONs so we can correctly close them
	bool isGeometryCollection = (geom_type == "GEOMETRYCOLLECTION") ? true : false;

	int sfglength = geojsonsf::utils::get_sexp_length( sfg );

	if (sfglength == 0) {
		writer.Null();
	} else {

		bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
		if ( isnull ) {
			writer.Null();
		} else {

			geojsonsf::writers::begin_geojson_geometry( writer, downcast_geometry );
			write_geojson( writer, sfg, geom_type, cls, geometry );

			geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
			geojsonsf::writers::end_geojson_geometry( writer, downcast_geometry );
		}
	}
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sfc_to_geojson( Rcpp::List& sfc ) {
	// atomise - each row is a separate GeoJSON string

	size_t n_rows = sfc.size();
	size_t i;

	Rcpp::StringVector geojson( n_rows );

	for( i = 0; i < n_rows; i++ ) {

		rapidjson::StringBuffer sb;
		rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

		write_geometry( writer, sfc, i );
		geojson[i] = sb.GetString();
	}
  geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_atomise( Rcpp::DataFrame& sf ) {

	std::string geom_column = sf.attr("sf_column");

	size_t n_cols = sf.ncol();
	size_t n_properties = n_cols - 1;
	size_t n_rows = sf.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = sf.names();
	Rcpp::StringVector property_names(sf.size() - 1);

	Rcpp::StringVector geojson( n_rows );

	int property_counter = 0;
	for (int i = 0; i < sf.length(); i++) {
		if (column_names[i] != geom_column) {
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

				SEXP this_vec = sf[ h ];

				jsonify::writers::write_value( writer, h );
				jsonify::dataframe::dataframe_cell( writer, this_vec, i );
			}
			writer.EndObject();
		}

		// now geometries
		if( n_properties > 0 ) {
		  writer.String("geometry");
		}

		Rcpp::List sfc = sf[ geom_column ];
		write_geometry( writer, sfc, i );

		if( n_properties > 0 ) {
			writer.EndObject();
		}
		geojson[i] = sb.GetString();
	}

	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson( Rcpp::DataFrame& sf, bool reduce_multi = false ) {
	rapidjson::StringBuffer sb;
	rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

	std::string geom_column = sf.attr("sf_column");

	size_t n_cols = sf.ncol();
	size_t n_properties = n_cols - 1;
	size_t n_rows = sf.nrows();
	size_t i, j;
	Rcpp::StringVector column_names = sf.names();
	Rcpp::StringVector property_names(sf.size() - 1);

	std::string geom_type;
	Rcpp::CharacterVector cls;

	int property_counter = 0;
	for (int i = 0; i < sf.length(); i++) {
		if (column_names[i] != geom_column) {
			property_names[property_counter] = column_names[i];
			property_counter++;
		}
	}

	writer.StartObject();
	geojsonsf::writers::start_feature_collection( writer );

	writer.StartArray();

	for( i = 0; i < n_rows; i++ ) {

		Rcpp::List sfc = sf[ geom_column ];
		SEXP sfg = sfc[ i ];

		cls = geojsonsf::getSfClass(sfg);
		geom_type = cls[1];

		if ( reduce_multi && geom_type == "GEOMETRYCOLLECTION" ) {
			Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
		}

		size_t property_multiplier = reduce_multi ? geojsonsf::sizes::geometry_size( sfg, geom_type, cls ) : 1;

		for( int geometry = 0; geometry < property_multiplier; geometry++ ) {

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

			if( reduce_multi ) {
				write_geometry( writer, sfc, i, geometry, geom_type, cls );
			} else {
				//Rcpp::List sfc = sf[ geom_column ];
				write_geometry( writer, sfc, i );
			}

			writer.EndObject();
		}
	}

	writer.EndArray();
	writer.EndObject();

	Rcpp::StringVector geojson = sb.GetString();
	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
	return geojson;
}





