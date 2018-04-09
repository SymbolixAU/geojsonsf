#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string or vector of GeoJSON
#'
#' @examples
#' ## load 'sf' for print methods
#' # library(sf)
#' geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#' geojson_sfc(geojson)
#'
#' @export
geojson_sfc <- function(geojson) {
	rcpp_geojson_to_sfc(geojson)
}


#' Geojson to sf
#'
#' Converts GeoJSON to an `sf` object
#'
#' @examples
#'
#' ## load 'sf' for print methods
#' # library(sf)
#' geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#' geojson_sf(geojson)
#'
#' @inheritParams geojson_sfc
#' @export
geojson_sf <- function(geojson){
	rcpp_geojson_to_sf(geojson)
}

#' sf to GeoJSON
#'
#' @export
sf_geojson <- function(sf) UseMethod("sf_geojson")

#' @export
sf_geojson.sf <- function(sf) {
  rcpp_sf_to_geojson(sf)
}

#' @export
sf_geojson.sfc <- function(sf) {
	rcpp_sfc_to_geojson(sf)
}

#' @export
sf_geojson.sfg <- function(sf) {
	rcpp_sfg_to_geojson(sf)
}

sf_geojson.default <- function(sf) stop("Expected an sf object")
