context("conversion")


test_that("sfc objects with ZM converted to GeoJSON", {

	js <- '{"type":"Point","coordinates":[0.0,0.0]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Point","coordinates":[0.0,0.0,0.0]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Point","coordinates":[0.0,0.0,0.0,0.0]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0],[1.0,1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0],[1.0,1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0,0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0,1.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0,2.0,3.0],[1.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XY")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0,2.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0,1.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZ")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0,1.0],[3.0,3.0],[3.0,2.0],[2.0,2.0,1.0,1.0]]]]}'
	sf <- geojson_sfc(js)
	expect_equal( attr( sf[[1]], "class" )[1], "XYZM")
	j <- sfc_geojson( sf )
	expect_true( jsonify::validate_json( j ) )
})


## SF ZM
test_that("sf objects with ZM converted to GeoJSON", {

	js <- '{"type":"Point","coordinates":[0.0,0.0]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Point","coordinates":[0.0,0.0,0.0]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Point","coordinates":[0.0,0.0,0.0,0.0]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0],[1.0,1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPoint","coordinates":[[0.0,0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0],[1.0,1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"LineString","coordinates":[[0.0,0.0,0.0,0.0],[1.0,1.0]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0,0.0,0.0],[1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiLineString","coordinates":[[[0.0,0.0],[1.0,1.0,1.0,1.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0,2.0,3.0],[1.0,0.0],[0.0,0.0]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XY")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0,2.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0,1.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZ")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )

	js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[2.0,2.0],[2.0,3.0,1.0],[3.0,3.0],[3.0,2.0],[2.0,2.0,1.0,1.0]]]]}'
	sf <- geojson_sf(js)
	expect_equal( attr( sf$geometry[[1]], "class" )[1], "XYZM")
	j <- sf_geojson( sf )
	expect_true( jsonify::validate_json( j ) )
})
## SF ZM


test_that("geometry collections with geometries with XYZM dimensions", {

	js <- '{"type":"GeometryCollection","geometries":[{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0,0]]]]}]}'
	sf <- geojson_sfc( js )
	expect_equal( attr( sf[[1]], "class")[1], "XY" ) ## GEOMETRYCOLLECTION has XY
	expect_equal( attr(sf[[1]][[1]],  "class")[1], "XYZ") ## MULTIPOLYGON has XYZ

	js <- '{"type":"GeometryCollection","geometries":[{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0,0,0]]]]}]}'
	sf <- geojson_sfc( js )
	expect_equal( attr( sf[[1]], "class")[1], "XY" ) ## GEOMETRYCOLLECTION has XY
	expect_equal( attr(sf[[1]][[1]],  "class")[1], "XYZM") ## MULTIPOLYGON has XYZM

	js <- '{"type":"GeometryCollection","geometries":[{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0,0,0]]]]},{"type":"Point","coordinates":[0,0]}]}'
	sf <- geojson_sfc( js )
	expect_equal( attr( sf[[1]], "class")[1], "XY" ) ## GEOMETRYCOLLECTION has XY
	expect_equal( attr(sf[[1]][[1]],  "class")[1], "XYZM") ## MULTIPOLYGON has XYZM
	expect_equal( attr(sf[[1]][[2]],  "class")[1], "XY") ## MULTIPOLYGON has XY

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
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,1,1), ncol = 2, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1],[1,1]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,1,1,1,0), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,0,1,1,2), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,1,1,1,2), ncol = 3, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1,2],[1,1,2]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,1,2,1,1,2,0), ncol = 4, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0],[1,1,2,3]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,0,0,1,1,2,3), ncol = 4, byrow = T) )
	mls <- '{"type":"MultiLineString","coordinates":[[[0.0,0,1,2],[1,1,2,3]]]}'
	expect_equal( as.matrix( geojson_sfc( mls )[[1]][[1]] ), matrix(c(0,0,1,2,1,1,2,3), ncol = 4, byrow = T) )

	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,0), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0,9]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,9), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0,1],[0,1],[1,1],[1,0],[0,0,9]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,1,0,1,0,1,1,0,1,0,0,0,0,9), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1,3],[1,0],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,0,0,1,0,1,1,3,1,0,0,0,0,0), ncol = 3, byrow = T) )
	ply <- '{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1,3],[1,0,1,2],[0,0]]]}'
	expect_equal( as.matrix( geojson_sfc( ply )[[1]][[1]] ), matrix(c(0,0,0,0,0,1,0,0,1,1,3,0,1,0,1,2,0,0,0,0), ncol = 4, byrow = T) )

	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3,9],[3,3],[3,2],[2,2]]]]}'
	expect_equal( geojson_sfc( mply )[[1]][[1]][[1]]  , matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T) )
	expect_equal( geojson_sfc( mply )[[1]][[1]][[2]]  , matrix(c(2,2,0,2,3,9,3,3,0,3,2,0,2,2,0), ncol = 3, byrow = T) )

	mply <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1,2,2],[1,0],[0,0]],[[2,2],[2,3,9],[3,3],[3,2],[2,2]]]]}'
	expect_equal( geojson_sfc( mply )[[1]][[1]][[1]]  , matrix(c(0,0,0,0,0,1,0,0,1,1,2,2,1,0,0,0,0,0,0,0), ncol = 4, byrow = T) )
	expect_equal( geojson_sfc( mply )[[1]][[1]][[2]]  , matrix(c(2,2,0,2,3,9,3,3,0,3,2,0,2,2,0), ncol = 3, byrow = T) )

})

test_that("NA values handled", {


	sf <- structure(list(geometry = structure(list(structure(c(0, 1, 0,
			  NA, 0, NA, 0, 1), .Dim = c(2L, 4L), class = c("XYZM", "LINESTRING",
				"sfg"))), class = c("sfc_LINESTRING", "sfc"), precision = 0, bbox = structure(c(xmin = 0,
				ymin = NA, xmax = 1, ymax = NA), class = "bbox"), crs = structure(list(
				epsg = NA_integer_, proj4string = NA_character_), class = "crs"), n_empty = 0L)), row.names = 1L, class = c("sf",
				"data.frame"), sf_column = "geometry", agr = structure(integer(0), class = "factor", .Label = c("constant",
				"aggregate", "identity"), .Names = character(0)))

	geo <- geojsonsf::sf_geojson( sf )
	expect_true( jsonify::validate_json( geo ) )
	expect_equal( as.character( geo ), '{"type":"LineString","coordinates":[[0.0,0.0,0.0,0.0],[1.0,null,null,1.0]]}' )

})



