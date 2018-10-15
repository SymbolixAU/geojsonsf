#' @useDynLib geojsonsf, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @import rapidjsonr
NULL

#' geo_melbourne
#'
#' GeoJSON data of Melbourne's Inner suburbs.
"geo_melbourne"

#' @export
print.geojson <- function( x, ... ) {

	if( length(x) == 1 ) {
		cat( x, "\n")
	} else { ## vector / atomised, show each individual vector
		NextMethod()
	}
}


