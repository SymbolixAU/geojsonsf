## sf to GeoJSON

## stream the data.frame, row by row.
##

# js <- '{"type" : "Point", "coordinates" : [0, 0]}'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)
#
# js <- '{"type" : "MultiPoint", "coordinates" : [ [0, 0], [1, 1] ]}'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)
#
# js <- '{"type" : "MultiLineString", "coordinates" : [ [ [0, 0], [1, 1] ] ]}'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)
#
# js <- '{"type" : "Polygon", "coordinates" : [ [ [0, 0], [1, 1] ] ]}'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)
#
# js <- '[{"type" : "Polygon", "coordinates" : [ [ [0, 0], [1, 1] ] ]},
# {"type" : "MultiLineString", "coordinates" : [ [ [0, 0], [1, 1] ], [[3,3],[4,4]] ]}]'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)

# js <- '{
#   "type": "GeometryCollection", "geometries": [
#     {"type": "Point", "coordinates": [100.0, 0.0]},
#     {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#     {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#   ]}'
# sf <- geojson_sf(js)
# j <- sf_geojson(sf)
#
# j
# gsub(" |\\n|\\r","",js)


# js <- '[{"type" : "Polygon", "coordinates" : [ [ [0, 0], [1, 1] ] ]},
# {"type" : "MultiLineString", "coordinates" : [ [ [0, 0], [1, 1] ] ]},
# {
#   "type": "GeometryCollection", "geometries": [
#     {"type": "Point", "coordinates": [100.0, 0.0]},
#     {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#     {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#   ]}
# ]'
# sf <- geojson_sf(js)
# sf
# sf_geojson(sf)

# js <- '[
# {
#   "type": "Feature",
#   "properties" : {},
#   "geometry": {
#   "type": "Polygon",
#   "coordinates": [[
# 	  [-10.0, -10.0],
#   	[10.0, -10.0],
#   	[10.0, 10.0],
#   	[-10.0, -10.0]]]
#   }
# },
# {
# 	"type": "Feature",
# 	"properties" : { "id" : 1, "foo" : false, "bar" : "world" },
# 	"geometry": {
# 	"type": "MultiPolygon",
# 	"coordinates": [
# 	[[[180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
# 	[170.0, 40.0], [180.0, 40.0]]],
# 	[[[-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],
# 	[-180.0, 40.0], [-170.0, 40.0]]]]
# 	}
# }
# ]'
# sf <- geojson_sf(js)
# sf_geojson(sf)
# geojson_sf( sf_geojson(sf) )



# js <- '{"type":"MultiPolygon","coordinates":[[[[0,0],[0,1],[1,1],[1,0],[0,0]]]]}'
# sf_geojson(geojson_sf(js))

# js <- '{
#   "type":"MultiLineString",
#   "coordinates":[
#     [
#       [0,0],[0,1],[1,1],[1,0],[0,0]
#     ],
#     [
#       [2,2],[2,3],[3,3],[3,2],[2,2]
#     ]
#   ]
# }'
#
# sf_geojson(geojson_sf(js))


# js <- '{
#   "type":"MultiPolygon",
#   "coordinates":[
#     [
#       [
#         [0,0],[0,1],[1,1],[1,0],[0,0]
#       ],
#       [
#         [0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]
#       ]
#     ],
#     [
#       [
#         [2,2],[2,3],[3,3],[3,2],[2,2]
#       ]
#     ]
#   ]
# }'
#
# sf_geojson(geojson_sf(js), TRUE)

# js <- '
# {
#   "type": "Feature",
#   "geometry": {
#     "type": "LineString",
#     "coordinates": [[100.0, 0.0], [101.0, 1.0]]
#   },
#   "properties": {
#   "prop0": "value0",
#   "prop1": "value1"
#   }
# }'
# geojson_sf(js)

# fgc <- '
# {
#   "type": "Feature",
#   "geometry": {
#     "type": "GeometryCollection",
#      "geometries": [
#       {
# 	      "type": "Point",
# 	      "coordinates": [100.0, 0.0]
#       },
# 	    {
# 	      "type": "LineString",
# 	      "coordinates": [
#           [101.0, 0.0], [102.0, 1.0]
#         ]
#       }
# 	  ]
#   },
# 	"properties": {
# 	  "prop0": "value0",
# 	  "prop1": "value1"
# 	}
# }'

# geojson_sf(fgc)


# js <- '{
#   "type": "GeometryCollection", "geometries": [
#     {"type": "Point", "coordinates": [100.0, 0.0]},
#     {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#     {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#   ]}'
# geojson_sf(js)
