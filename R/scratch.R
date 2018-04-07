## TODO
## - nested arrays / objects inside properties
## - test erroneous inputs
## - no need to use / call / create 'properties' in construct_sfc

## - don't attach 'sfc' or 'sf' attributes

## TODO:
## - handle incorrectly formed geometry type
## -- e.g., MultiPoint with only one-nested array


# p <- '{ "type" : "Point", "coordinates" : [0, 0] }'
#
# mp <- '{ "type" : "MultiPoint", "coordinates" : [ [0, 0], [2.324, 2] ] }'
#
# ls <- '{ "type" : "LineString", "coordinates" : [ [0, 0], [1, 1] ] }'
#
# ml <- '{"type": "MultiLineString","coordinates": [
# 	    [[100.0, 0.0],[101.0, 1.0]],[[102.0, 2.0],[103.0, 3.0]]
# ]}'
#
# poly <- '{"type": "Polygon","coordinates": [[
# 				[180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
# 				[170.0, 40.0], [180.0, 40.0]
# 				]]}'
#
# mpoly <- '{
#   "type": "MultiPolygon",
#   "coordinates": [
#     [
#       [
# 			  [180.0, 40.0],
#         [180.0, 50.0],
#         [170.0, 50.0],
# 				[170.0, 40.0],
#         [180.0, 40.0]
# 			],
#       [
#         [0, 0],
#         [1, 1],
#         [2, 2],
#         [2, 0]
#       ]
#     ],
#     [
#       [
# 		    [-170.0, 40.0],
#         [-170.0, 50.0],
#         [-180.0, 50.0],
# 			  [-180.0, 40.0],
#         [-170.0, 40.0]
# 			]
#     ]
#   ]
# }'
#
# gc <- '{
# 		"type": "GeometryCollection",
# "geometries": [
# {"type": "Point", "coordinates": [100.0, 0.0]},
# {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
# {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
# ]
# }'

# geojson_wkt(p)
# geojson_wkt(mp)
# geojson_wkt(ls)
# geojson_wkt(ml)
# geojson_wkt(poly)
# geojson_wkt(mpoly)
# geojson_wkt(gc)

## wellknown can't handle properties?
# install.packages("wellknown")
#
# library(RCurl)
# myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
# geo <- readLines(url(myurl))
# geo <- paste0(geo, collapse = "")
#
# library(microbenchmark)
#
# str <- '{"type":"LineString","coordinates":[[0,0,10],[2,1,20],[4,2,30],[5,4,40]]}'
# wellknown::geojson2wkt(str)
#
# microbenchmark(
# 	geojsonsf = {
# 		geojson_wkt(geo)
# 	},
# 	wellknown = {
# 		wellknown::geojson2wkt(geo)
# 	},
# 	times = 2
# )

