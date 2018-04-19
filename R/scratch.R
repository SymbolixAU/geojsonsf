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
# {"type" : "MultiLineString", "coordinates" : [ [ [0, 0], [1, 1] ] ]}]'
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
# sf
# sf_geojson(sf)


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
# 	sf <- geojson_sf(js)
# 	sf_geojson(sf)

