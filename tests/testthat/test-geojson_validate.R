
context("validate")


test_that("Feature Object has correct members", {

	## MUST HAVE
	## - type : Feature
	## - geometry : {}
	## - properties : {}


	## invalid 'geometry' member
	js <- '
  {
    "type" : "Feature",
    "properties" : {},
    "geom" : {
      "type" : "Point",
      "coordinates" : [ 0, 0]
    }
  }
	'
	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'geometry' member at object index 0 - invalid GeoJSON"
	)

	## invalid 'properties' member
	js <- '
	{
	  "type" : "Feature",
	  "property" : {},
	  "geometry" : {
	    "type" : "Point",
	    "coordinates" : [ 0, 0]
	  }
	}
	'
	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'properties' member at object index 0 - invalid GeoJSON"
	)

	js <- '
	[
    {
	    "type" : "Feature",
	    "properties" : {},
	    "geometry" : {
	      "type" : "Point",
	      "coordinates" : [ 0, 0]
	    }
    },
	  {
	    "type" : "Feature",
	    "property" : {},
	    "geometry" : {
	      "type" : "Point",
	      "coordinates" : [ 0, 0]
	    }
	  }
  ]
	'
	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'properties' member at object index 1 - invalid GeoJSON"
	)


})




