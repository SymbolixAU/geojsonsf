#' Geojson to WKT
#'
#' Converts GeoJSON to Well-Known Text
#'
#' @return data.frame with a 'geometry' column of well-known text
#'
#' @inheritParams geojson_sfc
#'
#' @examples
#' geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#' geojson_wkt(geojson)
#'
#' @export
geojson_wkt <- function(geojson) rcpp_geojson_to_wkt(geojson)

