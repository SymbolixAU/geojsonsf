#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string or vector of GeoJSON, or a URL or file pointing to a geojson file
#'
#' @examples
#'
#' ## character string of GeoJSON
#'
#' ## load 'sf' for print methods
#' # library(sf)
#' geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#' geojson_sfc(geojson)
#'
#'\dontrun{
#' ## GeoJSON at a url
#' myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
#' sf <- geojson_sfc(myurl)
#'}
#'
#' @export
geojson_sfc <- function(geojson) UseMethod("geojson_sfc")


#' @export
geojson_sfc.character <- function(geojson) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sfc(geojson))
	}
	if (is_url(geojson)) {
		return(geojson_sfc(curl::curl(geojson)))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sfc_file(normalizePath(geojson)))
	}
	return(rcpp_geojson_to_sfc(geojson))
}

#' @export
geojson_sfc.connection <- function(geojson) geojson_sfc(read_url(geojson))

#' @export
geojson_sfc.default <- function(geojson) rcpp_geojson_to_sfc(geojson)

#' Geojson to sf
#'
#' Converts GeoJSON to an `sf` object
#'
#' @examples
#'
#' ## character string of GeoJSON
#'
#' ## load 'sf' for print methods
#' # library(sf)
#' geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#' geojson_sf(geojson)
#'
#'
#'\dontrun{
#' ## GeoJSON at a url
#' myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
#' sf <- geojson_sf(myurl)
#'}
#'
#' @inheritParams geojson_sfc
#' @export
geojson_sf <- function(geojson) UseMethod("geojson_sf")


#' @export
geojson_sf.character <- function(geojson) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sf(geojson))
	}
	if (is_url(geojson)) {
		return(geojson_sf(curl::curl(geojson)))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sf_file(normalizePath(geojson)))
	}
	 return(rcpp_geojson_to_sf(geojson))
}

#' @export
geojson_sf.connection <- function(geojson) geojson_sf(read_url(geojson))

#' @export
geojson_sf.default <- function(geojson) rcpp_geojson_to_sf(geojson)


## TODO:
## - atomise - logical?
## -- Return a JSON array of objects
## -- Return an R Vector of objects?

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




is_url <- function(geojson) grepl("^https?://", geojson, useBytes=TRUE)

read_url <- function(con) {
	out <- tryCatch({
		paste0(readLines(con), collapse = "")
	},
	error = function(cond){
		stop("There was an error downloading the geojson")
	},
	finally = {
		close(con)
	})
}

