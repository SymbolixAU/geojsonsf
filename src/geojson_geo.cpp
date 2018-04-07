#include <Rcpp.h>
using namespace Rcpp;

// Stream an SF object to GeoJSON

void geometry_column_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {

}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson(Rcpp::List sf) {

	// If it contains properties
	// it's a 'feature' (or featureCollection)
	//
	// if 'atomise', return one object per row
	std::ostringstream os;

	geometry_column_to_geojson(os, sf);

	Rcpp::StringVector res = os.str();


	return res;

}


