#' Geojson to sfc
#'
#' Extracts geometries from GeoJSON and returns an `sfc` object
#'
#' @param geojson string of GeoJSON
#'
#' @export
geojson_sfc <- function(geojson) {
	rcpp_geojson_to_sf(geojson)
}
