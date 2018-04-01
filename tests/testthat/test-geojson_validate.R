
context("validate")

test_that("Geometry object has correct members", {

	## type : Point
	## Must have
	## - coordinates : [ ]

	## no 'coordinates' array
	js <- '
	{
    "type" : "Point",
    "coordinate" : [ 0, 0 ]
	}'

	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'coordinates' member at object index 0 - invalid GeoJSON"
	)

	## no 'type' key
	js <- '
	{
	  "geometry" : "Point",
	  "coordinates" : [ 0, 0 ]
  }'

	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'type' member at object index 0 - invalid GeoJSON"
	)

})

test_that("Feature Object has correct members", {

	## type : Feature
	## MUST HAVE
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


test_that("Featurecollection has correct members", {

  ## Feature Colection
	## MUST HAVE
	## - features

	## invalid 'feature'
	js <- '
  {
    "type": "FeatureCollection",
	  "feature": [
	    {
	      "type": "Feature",
	      "properties": null,
	      "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
	    },
	    {
	      "type": "Feature",
	      "properties": null,
	      "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
	    },
 	    {
	      "type": "Feature",
	      "properties": null,
	      "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
	    }
	  ]
  }'

	expect_error(
		geojsonsf:::rcpp_geojson_to_sf(js),
		"No 'features' member at object index 0 - invalid GeoJSON"
	)

})



