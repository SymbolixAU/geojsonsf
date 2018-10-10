
#include <Rcpp.h>
#include "geojsonsf.h"
#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

// TODO
// - sfc
// - atomize
// - sf (properties)


template< typename Writer>
void vector_type(Writer& writer, Rcpp::List& sfc, int i) {

	//Rcpp::Rcout << "sfc size: " << sfc.size() << std::endl;

	SEXP sfg = sfc[ i ];

	Rcpp::CharacterVector cls = getSfClass(sfg);
	Rcpp::String g = cls[1];
	std::string geom_type = g;

	Rcpp::Rcout << "geom type: " << geom_type << std::endl;

	//for (int i = 0; i < sfc.size(); i++) {
		//Rcpp::String geojson;
		//sfg = sfc[i];
		//write_geometry(sfg, geojson);
		//geometry_json[i] = geojson;
	//}
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
		writer.StartObject();

		Rcpp::List sfc = sf[ geom_column ];
		vector_type( writer, sfc, i );

		writer.EndObject();

	}

	writer.EndArray();
	writer.EndObject();

	return jsonify::utils::finalise_json( sb );
}
