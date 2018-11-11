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
