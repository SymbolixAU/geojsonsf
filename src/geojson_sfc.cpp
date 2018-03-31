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
	if (geom_type == "GeometryCollection") {
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

	// TODO:
	// - if it's all LINESTRINGS, this can be 'sfc_LINESTRING'...
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


Rcpp::List construct_sfc(int& sfg_objects,
                         Rcpp::List& sf,
                         Rcpp::NumericVector& bbox,
                         std::set< std::string >& geometry_types) {

	Rcpp::List sfc_output(sfg_objects);
	std::string geom_attr;

	//Rcpp::List lvl1 = sf[0];
	//Rcpp::List lvl2 = lvl1[0];
	//Rcpp::Rcout << "debug: sfc length: " << sf.length() << std::endl;
	//Rcpp::Rcout << "debug: lvl1 length: " << lvl1.length() << std::endl;
	//Rcpp::Rcout << "debug: lvl2 length: " << lvl2.length() << std::endl;
	Rcpp::Rcout << "sf length: " << sf.length() << std::endl;  // 1 for object, > 1 for array

	int counter = 0;
	//for (int j = 0; j < sf.length(); j++ ) {

		Rcpp::List lvl1 = sf[0];
		//Rcpp::Rcout << "lvl1 length: " << lvl1.length() << std::endl;

		for (int i = 0; i < sf.length(); i++) {

			//Rcpp::List ele = sf[i];  // going one level deeper becase we are working on a StringVector
			Rcpp::List ele = lvl1[i];
			Rcpp::List ele2 = ele[0];

			if (Rf_isNull(ele2.attr("geo_type"))){

				geom_attr = "GEOMETRY";

				sfc_output[counter] = ele[0];
				counter++;

			} else {

				//Rcpp::List fele = ele[0];
				std::string tmp_attr = ele2.attr("geo_type");
				geom_attr = tmp_attr;

				Rcpp::Rcout << "tmp_attr: " << geom_attr << std::endl;

				if (geom_attr == "FEATURECOLLECTION") {
					// 2 level sdeep

					for (int k = 0; k < ele2.size(); k++) {
					  Rcpp::List lvl2 = ele2[k];
						//Rcpp::List lvl3 = lvl2[0];
						//sfc_output[counter] = lvl1[0];
						sfc_output[counter] = lvl2[0];
						counter++;
					}

				} else if (geom_attr == "FEATURE" ) {

					//Rcpp::List lvl2 = ele2[0];
					//Rcpp::List lvl3 = lvl2[0];
					sfc_output[counter] = ele2[0];
					counter++;
				}
			}
		}
	//}

	std::string gt = "GEOMETRY";
	attach_sfc_attributes(sfc_output, gt, bbox, geometry_types);

	return sfc_output;
}
