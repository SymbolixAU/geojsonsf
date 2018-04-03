context("objects")


test_that("individual objects converted to sf", {

	g <- '{"type": "Point", "coordinates": [100.0, 0.0]}'

	f <- '{
		"type": "Feature",
		"properties": null,
		"geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
		}'

	gc <- '{
	    "type": "GeometryCollection",
	    "geometries": [
	        {"type": "Point", "coordinates": [100.0, 0.0]},
	        {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
	        {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
	    ]
	}'

	fc <- '{
	  "type": "FeatureCollection",
	  "features": [
	  {
	    "type": "Feature",
	    "properties": {"foo" : "feature 1.1", "bar" : "feature 1.2"},
	    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
	  },
	  {
	    "type": "Feature",
	    "properties": null,
	    "geometry": {"type": "LineString", "coordinates": [[103.0, 0.0], [102.0, 1.0]]}
	  },
	  {
	    "type": "Feature",
		    "properties": {"foo" : "feature 3.1", "bar" : "feature 3.2"},
		    "geometry": {"type": "LineString", "coordinates": [[109.0, 0.0], [102.0, 1.0]]}
		}
	 ]
	}'


	fc1 <- '{
	  "type": "FeatureCollection",
	  "features": [
	  {
	    "type": "Feature",
	    "properties": null,
	    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
	  }]
	}'

	sf_f <- geojson_sf(f)
	sf_g <- geojson_sf(g)
	sf_gc <- geojson_sf(gc)
	sf_fc1 <- geojson_sf(fc1)
	sf_fc <- geojson_sf(fc)

	expect_true("sf" %in% class(sf_f))
	expect_true("sf" %in% class(sf_g))
	expect_true("sf" %in% class(sf_gc))
	expect_true("sf" %in% class(sf_fc1))
	expect_true("sf" %in% class(sf_fc))

	expect_true(
		all.equal(
			attr(sf_f$geometry, "class"), c("sfc_LINESTRING", "sfc")
		)
	)

	expect_true(
		all.equal(
			attr(sf_g$geometry, "class"), c("sfc_POINT", "sfc")
		)
	)

	expect_true(
		all.equal(
			attr(sf_gc$geometry, "class"), c("sfc_GEOMETRY", "sfc")
		)
	)

	expect_true(
		all.equal(
			attr(sf_fc1$geometry, "class"), c("sfc_POINT", "sfc")
		)
	)

	expect_true(
		all.equal(
			attr(sf_fc$geometry, "class"), c("sfc_GEOMETRY", "sfc")
		)
	)

})
