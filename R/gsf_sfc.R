#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string of GeoJSON
#'
#' @export
geojson_sfc <- function(geojson) {
	rcpp_geojson_to_sfc(geojson)
	message("not yet implemented this function")
}


#' Geojson to sf
#'
#' Converts GeoJSON to an `sf` object
#'
#' @param geojson string of GeoJSON
#' @export
geojson_sf <- function(geojson){
	rcpp_geojson_to_sf(geojson)
}
