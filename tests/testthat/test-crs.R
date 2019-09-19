context("crs")

test_that("CRS and proj4string are set",{

	geo <- '[]'

	res <- geojson_sfc( geo, crs = 123 )
	expect_true( attr(res, "crs")[[1]] == 123 )
	expect_true( attr(res, "crs")[[2]] == "" )

	res <- geojson_sf( geo, crs = 123)
	expect_true( attr(res$geometry, "crs")[[1]] == 123 )
	expect_true( attr(res$geometry, "crs")[[2]] == "" )

	res <- geojson_sfc( geo, proj4string = "abc" )
	expect_true( is.na( attr(res, "crs")[[1]] ) )
	expect_true( attr(res, "crs")[[2]] == "abc" )

	res <- geojson_sf( geo, proj4string = "abc" )
	expect_true( is.na( attr(res$geometry, "crs")[[1]] ) )
	expect_true( attr(res$geometry, "crs")[[2]] == "abc" )

	res <- geojson_sfc( geo, crs = 123, proj4string = "abc" )
	expect_true( attr(res, "crs")[[1]] == 123 )
	expect_true( attr(res, "crs")[[2]] == "abc" )

	res <- geojson_sf( geo, crs = 123, proj4string = "abc" )
	expect_true( attr(res$geometry, "crs")[[1]] == 123 )
	expect_true( attr(res$geometry, "crs")[[2]] == "abc" )

})
