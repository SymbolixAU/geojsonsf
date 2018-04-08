#' Geojson to WKT
#'
#' Converts GeoJSON to Well-Known Text
#'
#' @param geojson
#'
#' @export
geojson_wkt <- function(geojson) {
	rcpp_geojson_to_wkt(geojson)
}
