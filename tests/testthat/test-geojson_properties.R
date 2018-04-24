context("properties")

test_that("properties captured correctly", {

	f <- '{"type": "Feature","properties": { "id" : 1, "name" : "foo" },
	       "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}}'

	sf <- geojson_sf(f)
	wkt <- geojson_wkt(f)

	expect_true(all(names(sf) == c("geometry", "id", "name")))
	expect_true(all(names(wkt) == c("geometry", "id", "name")))
	expect_true(sf$id == 1)
	expect_true(wkt$id == 1)
	expect_true(sf$name == "foo")
	expect_true(wkt$name == "foo")

	js <- '[{
	  "type": "Feature",
	  "properties" : {},
	  "geometry": {
	    "type": "Polygon","coordinates": [[[-10.0, -10.0],[10.0, -10.0],[10.0, 10.0],[-10.0, -10.0]]]}
	  },
	  {
      "type": "Feature",
	    "properties" : {"id":1},
	    "geometry": {"type": "MultiPolygon",
	    "coordinates": [[[[180.0, 40.0], [180.0, 50.0], [170.0, 50.0],[170.0, 40.0], [180.0, 40.0]]],
	      [[[-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],[-180.0, 40.0], [-170.0, 40.0]]]]}
	  },
	  {
	  "type": "FeatureCollection",
	  "features": [{
	      "type": "Feature",
	      "properties": {"id" : 2, "value" : "foo"},
	      "geometry": {"type": "Point","coordinates": [100.0, 0.0]}
	    },{
	      "type": "Feature",
	      "properties": null,
	      "geometry": {
	        "type": "LineString",
	        "coordinates": [[101.0, 0.0],[102.0, 1.0]]
	      }}
    ]
	},
	{
	  "type": "GeometryCollection",
	  "geometries": [
	    {"type": "Point","coordinates": [100.0, 0.0]},
	    {"type": "LineString","coordinates": [[101.0, 0.0],[102.0, 1.0]]},
	    {"type" : "MultiPoint","coordinates" : [[0,0],[1,1],[2,2]]}
	  ]
	},
	{"type": "Polygon","coordinates": [[[-10.0, -10.0],[10.0, -10.0],[10.0, 10.0],[-10.0, -10.0]]]}
	]'
	sf <- geojson_sf(js)
	wkt <- geojson_wkt(js)

	expect_true(ncol(sf) == 3)
	expect_true(ncol(wkt) == 3)
	expect_true(sum(sf$id, na.rm = T) == 3)
	expect_true(sum(wkt$id, na.rm = T) == 3)
	expect_true(sf$value[!is.na(sf$value)] == "foo")
	expect_true(wkt$value[!is.na(wkt$value)] == "foo")

})

test_that("sf and sfc created equally", {

	f <- '{
		"type": "Feature",
  	"properties": { "id" : 1, "name" : "foo" },
  	"geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
  }'

	sf <- geojson_sf(f)
	sfc <- geojson_sfc(f)

	expect_true(all(class(sf$geometry) == class(sfc)))

})

test_that("null geometries are valid for features", {

	js <- '{"type":"Point","coordinates":[null,null]}'
	geojson_sf(js) ## TODO: needs to error!!

	js <- '{"type":"Point","coordinates":[,]}'
	expect_error(geojson_sf(js), "Invalid JSON")

	js <- '{"type":"Point","coordinates":[]}'
	expect_error(geojson_sf(js), "Invalid lon/lat object")

	js <- '{"type":"Point","coordinates":{}}'
	expect_error(geojson_sf(js), "No 'array' member at object index 0 - invalid GeoJSON")

	js <- '{"type","Feature","geometry":null}'
	expect_error(geojson_sf(js), "Invalid JSON")

	js <- '{"type","Feature","geometry":null,"properties":{}}'
	expect_error(geojson_sf(js), "Invalid JSON")

	## NULL geometry should be fine / parse
	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"Point","coordinates":[0,0]}},
	{"type":"Feature","properties":{"id":2},"geometry":null}
	]}'
	expect_true(nrow(geojson_sf(js)) == 2)
	## TODO: Which geometry should the empty row be?

	js <- '{"type":"Feature","properties":{"id":2},"geometry": null}'
	expect_true(nrow(geojson_sf(js)) == 1)
	## TODO: Which geometry should the empty row be?

	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":1},"geometry":{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":2},"geometry":{"type":"Point","coordinates":[0,0]}},
	{"type":"Feature","properties":{"id":3},"geometry":null}
	]}'
	expect_true(nrow(geojson_sf(js)) == 3)
	expect_true(all(geojson_sf(js)[['id']] == 1:3))
	sf <- geojson_sf(js)
	expect_true(length(as.character(sf$geometry[[3]])) == 0)
	## TODO: Which geometry should this be?


	js <- '{"type":"FeatureCollection","features":[
	{"type":"Feature","properties":{"id":3},"geometry":{"type":"MultiPoint","coordinates":[[0,0],[1,1]]}},
	{"type":"Feature","properties":{"id":1},"geometry":null},
	{"type":"Feature","properties":{"id":2},"geometry":{"type":"Point","coordinates":[0,0]}}
	]}'
	expect_true(nrow(geojson_sf(js)) == 3)
	expect_true(all(geojson_sf(js)[['id']] == c(3,1,2)))
	sf <- geojson_sf(js)
	expect_true(length(as.character(sf$geometry[[2]])) == 0)
	## TODO: Which geometry should this be?


	## null geometries that aren't part of features should still error
	js <- '{"type":"Point","coordinates":null}'
  expect_error(geojson_sf(js), "No 'array' member at object index 0 - invalid GeoJSON")
})






