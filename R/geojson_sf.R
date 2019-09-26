#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string or vector of GeoJSON, or a URL or file pointing to a geojson file
#' @param expand_geometries logical indicating whether to unnest GEOMETRYCOLLECTION rows. see details
#' @param crs coordiante reference system. See Details
#' @param proj4string proj4string. See Details
#' @param buffer_size size of buffer used when reading a file from disk. Defaults 1024
#'
#' @details
#' specifying \code{expand_geometries = TRUE} will expand individual \code{GEOMETRYCOLLECTION}
#' geometries to their own row in the resulting `sf` object. If the geometries are part
#' of a \code{Feature} (i.e., with properties), the properties will be repeated on each row.
#'
#' The \code{GEOMETRYCOLLECTION} information is not kept when using \code{expand_geometries = TRUE}. Therefore,
#' it is not possible to reconstruct the \code{GEOMETRYCOLLECTION} after unnesting it.
#'
#' Geojson specification RFC7946 \url{https://tools.ietf.org/html/rfc7946#page-12}
#' says all CRS should be the World Geodetic System 1984 (WGS 84) [WGS84] datum,
#' with longitude and latitude units of decimal degrees.  This is equivalent to
#' the coordinate reference system identified by the Open Geospatial Consortium (OGC)
#' URN urn:ogc:def:crs:OGC::CRS84
#'
#' \code{geojson_sfc} and \code{geojson_sf} automatically set the CRS to WGS 84.
#' The fields \code{crs} and \code{proj4string} let you to overwrite the defaults.
#'
#' @examples
#'
#' ## character string of GeoJSON
#'
#' ## load 'sf' for print methods
#' # library(sf)
#' geojson <- '{ "type":"Point","coordinates":[0,0] }'
#' geojson_sfc(geojson)
#'
#' geojson <- '[
#'   { "type":"Point","coordinates":[0,0]},
#'   {"type":"LineString","coordinates":[[0,0],[1,1]]}
#'   ]'
#' geojson_sfc( geojson )
#'
#'\dontrun{
#' ## GeoJSON at a url
#' myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
#' sf <- geojson_sfc(myurl)
#' }
#'
#' @export
geojson_sfc <- function(
	geojson,
	expand_geometries = FALSE,
	crs = NULL,
	proj4string = NULL,
	buffer_size = 1024
	) {

	sfc <- geojson_to_sfc( geojson, expand_geometries, buffer_size )
	if( !is.null( crs ) | !is.null( proj4string ) ) {
		sfc <- set_crs( sfc, crs, proj4string )
	}
	return( sfc )
}

geojson_to_sfc <- function( geojson, expand_geometries, buffer_size ) UseMethod("geojson_to_sfc")

#' @export
geojson_to_sfc.geojson <- function(
	geojson,
	expand_geometries = FALSE,
	buffer_size
	) {

	geojson_to_sfc.character(geojson, expand_geometries, buffer_size)
}

#' @export
geojson_to_sfc.character <- function(
	geojson,
	expand_geometries = FALSE,
	buffer_size
	) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sfc(geojson, expand_geometries))
	}
	if (is_url(geojson)) {

		return(geojson_to_sfc(curl::curl(geojson), expand_geometries))

	} else if (file.exists(geojson) ) {
		return(
			rcpp_read_sfc_file(
			  normalizePath( geojson )
			  , get_download_mode()
			  , expand_geometries
			  , buffer_size
			  )
		  )
	}
	return(rcpp_geojson_to_sfc(geojson, expand_geometries))
}

#' @export
geojson_to_sfc.connection <- function(
	geojson,
	expand_geometries = FALSE,
	buffer_size
	) {
	geojson_sfc(read_url(geojson), expand_geometries)
}

#' @export
geojson_to_sfc.default <- function(
	geojson,
	expand_geometries = FALSE,
	buffer_size
	) {
	rcpp_geojson_to_sfc(geojson, expand_geometries)
}

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
geojson_sf <- function(
	geojson,
	expand_geometries = FALSE,
	crs = NULL,
	proj4string = NULL,
	buffer_size = 1024
	) {
	sf <- geojson_to_sf( geojson, expand_geometries, buffer_size )
	if( !is.null( crs ) | !is.null( proj4string ) ) {
		sf[["geometry"]] <- set_crs( sf[["geometry"]], crs, proj4string )
	}
	return( sf )
}

geojson_to_sf <- function( geojson, expand_geometries, buffer_size ) {
	UseMethod("geojson_to_sf")
}

#' @export
geojson_to_sf.geojson <- function( geojson, expand_geometries = FALSE, buffer_size ) {
	geojson_to_sf.character(geojson, expand_geometries)
}

#' @export
geojson_to_sf.character <- function(geojson, expand_geometries = FALSE, buffer_size ) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sf(geojson, expand_geometries))
	}
	if (is_url(geojson)) {

		return(geojson_to_sf(curl::curl(geojson), expand_geometries))

	} else if (file.exists(geojson) ) {
		return(
			rcpp_read_sf_file(
				normalizePath( geojson )
				, get_download_mode()
				, expand_geometries
				, buffer_size
				)
			)
	}
	 return(rcpp_geojson_to_sf( geojson, expand_geometries ) )
}

#' @export
geojson_to_sf.connection <- function(geojson, expand_geometries = FALSE, buffer_size ) {
	geojson_sf(read_url(geojson), expand_geometries)
}

#' @export
geojson_to_sf.numeric <- function( geojson, expand_geometries = FALSE, buffer_size ) {
	stop("Numeric vectors are not valid GeoJSON")
}

#' @export
geojson_to_sf.default <- function(geojson, expand_geometries = FALSE, buffer_size ) {
	rcpp_geojson_to_sf(geojson, expand_geometries)
}



date_columns <- function( sf ) {
	names(which(vapply(sf , function(x) { inherits(x, "Date") | inherits(x, "POSIXct") }, T)))
}

set_crs <- function(sfc, crs, proj4string ) {
	crs <- list(
		epsg = ifelse(is.null(crs),NA_integer_,crs)
		, proj4string = ifelse(is.null(proj4string),"",proj4string)
	)
	attr( crs, "class" ) <- "crs"
	attr( sfc, "crs" ) <- crs
	return( sfc )
}


handle_dates <- function( x ) {
	dte <- date_columns( x )
	x[dte] <- lapply(as.data.frame(x)[dte], as.character)
	return( x )
}

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

get_download_mode <- function() {
	ifelse( .Platform$OS.type == "windows", "r", "rb" )
}

