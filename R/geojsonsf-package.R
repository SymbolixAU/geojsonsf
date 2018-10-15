#' @useDynLib geojsonsf, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @import rapidjsonr
NULL

#' geo_melbourne
#'
#' GeoJSON data of Melbourne's Inner suburbs.
"geo_melbourne"

#' @export
print.geojson <- function( geo ) {

	if( length(geo) == 1 ) {
		cat( geo, "\n")
	} else { ## vector / atomised, show each individual vector
		NextMethod()
	}
}


