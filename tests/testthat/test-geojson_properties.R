context("properties")

test_that("properties captured correctly", {

	f <- '{
		"type": "Feature",
		"properties": { "id" : 1, "name" : "foo" },
		"geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
		}'

	sf <- geojson_sf(f)
	wkt <- geojson_wkt(f)

	expect_true(
		all(names(sf) == c("geometry", "id", "name"))
	)
	expect_true(
		all(names(wkt) == c("geometry", "id", "name"))
	)

	expect_true(
	  sf$id == 1
	)
	expect_true(
		wkt$id == 1
	)
	expect_true(
		sf$name == "foo"
	)
	expect_true(
		wkt$name == "foo"
	)

	js <- '[
	{
	  "type": "Feature",
	  "properties" : {},
	  "geometry": {
	    "type": "Polygon",
	    "coordinates": [
	      [
	        [-10.0, -10.0],
	        [10.0, -10.0],
	        [10.0, 10.0],
	        [-10.0, -10.0]
	      ]
	    ]
	  }
	},
	{
	  "type": "Feature",
	  "properties" : { "id" : 1 },
	  "geometry": {
	    "type": "MultiPolygon",
	    "coordinates": [
	      [
	        [
	          [180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
	          [170.0, 40.0], [180.0, 40.0]
	        ]
	      ],
	      [
	        [
	          [-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],
	          [-180.0, 40.0], [-170.0, 40.0]
	        ]
	      ]
	    ]
	  }
	},
	{
	  "type": "FeatureCollection",
	  "features": [
	    {
	      "type": "Feature",
	      "properties": {"id" : 2, "value" : "foo"},
	      "geometry": {
	        "type": "Point",
	        "coordinates": [100.0, 0.0]
	      }
	    },
	    {
	      "type": "Feature",
	      "properties": null,
	      "geometry": {
	        "type": "LineString",
	        "coordinates": [
	          [101.0, 0.0],
	          [102.0, 1.0]
	        ]
	      }
	    }
	  ]
	},
	{
	  "type": "GeometryCollection",
	  "geometries": [
	    {
	      "type": "Point",
	      "coordinates": [100.0, 0.0]
	    },
	    {
	      "type": "LineString",
	      "coordinates": [
	        [101.0, 0.0],
	        [102.0, 1.0]
	      ]
	    },
	    {
	      "type" : "MultiPoint",
	      "coordinates" : [
	        [0,0],
	        [1,1],
	        [2,2]
	      ]
	    }
	  ]
	},
	{
	"type": "Polygon",
	    "coordinates": [
	      [
	        [-10.0, -10.0],
	        [10.0, -10.0],
	        [10.0, 10.0],
	        [-10.0, -10.0]
	      ]
	    ]
	}
	]'
	sf <- geojson_sf(js)
	wkt <- geojson_wkt(js)

	expect_true(
		ncol(sf) == 3
	)
	expect_true(
		ncol(wkt) == 3
	)
	expect_true(
		sum(sf$id, na.rm = T) == 3
	)
	expect_true(
		sum(wkt$id, na.rm = T) == 3
	)
	expect_true(
		sf$value[!is.na(sf$value)] == "foo"
	)
	expect_true(
		wkt$value[!is.na(wkt$value)] == "foo"
	)


})
