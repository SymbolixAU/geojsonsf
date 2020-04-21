context("crs")

test_that("CRS and proj4string are deprecated",{

	geo <- '[]'
	warn <- "crs and proj4string are deprecated. Please now use input and wkt"

	expect_warning( geojson_sfc( geo, crs = 123 ), warn)
	expect_warning( geojson_sf( geo, crs = 123), warn )
	expect_warning( geojson_sfc( geo, proj4string = "abc" ), warn )
	expect_warning( geojson_sf( geo, proj4string = "abc" ), warn )
	expect_warning( geojson_sfc( geo, crs = 123, proj4string = "abc" ), warn )
	expect_warning( geojson_sf( geo, crs = 123, proj4string = "abc" ), warn )

})

test_that("input and wkt are set",{

	geo <- '[]'

	res <- geojson_sfc( geo, input = 123 )
	expect_true( attr(res, "input")[[1]] == 123 )
	expect_true( attr(res, "input")[[2]] == "" )

	res <- geojson_sf( geo, input = 123)
	expect_true( attr(res$geometry, "input")[[1]] == 123 )
	expect_true( attr(res$geometry, "input")[[2]] == "" )

	res <- geojson_sfc( geo, wkt = "abc" )
	expect_true( is.na( attr(res, "input")[[1]] ) )
	expect_true( attr(res, "input")[[2]] == "abc" )

	res <- geojson_sf( geo, wkt = "abc" )
	expect_true( is.na( attr(res$geometry, "input")[[1]] ) )
	expect_true( attr(res$geometry, "input")[[2]] == "abc" )

	res <- geojson_sfc( geo, input = 123, wkt = "abc" )
	expect_true( attr(res, "input")[[1]] == 123 )
	expect_true( attr(res, "input")[[2]] == "abc" )

	res <- geojson_sf( geo, input = 123, wkt = "abc" )
	expect_true( attr(res$geometry, "input")[[1]] == 123 )
	expect_true( attr(res$geometry, "crs")[[2]] == "abc" )

})
