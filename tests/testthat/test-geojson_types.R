
context("types")


test_that("geojson types correctly captured in df", {

	## int & strings
	geo <- '
  {
    "type" : "Feature",
    "properties" : { "id" : 1, "val" : "a" },
    "geometry" : { "type" : "Point", "coordinates" : [0,0] }
	}'

	sf <- geojson_sf(geo)

	expect_true(
		all(c("geometry", "id", "val") %in% names(sf))
	)

	expect_true(
		nrow(sf) == 1
	)

	expect_true(
		is.numeric(sf[['id']])
	)

	## null property
	geo <- '
  {
    "type" : "Feature",
    "properties" : null,
    "geometry" : { "type" : "Point", "coordinates" : [0,0] }
	}'

	sf <- geojson_sf(geo)

	expect_true(
		all(names(sf) %in% c("geometry"))
	)

	## null property value
	geo <- '
  {
    "type" : "Feature",
    "properties" : { "id" : null },
    "geometry" : { "type" : "Point", "coordinates" : [0,0] }
	}'

	sf <- geojson_sf(geo)

	expect_true(
		all(names(sf) %in% c("geometry", "id"))
	)

	## logical property value
	geo <- '
	{
	"type" : "Feature",
	  "properties" : { "id" : true },
	  "geometry" : { "type" : "Point", "coordinates" : [0,0] }
	}'

	sf <- geojson_sf(geo)

	expect_true(
		all(names(sf) %in% c("geometry", "id"))
	)

	expect_true(
		is.logical(sf[['id']])
	)

	geo <- '
	{
	  "type" : "Feature",
	  "properties" : { "id" : { } },
	  "geometry" : { "type" : "Point", "coordinates" : [0,0] }
  }'

	sf <- geojson_sf(geo)

	## TODO:
	## - Object type converted to JSON string
	## - Array type converted to JSON string

})
