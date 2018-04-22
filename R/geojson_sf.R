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
#' Converts `sf` objects to GeoJSON
#'
#' @param sf simple feature object
#' @param atomise logical
#'
#' @return vector of GeoJSON
#'
#' @examples
#' \dontrun{
#' library(sf)
#' sf <- sf::st_sf(geometry = sf::st_sfc(list(sf::st_point(c(0,0)), sf::st_point(c(1,1)))))
#' sf$id <- 1:2
#' sf_geojson(sf)
#' sf_geojson(sf, atomise = T)
#' }
#'
#' @export
sf_geojson <- function(sf, atomise = FALSE) UseMethod("sf_geojson")

#' @export
sf_geojson.sf <- function(sf, atomise = FALSE) rcpp_sf_to_geojson(sf, atomise)


#' sfc to GeoJSON
#'
#' Converts `sfc` objects to GeoJSON
#'
#' @param sfc simple feature collection object
#'
#' @return vector of GeoJSON
#'
#' @examples
#' \dontrun{
#' library(sf)
#' sf <- sf::st_sfc(list(sf::st_point(c(0,0)), sf::st_point(c(1,1))))
#' sfc_geojson(sf)
#' }
#' @export
sfc_geojson <- function(sfc) UseMethod("sfc_geojson")

#' @export
sfc_geojson.sfc <- function(sf) rcpp_sfc_to_geojson(sf)

sf_geojson.default <- function(sf, atomise = FALSE) stop("Expected an sf object")
sfc_geojson.default <- function(sf) stop("Expected an sfc object")




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

