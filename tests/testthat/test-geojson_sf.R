context("geojsonsf")


test_that("ints vs numerics read correctly", {

	# geo <- '{"type":"Point","coordinates":[0,0]}'
	# expect_equal(geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true(is.integer( geojson_sfc( geo )[[1]] ) )

	pt <- '{"type":"Point","coordinates":[0.1,0.1]}'
	expect_equal(geojson_sf( pt )[[1]], geojson_sfc( pt ) )
	expect_false(is.integer( geojson_sfc( pt )[[1]] ) )

	# geo <- '{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true( is.integer( geojson_sfc( geo )[[1]] ) )

	mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0],[1,1]]}'
	expect_equal( geojson_sf( mpt )[[1]], geojson_sfc( mpt ) )
	expect_false( is.integer( geojson_sfc( mpt )[[1]] ) )

	# geo <- '{"type":"LineString","coordinates":[[0,0],[1,1]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true( is.integer( geojson_sfc( geo )[[1]] ) )

	ls <- '{"type":"LineString","coordinates":[[0.1,0],[1,1]]}'
	expect_equal( geojson_sf( ls )[[1]], geojson_sfc( ls ) )
	expect_false( is.integer( geojson_sfc( ls )[[1]] ) )

	# ## TODO( if the 2nd element is a double and the first isn't? )
	# geo <- '{"type":"LineString","coordinates":[[0,0.1],[1,1]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_false( is.integer( geojson_sfc( geo )[[1]] ) )

	# geo <- '{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]}'
	# expect_equal( geojson_sf( geo )[[1]], geojson_sfc( geo ) )
	# expect_true( is.integer( geojson_sfc( geo )[[1]] ) )

	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1]]]}'
	expect_equal( geojson_sf( mls )[[1]], geojson_sfc( mls ) )
	expect_false( is.integer( geojson_sfc( mls )[[1]] ) )

	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}'
	expect_equal( geojson_sf( ply )[[1]], geojson_sfc( ply ) )
	expect_false( is.integer( geojson_sfc( ply )[[1]] ) )

	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	expect_equal( geojson_sf( mply )[[1]], geojson_sfc( mply ) )
	expect_false( is.integer( geojson_sfc( mply )[[1]] ) )

})

test_that("ZM attributes", {

	pt <- '{"type":"Point","coordinates":[0.1,0.1]}'
	expect_true( length( as.numeric( geojson_sfc( pt )[[1]] ) ) == 2 )
	pt <- '{"type":"Point","coordinates":[0.1,0.1,1]}'
	expect_true( length( as.numeric( geojson_sfc( pt )[[1]] ) ) == 3 )
	pt <- '{"type":"Point","coordinates":[0.1,0.1,1,1]}'
	expect_true( length( as.numeric( geojson_sfc( pt )[[1]] ) ) == 4 )

	mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0],[1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) ) == 4 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0,1],[1,1]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 6 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0],[1,1,2]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 6 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0,1],[1,1,1]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 6 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0,1,1],[1,1]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 8 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0,1],[1,1,1,2]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 8 )
  mpt <- '{"type":"MultiPoint","coordinates":[[0.1,0,1,1],[1,1,1]]}'
  expect_true( length( as.numeric( geojson_sfc( mpt )[[1]] ) )  == 8 )

	ls <- '{"type":"LineString","coordinates":[[0.1,0],[1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 4 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0,1],[1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 6 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0],[1,1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 6 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0,1],[1,1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 6 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0,1,1],[1,1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 8 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0,1],[1,1,1,1]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 8 )
	ls <- '{"type":"LineString","coordinates":[[0.1,0,1,1],[1,1,1,2]]}'
	expect_true( length( as.numeric( geojson_sfc( ls )[[1]] ) ) == 8 )

	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,1,1), ncol = 2, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1],[1,1]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,1,1,1,0), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,0,1,1,2), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,1,1,1,2), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1,2],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,1,2,1,1,2,0), ncol = 4, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1,2,3]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,0,0,1,1,2,3), ncol = 4, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1,2],[1,1,2,3]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]] ), matrix(c(0,0,1,2,1,1,2,3), ncol = 4, byrow = T) )


	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,0), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0,9]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,9), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0,9]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,9), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1,3],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,0,0,1,0,1,1,3,1,0,0,0,0,0), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1,3],[1,0,1,2],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]] ), matrix(c(0,0,0,0,0,1,0,0,1,1,3,0,1,0,1,2,0,0,0,0), ncol = 4, byrow = T) )


	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	expect_equal( as.matrix( geojson_sfc( mply )[[1]] ) , matrix(c(0,0,0,1,1,1,1,0,0,0,2,2,2,3,3,3,3,2,2,2), ncol = 2, byrow = T) )
	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3,9],[3,3],[3,2],[2,2]]]]}'
	expect_equal( geojson_sfc( mply )[[1]][[1]][[1]]  , matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T) )
	expect_equal( geojson_sfc( mply )[[1]][[1]][[2]]  , matrix(c(2,2,0,2,3,9,3,3,0,3,2,0,2,2,0), ncol = 3, byrow = T) )

	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1,2,2],[1,0],[0,0]],[[2,2],[2,3,9],[3,3],[3,2],[2,2]]]]}'
	expect_equal( geojson_sfc( mply )[[1]][[1]][[1]]  , matrix(c(0,0,0,0,0,1,0,0,1,1,2,2,1,0,0,0,0,0,0,0), ncol = 4, byrow = T) )
	expect_equal( geojson_sfc( mply )[[1]][[1]][[2]]  , matrix(c(2,2,0,2,3,9,3,3,0,3,2,0,2,2,0), ncol = 3, byrow = T) )

})

