#' @useDynLib geojsonsf, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL

#' geo_melbourne
#'
#' GeoJSON data of Melbourne's Inner suburbs.
"geo_melbourne"

#' @export
print.geojson <- function( x, ... ) sapply(x, function(x) cat(x, "\n"))


