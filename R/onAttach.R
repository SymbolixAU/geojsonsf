.onAttach <- function(...) {
	## check sf version if installed

	tryCatch({
		if( utils::packageVersion("sf") < "0.9.0" ){
			packageStartupMessage(
				"geojsonsf >= v0.2.2 is designed to work with sf >= v0.9.0\n",
				"your current version is ", utils::packageVersion("sf"), " and you may notice some issues with setting and using CRS values"
				)
		}
	},
	error = function( e ) {
		return( invisible() )
	})

}
