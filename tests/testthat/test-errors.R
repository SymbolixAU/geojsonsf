context("errors")

test_that("errors are handled", {

	expect_error(geojson_sf(1:5))
	expect_error(geojson_sf("a"))
	expect_error(geojson_sf())
  expect_error(geojson_sf(NULL))
  expect_error(geojson_sf(NA))
  expect_error(geojson_sf('{ "type" : "Point" }'))

  expect_error(geojson_sf('{"type" : "MultiPoint","coordinates" : [0, 0] }'))
  expect_error(geojson_sf('{"type" : "Point", "coordinates" : null }'))
  expect_error(geojson_sf('{"type" : "LineString", "coordinates" : [ 0, 0 ] }'))
  expect_error(geojson_sf('{"type" : "MultiLineString", "coordinates" : [ 0, 0 ] }'))
  expect_error(geojson_sf('{"type" : "MultiLineString", "coordinates" : [ [0, 0] ] }'))
  expect_error(geojson_sf('{"type" : "Polygon", "coordinates" : [0, 0] }'))
  expect_error(geojson_sf('{"type" : "Polygon", "coordinates" : [ [ 0, 0 ] ] }'))
  expect_error(geojson_sf('{"type" : "MultiPolygon", "coordinates" : [ [0, 0] ] }'))
  expect_error(geojson_sf('{"type" : "MultiPolygon", "coordinates" : [ [ [0, 0] ] ] }'))

  expect_error(geojson_wkt('{"type" : "LineString", "coordinates" : [ 0, 0 ] }'))
  expect_error(geojson_wkt('{"type" : "MultiLineString", "coordinates" : [ 0, 0 ] }'))
  expect_error(geojson_wkt('{"type" : "MultiLineString", "coordinates" : [ [0, 0] ] }'))
  expect_error(geojson_wkt('{"type" : "Polygon", "coordinates" : [0, 0] }'))
  expect_error(geojson_wkt('{"type" : "Polygon", "coordinates" : [ [ 0, 0 ] ] }'))
  expect_error(geojson_wkt('{"type" : "MultiPolygon", "coordinates" : [ [0, 0] ] }'))
  expect_error(geojson_wkt('{"type" : "MultiPolygon", "coordinates" : [ [ [0, 0] ] ] }'))

  expect_error(geojson_sf('{"type" : "Point" , "coordinates" : {} }'))

})
