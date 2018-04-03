### ARRAYS

# garr <- '[
#   {
#     "type": "Point",
#     "coordinates": [
#       100.0, 0.0
#     ]
#   },
#   {
#     "type": "Point",
#       "coordinates": [
#         100.0, 0.0
#     ]
#   }
# ]'
#
# gcarr <- '[{
#     "type": "GeometryCollection",
#     "geometries": [
#         {"type": "Point", "coordinates": [100.0, 0.0]},
#         {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#         {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#     ]
# },
# {
#     "type": "GeometryCollection",
#     "geometries": [
#         {"type": "Point", "coordinates": [100.0, 0.0]},
#         {"type": "LineString", "coordinates": [[201.0, 0.0], [202.0, 1.0]]},
#         {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#     ]
# }
# ]'
#
# fcarr <- '[
# {
#   "type": "FeatureCollection",
#   "features": [
#   {
#     "type": "Feature",
#     "properties": null,
#     "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
#   },
#   {
#     "type": "Feature",
#     "properties": null,
#     "geometry": {"type": "LineString", "coordinates": [[201.0, 0.0], [102.0, 1.0]]}
#   },
#   {
#     "type": "Feature",
# 	    "properties": null,
# 	    "geometry": {"type": "LineString", "coordinates": [[301.0, 0.0], [102.0, 1.0]]}
# 	}
#  ]
# },
# {
#   "type": "FeatureCollection",
# 	"features": [
# 	{
# 	  "type": "Feature",
# 	  "properties": null,
# 	  "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
# 	},
# 	{
# 	  "type": "Feature",
# 	  "properties": null,
# 	  "geometry": {"type": "LineString", "coordinates": [[501.0, 0.0], [102.0, 1.0]]}
# 	},
# 	{
# 	  "type": "Feature",
# 	  "properties": null,
# 	  "geometry": {"type": "LineString", "coordinates": [[601.0, 0.0], [102.0, 1.0]]}
# 	}
#   ]
# }
# ]'

# geojson_sf(garr)
# geojson_sf(gcarr)
# geojson_sf(fcarr)

## PROPERTIES

# f <- '{
# 	"type": "Feature",
# 	"properties": { "id" : 1, "name" : "foo" },
# 	"geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# 	}'
#
# geojson_sf(f)


# js <- '[
# {
#   "type": "Feature",
#   "properties" : {},
#   "geometry": {
#     "type": "Polygon",
#     "coordinates": [
#       [
#         [-10.0, -10.0],
#         [10.0, -10.0],
#         [10.0, 10.0],
#         [-10.0, -10.0]
#       ]
#     ]
#   }
# },
# {
#   "type": "Feature",
#   "properties" : { "id" : 1 },
#   "geometry": {
#     "type": "MultiPolygon",
#     "coordinates": [
#       [
#         [
#           [180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
#           [170.0, 40.0], [180.0, 40.0]
#         ]
#       ],
#       [
#         [
#           [-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],
#           [-180.0, 40.0], [-170.0, 40.0]
#         ]
#       ]
#     ]
#   }
# },
# {
#   "type": "FeatureCollection",
#   "features": [
#     {
#       "type": "Feature",
#       "properties": null,
#       "geometry": {
#         "type": "Point",
#         "coordinates": [100.0, 0.0]
#       }
#     },
#     {
#       "type": "Feature",
#       "properties": null,
#       "geometry": {
#         "type": "LineString",
#         "coordinates": [
#           [101.0, 0.0],
#           [102.0, 1.0]
#         ]
#       }
#     }
#   ]
# },
# {
#   "type": "GeometryCollection",
#   "geometries": [
#     {
#       "type": "Point",
#       "coordinates": [100.0, 0.0]
#     },
#     {
#       "type": "LineString",
#       "coordinates": [
#         [101.0, 0.0],
#         [102.0, 1.0]
#       ]
#     },
#     {
#       "type" : "MultiPoint",
#       "coordinates" : [
#         [0,0],
#         [1,1],
#         [2,2]
#       ]
#     }
#   ]
# },
# {
# "type": "Polygon",
#     "coordinates": [
#       [
#         [-10.0, -10.0],
#         [10.0, -10.0],
#         [10.0, 10.0],
#         [-10.0, -10.0]
#       ]
#     ]
# }
# ]'
# sf <- geojson_sf(js)


# geo <- c("{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68152563269095,36.43764870908927]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67408758213843,36.43366018922779]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67708346361097,36.44208638659282]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67886661944996,36.44110273135671]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68089232041565,36.44173155205561]}")

# geojsonsf:::rcpp_geojson_to_sf(geo)
# sf::st_read(geo, quiet = T)

