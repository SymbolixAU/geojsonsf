
#include <Rcpp.h>
#include "geojsonsf/geojson/api/sf_api.hpp"

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sfc_to_geojson( Rcpp::List& sfc, int& digits ) {
	return geojsonsf::api::sfc_to_geojson( sfc, digits );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_atomise( Rcpp::DataFrame& sf, int& digits ) {
	return geojsonsf::api::sf_to_geojson_atomise( sf, digits );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson( Rcpp::DataFrame& sf, int& digits ) {
	return geojsonsf::api::sf_to_geojson( sf, digits );
}




// // [[Rcpp::export]]
// Rcpp::StringVector rcpp_sf_to_geojson_downcast( Rcpp::DataFrame& sf ) {
// 	rapidjson::StringBuffer sb;
// 	rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
//
// 	std::string geom_column = sf.attr("sf_column");
//
// 	size_t n_cols = sf.ncol();
// 	size_t n_properties = n_cols - 1;
// 	size_t n_rows = sf.nrows();
// 	size_t i, j;
// 	Rcpp::StringVector column_names = sf.names();
// 	Rcpp::StringVector property_names(sf.size() - 1);
//
// 	size_t property_multiplier = 0;
// 	std::string geom_type;
// 	Rcpp::CharacterVector cls;
//
// 	int property_counter = 0;
// 	for (int i = 0; i < sf.length(); i++) {
// 		if (column_names[i] != geom_column) {
// 			property_names[property_counter] = column_names[i];
// 			property_counter++;
// 		}
// 	}
//
// 	writer.StartObject();
// 	geojsonsf::writers::start_feature_collection( writer );
//
// 	writer.StartArray();
//
// 	for( i = 0; i < n_rows; i++ ) {
//
// 		Rcpp::List sfc = sf[ geom_column ];
// 		SEXP sfg = sfc[ i ];
//
// 		cls = geojsonsf::getSfClass(sfg);
// 		geom_type = cls[1];
//
// 		if (  geom_type == "GEOMETRYCOLLECTION" ) {
// 			Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
// 		}
//
// 		property_multiplier = geojsonsf::sizes::geometry_size( sfg, geom_type, cls );
// 		// Rcpp::Rcout << "property_multiplier: " << property_multiplier << std::endl;
//
// 		for( int geometry = 0; geometry < property_multiplier; geometry++ ) {
//
// 			writer.StartObject();
//
// 			geojsonsf::writers::start_features( writer );
// 			geojsonsf::writers::start_properties( writer );
// 			writer.StartObject();
//
// 			// properties first, then sfc
// 			for( j = 0; j < n_properties; j++ ) {
// 				const char *h = property_names[ j ];
//
// 				SEXP this_vec = sf[ h ];
//
// 				jsonify::writers::write_value( writer, h );
// 				jsonify::dataframe::dataframe_cell( writer, this_vec, i );
// 			}
// 			writer.EndObject();
//
// 			writer.String("geometry");
// 			write_geometry( writer, sfc, i, geometry, geom_type, cls );
//
// 			writer.EndObject();
// 		}
// 	}
//
// 	writer.EndArray();
// 	writer.EndObject();
//
// 	Rcpp::StringVector geojson = sb.GetString();
// 	geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
// 	return geojson;
// }


