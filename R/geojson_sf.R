#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string or vector of GeoJSON, or a URL or file pointing to a geojson file
#' @param expand_geometries logical indicating whether to unnest GEOMETRYCOLLECTION rows. see details
#'
#' @details
#' specifying \code{expand_geometries = TRUE} will expand individual \code{GEOMETRYCOLLECTION}
#' geometries to their own row in the resulting `sf` object. If the geometries are part
#' of a \code{Feature} (i.e., with properties), the properties will be repeated on each row.
#'
#' The \code{GEOMETRYCOLLECTION} information is not kept when using \code{expand_geometries = TRUE}. Therefore,
#' it is not possible to reconstruct the \code{GEOMETRYCOLLECTION} after unnesting it.
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
geojson_sfc <- function(geojson, expand_geometries = FALSE) UseMethod("geojson_sfc")


#' @export
geojson_sfc.geojson <- function( geojson, expand_geometries = FALSE) geojson_sfc.character(geojson, expand_geometries)

#' @export
geojson_sfc.character <- function(geojson, expand_geometries = FALSE) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sfc(geojson, expand_geometries))
	}
	if (is_url(geojson)) {
		return(geojson_sfc(curl::curl(geojson), expand_geometries))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sfc_file(normalizePath(geojson), expand_geometries))
	}
	return(rcpp_geojson_to_sfc(geojson, expand_geometries))
}

#' @export
geojson_sfc.connection <- function(geojson, expand_geometries = FALSE) geojson_sfc(read_url(geojson), expand_geometries)

#' @export
geojson_sfc.default <- function(geojson, expand_geometries = FALSE) rcpp_geojson_to_sfc(geojson, expand_geometries)

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
geojson_sf <- function(geojson, expand_geometries = FALSE) UseMethod("geojson_sf")

#' @export
geojson_sf.geojson <- function( geojson, expand_geometries = FALSE) geojson_sf.character(geojson, expand_geometries)

#' @export
geojson_sf.character <- function(geojson, expand_geometries = FALSE) {

	if(length(geojson) > 1) {
		return(rcpp_geojson_to_sf(geojson, expand_geometries))
	}
	if (is_url(geojson)) {
		return(geojson_sf(curl::curl(geojson), expand_geometries))
	} else if (file.exists(geojson) ) {
		return(rcpp_read_sf_file(normalizePath(geojson), expand_geometries))
	}
	 return(rcpp_geojson_to_sf(geojson, expand_geometries))
}

#' @export
geojson_sf.connection <- function(geojson, expand_geometries = F) geojson_sf(read_url(geojson), expand_geometries)

#' @export
geojson_sf.default <- function(geojson, expand_geometries = F) rcpp_geojson_to_sf(geojson, expand_geometries)

#' sf to GeoJSON
#'
#' Converts `sf` objects to GeoJSON
#'
#' @param sf simple feature object
#' @param atomise logical indicating if the sf object should be converted into a vector
#' of GeoJSON objects
#' @param simplify logical indicating if sf objects without property columns should simplify
#' (\code{TRUE}) into a vector of GeoJSON, or (\code{FALSE}). If \code{atomise} is TRUE
#' this argument is ignored.
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
#'
#' ls <- st_linestring(rbind(c(0,0),c(1,1),c(2,1)))
#' mls <- st_multilinestring(list(rbind(c(2,2),c(1,3)), rbind(c(0,0),c(1,1),c(2,1))))
#' sfc <- st_sfc(ls,mls)
#' sf <- st_sf(sfc)
#' sf_geojson( sf )
#' sf_geojson( sf, simplify = FALSE )
#'
#' }
#'
#' @export
sf_geojson <- function(sf, atomise = FALSE, simplify = TRUE) UseMethod("sf_geojson")

#' @export
sf_geojson.sf <- function(sf, atomise = FALSE, simplify = TRUE) {
	sf <- handle_dates( sf )
	if( atomise | ( ncol( sf ) == 1 & simplify ) ) return( rcpp_sf_to_geojson_atomise( sf ) )
	return( rcpp_sf_to_geojson( sf ) )
}


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
sfc_geojson <- function( sfc ) UseMethod("sfc_geojson")

#' @export
sfc_geojson.sfc <- function(sfc) rcpp_sfc_to_geojson(sfc)

#' @export
sf_geojson.default <- function(sf, atomise = FALSE, simplify = TRUE) stop("Expected an sf object")

#' @export
sfc_geojson.default <- function(sfc) stop("Expected an sfc object")


#' df to GeoJSON
#'
#' Converts data.frame objects to GeoJSON. Each row is considerd a POINT
#'
#' @param df data.frame
#' @param atomise logical indicating if the data.frame should be converted into a vector
#' of GeoJSON objects
#' @param simplify logical indicating if data.frame without property columns should simplify
#' (\code{TRUE}) into a vector of GeoJSON, or (\code{FALSE}). If \code{atomise} is TRUE
#' this argument is ignored.
#'
#' @return vector of GeoJSON
#'
#' @examples
#' \dontrun{
#'
#' df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA), id = 1:6, val = letters[1:6])
#' df_geojson( df, lon = "lon", lat = "lat")
#' df_geojson( df, lon = "lon", lat = "lat", atomise = T)
#'
#' df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA) )
#' df_geojson( df, lon = "lon", lat = "lat")
#' df_geojson( df, lon = "lon", lat = "lat", simplify = T)
#'
#'
#' }
#'
#' @export
df_geojson <- function(df, lon, lat, atomise = FALSE, simplify = TRUE) UseMethod("df_geojson")

#' @export
df_geojson.data.frame <- function(df, lon, lat, atomise = FALSE, simplify = TRUE) {
	df <- handle_dates( df )
	if( atomise | ( ncol( df ) == 2 & simplify ) ) return( rcpp_df_to_geojson_atomise( df, lon, lat ) )
	return( rcpp_df_to_geojson( df, lon, lat ) )
}


date_columns <- function( sf ) names(which(vapply(sf , function(x) { inherits(x, "Date") | inherits(x, "POSIXct") }, T)))

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

