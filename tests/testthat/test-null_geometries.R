context("null geometries")

test_that("null geometries parsed correctly", {

	js <- '{"type":"Feature","properties":{"id":1},"geometry":null}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"Point","coordinates":[0,0]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"LineString","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":2},"geometry":null},
  {"type":"Feature","properties":{"id":1},"geometry":{"type":"Polygon","coordinates":[[[0,0],[1,1],[2,2],[0,0]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 2)

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiPolygon","coordinates":[[[[0,0],[1,1],[2,2],[0,0]]]]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}]}'
	sf <- geojson_sf(js)
	expect_true(attr(sf$geometry, "n_empty") == 1)

})
