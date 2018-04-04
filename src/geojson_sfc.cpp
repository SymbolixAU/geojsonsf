#include <Rcpp.h>
#include "geojsonsf.h"

using namespace Rcpp;

void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& point) {
  //xmin, ymin, xmax, ymax
  bbox[0] = std::min(point[0], bbox[0]);
  bbox[2] = std::max(point[0], bbox[2]);

  bbox[1] = std::min(point[1], bbox[1]);
  bbox[3] = std::max(point[1], bbox[3]);
}


std::string attach_class(Rcpp::List& sfc, std::string geom_type,
                          std::set< std::string >& geometry_types) {

  std::string geometry_class;
  if (geom_type == "GEOMETRYCOLLECTION") {
    geometry_class = "GEOMETRYCOLLECTION";
  } else {

    if (geometry_types.size() > 1) {
      geometry_class = "GEOMETRY";
    } else {

      std::set<std::string>::iterator iter = geometry_types.begin();
    	// It will move forward the passed iterator by passed value
    	//std::advance(iter, 1);
    	std::string type = *geometry_types.begin();
    	//std::cout << "debug: type " << type << std::endl;
    	transform(type.begin(), type.end(), type.begin(), toupper);
    	geometry_class = type;
    }
  }
  return geometry_class;
}

void attach_sfc_attributes(Rcpp::List& sfc, std::string& type,
                           Rcpp::NumericVector& bbox,
                           std::set< std::string >& geometry_types) {

  std::string geometry_class = attach_class(sfc, type, geometry_types);
  sfc.attr("class") = Rcpp::CharacterVector::create("sfc_" + geometry_class, "sfc");

  double prec = 0;
  int n_empty = 0;

  // attribute::classes
  //Rcpp::List sfc_attr = Rcpp::List::create(Named("classes") = sfc_classes);
  //sfc.attr("classes") = sfc_classes;

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

std::set< std::string> start_geometry_types() {
  std::set< std::string> geometry_types;
  return geometry_types;
}

/*
Rcpp::StringVector start_sfc_classes(size_t collectionCount) {
	Rcpp::StringVector sfc_classes(collectionCount);
	return sfc_classes;
}
*/

void fetch_geometries(Rcpp::List& sf, Rcpp::List& res, int& sfg_counter) {

  std::string geom_attr;

  for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {

    int x = TYPEOF(*it);

    switch( TYPEOF(*it) ) {
    case VECSXP: {
      Rcpp::List tmp = as<Rcpp::List>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        fetch_geometries(tmp, res, sfg_counter);
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        // TODO:
        // handle missing geo_type in vector
				Rcpp::stop("Geometry could not be determined");
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector tmp = as<Rcpp::IntegerVector>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        // TODO:
        //handle missing geo_type in vector
        Rcpp::stop("Geometry could not be determined");
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    default: {
      Rcpp::stop("Geometry could not be determined");
    }
    }
  }
}




Rcpp::List construct_sfc(int& sfg_objects,
                         Rcpp::List& sf,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {

  Rcpp::List sfc_output(sfg_objects);
  std::string geom_attr;

  int sfg_counter = 0;

  fetch_geometries(sf, sfc_output, sfg_counter);
  attach_sfc_attributes(sfc_output, geom_attr, bbox, geometry_types);

  return sfc_output;
}


