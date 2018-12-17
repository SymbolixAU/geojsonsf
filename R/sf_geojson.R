#' sf to GeoJSON
#'
#' Converts `sf` objects to GeoJSON
#'
#' @param sf simple feature object
#' @param atomise logical indicating if the sf object should be converted into a vector
#' of GeoJSON objects
#' @param simplify logical indicating if sf objects without property columns should simplify
#' (\code{TRUE}) into a vector of GeoJSON, or return a Featurecollection with
#' empty property fields (\code{FALSE}). If \code{atomise} is TRUE this argument is ignored.
#' @param digits integer specifying the number of decimal places to round numerics.
#' numeric values are coorced using \code{as.integer}, which may round-down the value you supply.
#' Default is \code{NULL} - no rounding
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
sf_geojson <- function( sf, atomise = FALSE, simplify = TRUE, digits = NULL ) UseMethod("sf_geojson")

#' @export
sf_geojson.sf <- function( sf, atomise = FALSE, simplify = TRUE, digits = NULL ) {
	sf <- handle_dates( sf )
	digits <- handle_digits( digits )
	if( atomise | ( ncol( sf ) == 1 & simplify ) ) return( rcpp_sf_to_geojson_atomise( sf, digits ) )
	return( rcpp_sf_to_geojson( sf, digits ) )
}


#' sfc to GeoJSON
#'
#' Converts `sfc` objects to GeoJSON
#'
#' @param sfc simple feature collection object
#' @param digits integer specifying the number of decimal places to round numerics.
#' numeric values are coorced using \code{as.integer}, which may round-down the value you supply.
#' Default is \code{NULL} - no rounding
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
sfc_geojson <- function( sfc, digits = NULL )	UseMethod("sfc_geojson")

#' @export
sfc_geojson.sfc <- function( sfc, digits = NULL ) {
	digits <- handle_digits( digits )
	rcpp_sfc_to_geojson( sfc, digits )
}

#' @export
sf_geojson.default <- function( sf, atomise = FALSE, simplify = TRUE, digits = NULL ) stop("Expected an sf object")

#' @export
sfc_geojson.default <- function( sfc, digits = NULL ) stop("Expected an sfc object")


#' df to GeoJSON
#'
#' Converts data.frame objects to GeoJSON. Each row is considerd a POINT
#'
#' @param df data.frame
#' @param lon column of \code{df} containing the longitude data
#' @param lat column of \code{df} containing the latitude data
#' @param z column of \code{df} containing the Z attribute of the GeoJSON
#' @param m column of \code{df} containing the M attribute of the GeoJSON.
#' If supplied, you must also supply \code{z}
#' @param atomise logical indicating if the data.frame should be converted into a vector
#' of GeoJSON objects
#' @param simplify logical indicating if data.frame without property columns should simplify
#' (\code{TRUE}) into a vector of GeoJSON, or (\code{FALSE}). If \code{atomise} is TRUE
#' this argument is ignored.
#' @param digits integer specifying the number of decimal places to round numerics.
#' numeric values are coorced using \code{as.integer}, which may round-down the value you supply.
#' Default is \code{NULL} - no rounding
#'
#' @return vector of GeoJSON
#'
#' @examples
#'
#' df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA), id = 1:6, val = letters[1:6])
#' df_geojson( df, lon = "lon", lat = "lat")
#' df_geojson( df, lon = "lon", lat = "lat", atomise = TRUE)
#'
#' df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA) )
#' df_geojson( df, lon = "lon", lat = "lat")
#' df_geojson( df, lon = "lon", lat = "lat", simplify = FALSE)
#'
#' df <- data.frame(lon = c(1:5), lat = c(1:5), elevation = c(1:5) )
#' df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
#' df_geojson( df, lon = "lon", lat = "lat", z = "elevation", simplify = FALSE)
#'
#' df <- data.frame(lon = c(1:5), lat = c(1:5), elevation = c(1:5), id = 1:5 )
#' df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
#' df_geojson( df, lon = "lon", lat = "lat", z = "elevation", atomise = TRUE)
#'
#'
#' ## to sf objects
#' geo <- df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
#' sf <- geojson_sf( geo )
#'
#' @export
df_geojson <- function(
	df, lon, lat, z = NULL, m = NULL,
	atomise = FALSE, simplify = TRUE, digits = NULL
	) {
	UseMethod("df_geojson")
}

#' @export
df_geojson.data.frame <- function(
	df, lon, lat, z = NULL, m = NULL,
	atomise = FALSE, simplify = TRUE, digits = NULL
	) {

	digits <- handle_digits( digits )
	df <- handle_dates( df )
	lon <- force( lon )
	lat <- force( lat )
	z <- force( z )
	m <- force( m )
	if( is.null(z) && !is.null(m)) stop("z must be supplied when using m")
	geometries <- c(lon, lat, z, m)

	if( atomise | ( ncol( df ) == length( geometries ) & simplify ) ){
		return( rcpp_df_to_geojson_atomise( df, geometries, digits ) )
	}
	return( rcpp_df_to_geojson( df, geometries, digits ) )
}
