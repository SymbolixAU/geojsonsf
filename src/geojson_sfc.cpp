#include <Rcpp.h>
#include "geojsonsf.h"
#include "geojson_sfc.h"

void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& point) {
  //xmin, ymin, xmax, ymax
  bbox[0] = std::min(point[0], bbox[0]);
  bbox[2] = std::max(point[0], bbox[2]);

  bbox[1] = std::min(point[1], bbox[1]);
  bbox[3] = std::max(point[1], bbox[3]);
}


std::string attach_class(Rcpp::List& sfc,
                         std::string geom_type,
                         std::unordered_set< std::string >& geometry_types) {

  std::string geometry_class;
  if (geom_type == "GEOMETRYCOLLECTION") {
    geometry_class = "GEOMETRYCOLLECTION";
  } else {

    if (geometry_types.size() > 1) {
      geometry_class = "GEOMETRY";

      Rcpp::StringVector sfc_classes = start_sfc_classes(sfc.size());
      for (int i = 0; i < sfc.size(); i++) {
        SEXP sfci = sfc[i];
        Rcpp::CharacterVector cls = getSfClass(sfci);
        sfc_classes[i] = cls[1];
      }

      // attribute::classes
      sfc.attr("classes") = sfc_classes;

    } else {
      std::string type = *geometry_types.begin();
      transform(type.begin(), type.end(), type.begin(), toupper);
      geometry_class = type;
    }
  }
  return geometry_class;
}

void attach_sfc_attributes(Rcpp::List& sfc,
                           std::string& type,
                           Rcpp::NumericVector& bbox,
                           std::unordered_set< std::string >& geometry_types,
                           int& nempty) {

  std::string geometry_class = attach_class(sfc, type, geometry_types);
  sfc.attr("class") = Rcpp::CharacterVector::create("sfc_" + geometry_class, "sfc");

  double prec = 0;

  // attribute::crs
  Rcpp::List crs = Rcpp::List::create(
  	Rcpp::Named("epsg") = geojsonsf::EPSG,
  	Rcpp::Named("proj4string") = geojsonsf::PROJ4STRING
  	);

  crs.attr("class") = Rcpp::CharacterVector::create("crs");
  sfc.attr("crs") = crs;

  // attribute::precision
  sfc.attr("precision") = prec;

  // attribute::n_empty
  sfc.attr("n_empty") = nempty;

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

void fetch_geometries(Rcpp::List& sf, Rcpp::List& res, int& sfg_counter) {

  std::string geom_attr;

  for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {

    switch( TYPEOF(*it) ) {

    case VECSXP: {
      Rcpp::List tmp = Rcpp::as< Rcpp::List >( *it );
      if(Rf_isNull(tmp.attr("class"))){
        fetch_geometries(tmp, res, sfg_counter);
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector tmp = Rcpp::as< Rcpp::NumericVector >( *it );
      if(Rf_isNull(tmp.attr("class"))) {
        Rcpp::stop("Geometry could not be determined");
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector tmp = Rcpp::as< Rcpp::IntegerVector >( *it );
      if(Rf_isNull( tmp.attr( "class" ) ) ){
        Rcpp::stop("Geometry could not be determined");
      } else {
        res[sfg_counter] = tmp;
        sfg_counter++;
      }
      break;
    }
    case STRSXP: {
    	Rcpp::StringVector tmp = Rcpp::as< Rcpp::StringVector >( *it );
    	if(Rf_isNull( tmp.attr( "class" ) ) ) {
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
                         std::unordered_set< std::string >& geometry_types,
                         int& nempty) {

  Rcpp::List sfc_output( sfg_objects );
  std::string geom_attr;

  int sfg_counter = 0;

  fetch_geometries( sf, sfc_output, sfg_counter );
  attach_sfc_attributes( sfc_output, geom_attr, bbox, geometry_types, nempty );

  return sfc_output;
}


