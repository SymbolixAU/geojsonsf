context("geojsonsf")


test_that("ints vs numerics read correctly", {

	geo <- '{"type":"Point","coordinates":[0,0]}'
	expect_equal(geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	expect_true(is.integer( geojson_sfc( geo )[[1]] ) )

	geo <- '{"type":"Point","coordinates":[0.1,0.1]}'
	expect_equal(geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	expect_false(is.integer( geojson_sfc( geo )[[1]] ) )


	## TODO( this fails )
	# geo <- '{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true( is.integer( geojson_sfc( geo )[[1]] ) )

	geo <- '{"type":"MultiPoint","coordinates":[[0.1,0],[1,1]]}'
	expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	expect_false( is.integer( geojson_sfc( geo )[[1]] ) )

	## TODO( this fails )
	# geo <- '{"type":"LineString","coordinates":[[0,0],[1,1]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true( is.integer( geojson_sfc( geo )[[1]] ) )

	geo <- '{"type":"LineString","coordinates":[[0.1,0],[1,1]]}'
	expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	expect_false( is.integer( geojson_sfc( geo )[[1]] ) )

})
