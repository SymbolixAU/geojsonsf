context("sf geojson")

test_that("sfc objects converted to GeoJSON", {

	js <- '{"type":"Point","coordinates":[0,0]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"LineString","coordinates":[[0,0],[1,1]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"MultiLineString","coordinates":[[[0,0],[1,1]],[[2,2],[3,3]]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"Polygon","coordinates":[[[0,0],[1,1]]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	sf <- geojson_sfc(js)
	expect_true(sfc_geojson(sf) == js)
	jsonify::validate_json(sfc_geojson(sf))

	js <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	expect_true(sfc_geojson(geojson_sfc(js)) == gsub(" |\\r|\\n|\\t","",js))
	jsonify::validate_json(sfc_geojson(geojson_sfc(js)))
})

test_that("GeometryCollections correctly closed", {
	js <- '{"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[100,0]},{"type":"LineString","coordinates":[[101,0],[102,1]]},{"type":"MultiPoint","coordinates":[[0,0],[1,1],[2,2]]}]}'
	sf <- geojson_sfc(js)
	jsonify::validate_json(sfc_geojson(sf))
	j <- sfc_geojson(sf)
	expect_true(gsub(" |\\n|\\r|\\t","",js) == j)

	js <- '{"type":"GeometryCollection","geometries":[{"type":"MultiLineString","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}]}'
	sf <- geojson_sf(js)
	jsonify::validate_json(sf_geojson(sf))
	j <- sf_geojson(sf)
	sf2 <- geojson_sf(j)
	expect_equal(sf, sf2)

	js <- '{"type":"GeometryCollection","geometries":[{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}]}'
	sf <- geojson_sf(js)
	j <- sf_geojson(sf)
	sf2 <- geojson_sf(j)
	expect_equal(sf, sf2)

	js <- '{"type":"GeometryCollection","geometries":[{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]]]]}]}'
	sf <- geojson_sf(js)
	j <- sf_geojson(sf)
	sf2 <- geojson_sf(j)
	expect_equal(sf, sf2)
})

test_that("single sf objects converted to GeoJSON", {

	js <- '{"type":"Point","coordinates":[0,0]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"LineString","coordinates":[[0,0],[1,1]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"MultiLineString","coordinates":[[[0,0],[1,1]],[[2,2],[3,3]]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"Polygon","coordinates":[[[0,0],[1,1]]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	sf <- geojson_sf(js)
	expect_true(sf_geojson(sf) == js)

	js <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2,2],[2,3],[3,3],[3,2],[2,2]]]]}'
	expect_true(sf_geojson(geojson_sf(js), TRUE) == gsub(" |\\r|\\n|\\t","",js))

	js <- '{"type": "GeometryCollection", "geometries": [{"type": "Point", "coordinates": [100,0]},{"type": "LineString", "coordinates": [[101,0],[102,1]]},{"type" : "MultiPoint", "coordinates" : [[0,0],[1,1],[2,2]]}]}'
	sf <- geojson_sf(js)
	j <- sf_geojson(sf)
	expect_true(gsub(" |\\n|\\r|\\t","",js) == j)
})

test_that("sf without properties not converted to FeatureCollections", {
	js <- '[{"type":"Polygon","coordinates":[[[0,0],[1,1]]]},{"type":"MultiLineString","coordinates":[[[0,0],[1,1]],[[3,3],[4,4]]]}]'
	sf <- geojson_sf(js)
	expect_true(all(sf_geojson(sf, atomise = F) == sf_geojson(sf, atomise = T)))

	js <- '[{"type":"Polygon","coordinates":[[[0,0],[1,1]]]},{"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]},{"type":"GeometryCollection","geometries":[{"type":"Point", "coordinates":[100.0, 0.0]},{"type":"LineString","coordinates":[[101,0],[102,1]]},{"type":"MultiPoint","coordinates":[[0,0],[1,1],[2,2]]}]}]'
	sf <- geojson_sf(js)
	expect_true(all(sf_geojson(sf, atomise = T) == sf_geojson(sf, atomise = F)))
})

test_that("sf with properties converted to FeatureCollection", {

	js <- '{"type":"Feature","properties":{"prop0":"value0"},"geometry":{"type":"LineString","coordinates":[[100,0],[101,1]]}}'
	expect_true(sf_geojson( geojson_sf(js), atomise = T) == gsub(" |\\r|\\n|\\t","",js))

	fgc <- '{"type":"Feature","geometry":{"type":"GeometryCollection","geometries": [{"type":"Point","coordinates":[100,0]},{"type":"LineString","coordinates":[[101,0],[102,1]]}]},"properties":{"prop0":"value0","prop1":"value1"}}'
	sf <- geojson_sf(fgc)
	expect_true(grepl("prop0",sf_geojson(sf)))
	expect_true(grepl("prop1",sf_geojson(sf)))
	expect_true(grepl("FeatureCollection",sf_geojson(sf)))

	js <- '{"type" : "Feature","properties" : {},"geometry" : {"type": "GeometryCollection", "geometries": [{"type":"Point","coordinates":[100,0]},{"type":"LineString","coordinates":[[101,0],[102,1]]},{"type":"MultiPoint","coordinates":[[0,0],[1,1],[2,2]]}]}}'
	sf <- geojson_sf(js)
	## properties are null, so they wont' be found to be converted back to JSON
	expect_false(grepl("properties",sf_geojson(sf)))

	fc1 <- '{"type":"FeatureCollection","features":[{"type":"Feature","properties":null,"geometry":{"type":"Point","coordinates":[100,0]}}]}'
	sf <- geojson_sf(fc1)
  expect_false(grepl("properties",sf_geojson(sf)))

  js <- '{"type": "FeatureCollection","features":[{"type": "Feature","id": "id0","geometry": {"type": "LineString","coordinates":[[102,0],[103,1],[104,0],[105,1]]},"properties": {"prop0":"value0","prop1":"value1"}},{"type": "Feature","id": "id1","geometry":{"type":"Polygon","coordinates":[[[100,0],[101,0],[101,1], [100.0, 1.0], [100.0, 0.0]]]},"properties":{"prop0":"value0","prop1":"value1"}}]}'

  sf <- geojson_sf(js)
  expect_true(grepl("properties",sf_geojson(sf)))
  expect_true(length(sf_geojson(sf, atomise = T)) == 2)
})

test_that("sf object with properties converted to sfc", {
	fgc <- '{"type":"Feature","geometry":{"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[100,0]},{"type":"LineString","coordinates":[[101,0],[102,1]]}]},"properties": {"prop0": "value0","prop1": "value1"}}'
	sf <- geojson_sf(fgc)
	expect_false(grepl("properties", sfc_geojson( sf$geometry )))
})

test_that("errors are handled", {
	js <- '{"type":"Point","coordinates":[0,0]}'
	sf <- geojson_sf(js)
	expect_error(sfc_geojson(sf),"Expected an sfc object")

	js <- '{"type":"Point","coordinates":[0,0]}'
	sf <- geojson_sfc(js)
	expect_error(sf_geojson(sf),"Expected an sf object")
})

test_that("factors are strings", {

	fgc <- '{"type":"Feature","geometry":{"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[100,0]},{"type":"LineString","coordinates":[[101,0],[102,1]]}]},"properties":{"prop0":"value0","prop1":"value1"}}'
	sf <- geojson_sf(fgc)
	sf$prop0 <- as.factor(sf$prop0)
	geo <- sf_geojson(sf)
	expect_true(grepl("value0", geo))
})


