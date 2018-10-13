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
