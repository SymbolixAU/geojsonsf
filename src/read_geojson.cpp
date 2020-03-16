#include <Rcpp.h>
#include <rapidjson/document.h>

#include <rapidjson/filereadstream.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geojson/geojson_to_sf.hpp"
#include "geojsonsf/sf/sfc/geojson_sfc.hpp"
#include "geojsonsf/sf/sfg/geojson_sfg.hpp"
#include "geojsonsf/geojson/geojson_properties.hpp"
#include <fstream>

// Rcpp::StringVector buffer_string(std::string file) {
//   std::ifstream ifs(file);
//   std::stringstream buffer;
//   buffer << ifs.rdbuf();
//   return buffer.str();
// }


rapidjson::Document buffer_string( const char* file, const char* mode, int buffer_size = 1024 ) {

	FILE* fp = fopen(file, mode );
	//char readBuffer[ buffer_size ];
	//rapidjson::FileReadStream is(fp, readBuffer, sizeof( readBuffer ) );

	// ISO C++ forbids variable length array ‘readBuffer’ [-Wvla]
	// https://stackoverflow.com/a/11379442/5977215
	char *readBuffer = new char[ buffer_size ];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof( readBuffer ) );

	Document d;
	d.ParseStream( is );
	fclose(fp);

	return d;
}

// [[Rcpp::export]]
Rcpp::List rcpp_read_sf_file(
		const char* file,
		const char* mode,
		bool flatten_geometries,
		int buffer_size = 1024
	) {
	rapidjson::Document d = buffer_string( file, mode, buffer_size );
  return geojsonsf::sf::generic_geojson_to_sf( d , flatten_geometries );
}

// [[Rcpp::export]]
Rcpp::List rcpp_read_sfc_file(
		const char* file,
		const char* mode,
		bool flatten_geometries,
		int buffer_size = 1024
	) {
	rapidjson::Document d = buffer_string( file, mode, buffer_size );
	return geojsonsf::sf::create_sfc( d, flatten_geometries);
}


// // [[Rcpp::export]]
// Rcpp::List rcpp_read_sfc_file(std::string file, bool flatten_geometries) {
//   return geojsonsf::sf::create_sfc( buffer_string( file ), flatten_geometries);
// }


// // [[Rcpp::export]]
// Rcpp::List rcpp_read_sf_file(std::string file, bool flatten_geometries) {
//   return geojsonsf::sf::generic_geojson_to_sf(buffer_string(file), flatten_geometries);
// }

