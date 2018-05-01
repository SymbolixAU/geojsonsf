context("null geometries")

test_that("null geometries parsed correctly", {

	js <- '{"type":"Feature","properties":{"id":1},"geometry":null}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_POINT")
	js2 <- sf_geojson(sf, atomise = T)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"Point","coordinates":[0,0]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_POINT")
	js2 <- sf_geojson(sf)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_MULTIPOINT")

	js2 <- sf_geojson(sf)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"LineString","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_LINESTRING")
	js2 <- sf_geojson(sf)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_MULTILINESTRING")
	js2 <- sf_geojson(sf)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":2},"geometry":null},
  {"type":"Feature","properties":{"id":1},"geometry":{"type":"Polygon","coordinates":[[[0,0],[1,1],[2,2],[0,0]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 2)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_GEOMETRY") ## because the first null starts as a point
	# js2 <- sf_geojson(sf)
	# expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiPolygon","coordinates":[[[[0,0],[1,1],[2,2],[0,0]]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)
	expect_true(attributes(sf$geometry)[['class']][1] == "sfc_MULTIPOLYGON")
	js2 <- sf_geojson(sf)
	expect_true(gsub(" |\\r|\\n|\\t","",js) == js2)

	js <- '{"type":"FeatureCollection","features":[
  {"type":"Feature","properties":{"id":1},"geometry":{"type":"GeometryCollection","geometries": [
	{"type": "Point","coordinates": [100.0, 0.0]},
	{"type": "LineString","coordinates": [[101.0, 0.0], [102.0, 1.0]]}]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	geojson_sf(js)


})

