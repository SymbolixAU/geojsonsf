#include <Rcpp.h>
#include "geojsonsf.h"

using namespace Rcpp;


void attach_sfc_attributes(Rcpp::List& sfc, Rcpp::StringVector sfc_classes, Rcpp::NumericVector bbox) {

	// TODO:
	// - if it's all LINESTRINGS, this can be 'sfc_LINESTRING'...
	sfc.attr("class") = Rcpp::CharacterVector::create("sfc_GEOMETRY", "sfc");

	double prec = 0;
	int n_empty = 0;

	// attribute::classes
	Rcpp::List sfc_attr = Rcpp::List::create(Named("classes") = sfc_classes);
	sfc.attr("classes") = sfc_classes;

	// attribute::crs
	Rcpp::List crs = Rcpp::List::create(Named("epsg") = geojsonsf::EPSG,
                                     Named("proj4string") = geojsonsf::PROJ4STRING);

	crs.attr("class") = Rcpp::CharacterVector::create("crs");
	sfc.attr("crs") = crs;

	// attribute::precision
	sfc.attr("precision") = prec;

	// attribute::n_empty
	sfc.attr("n_empty") = n_empty;

	// attribute::bbox
	bbox.attr("class") = Rcpp::CharacterVector::create("bbox");
	bbox.attr("names") = Rcpp::CharacterVector::create("xmin", "ymin", "xmax", "ymax");
	sfc.attr("bbox") = bbox;

}

Rcpp::NumericVector start_bbox() {
	Rcpp::NumericVector bbox(4);  // xmin, ymin, xmax, ymax
	bbox(0) = bbox(1) = bbox(2) = bbox(3) = NA_REAL;
	return bbox;
}

Rcpp::StringVector start_sfc_classes(size_t collectionCount) {
	Rcpp::StringVector sfc_classes(collectionCount);
	return sfc_classes;
}
