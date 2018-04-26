#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string or vector of GeoJSON, or a URL or file pointing to a geojson file
#' @param flatten_geometries logical indicating whether to unnest GEOMETRYCOLLECTION rows. see details
#'
#' @details
#' specifying \code{flatten_geometries = TRUE} will expand individual \code{GEOMETRYCOLLECTION}
#' geometries to their own row in the resulting `sf` object. If the geometries are part
#' of a \code{Feature} (i.e., with properties), the properties will be repeated on each row.
#'
#' The \code{GEOMETRYCOLLECTION} information is not kept when using \code{flatten_geometries = TRUE}. Therefore,
#' it is not possible to reconstruct the \code{GEOMETRYCOLLECTION} after unnesting it.
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
#' }
#'
#' @export
geojson_sfc <- function(geojson, flatten_geometries = FALSE) UseMethod("geojson_sfc")


#' @export
geojson_sfc.character <- function(geojson, flatten_geometries = FALSE) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sfc(geojson, flatten_geometries))
	}
	if (is_url(geojson)) {
		return(geojson_sfc(curl::curl(geojson), flatten_geometries))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sfc_file(normalizePath(geojson), flatten_geometries))
	}
	return(rcpp_geojson_to_sfc(geojson, flatten_geometries))
}

#' @export
geojson_sfc.connection <- function(geojson, flatten_geometries = FALSE) geojson_sfc(read_url(geojson), flatten_geometries)

#' @export
geojson_sfc.default <- function(geojson, flatten_geometries = FALSE) rcpp_geojson_to_sfc(geojson, flatten_geometries)

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
#' @inherit geojson_sfc params details
#' @export
geojson_sf <- function(geojson, flatten_geometries = FALSE) UseMethod("geojson_sf")


#' @export
geojson_sf.character <- function(geojson, flatten_geometries = FALSE) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sf(geojson, flatten_geometries))
	}
	if (is_url(geojson)) {
		return(geojson_sf(curl::curl(geojson), flatten_geometries))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sf_file(normalizePath(geojson), flatten_geometries))
	}
	 return(rcpp_geojson_to_sf(geojson, flatten_geometries))
}

#' @export
geojson_sf.connection <- function(geojson, flatten_geometries = F) geojson_sf(read_url(geojson), flatten_geometries)

#' @export
geojson_sf.default <- function(geojson, flatten_geometries = F) rcpp_geojson_to_sf(geojson, flatten_geometries)


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
sfc_geojson.sfc <- function(sfc) rcpp_sfc_to_geojson(sfc)

sf_geojson.default <- function(sf, atomise = FALSE) stop("Expected an sf object")
sfc_geojson.default <- function(sfc) stop("Expected an sfc object")

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

