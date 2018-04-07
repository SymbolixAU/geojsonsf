context("wkt")

test_that("wkt created correctly", {


	p <- '{ "type" : "Point", "coordinates" : [0, 0] }'

	mp <- '{ "type" : "MultiPoint", "coordinates" : [ [0, 0], [2.324, 2] ] }'

	ls <- '{ "type" : "LineString", "coordinates" : [ [0, 0], [1, 1] ] }'

	ml <- '{"type": "MultiLineString","coordinates": [
		    [[100.0, 0.0],[101.0, 1.0]],[[102.0, 2.0],[103.0, 3.0]]
	]}'

	poly <- '{"type": "Polygon","coordinates": [[
					[180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
					[170.0, 40.0], [180.0, 40.0]
					]]}'

	mpoly <- '{
	  "type": "MultiPolygon",
	  "coordinates": [
	    [
	      [
				  [180.0, 40.0],
	        [180.0, 50.0],
	        [170.0, 50.0],
					[170.0, 40.0],
	        [180.0, 40.0]
				],
	      [
	        [0, 0],
	        [1, 1],
	        [2, 2],
	        [2, 0]
	      ]
	    ],
	    [
	      [
			    [-170.0, 40.0],
	        [-170.0, 50.0],
	        [-180.0, 50.0],
				  [-180.0, 40.0],
	        [-170.0, 40.0]
				]
	    ]
	  ]
	}'

	gc <- '{
			"type": "GeometryCollection",
	"geometries": [
	{"type": "Point", "coordinates": [100.0, 0.0]},
	{"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
	{"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
	]
	}'

	p <- geojson_wkt(p)
	mp <- geojson_wkt(mp)
	ls <- geojson_wkt(ls)
	ml <- geojson_wkt(ml)
	poly <- geojson_wkt(poly)
	mpoly <- geojson_wkt(mpoly)
	gc <- geojson_wkt(gc)

	expect_true(
		class(p) == "data.frame"
	)
	expect_true(
		class(mp) == "data.frame"
	)
	expect_true(
		class(ml) == "data.frame"
	)
	expect_true(
		class(poly) == "data.frame"
	)
	expect_true(
		class(mpoly) == "data.frame"
	)
	expect_true(
		class(gc) == "data.frame"
	)

})
