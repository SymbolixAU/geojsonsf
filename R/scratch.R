
### OBJECTS

# g <- '{"type": "Point", "coordinates": [100.0, 0.0]}'
#
# f <- '{
# 	"type": "Feature",
# 	"properties": null,
# 	"geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# 	}'
#
# gc <- '{
#     "type": "GeometryCollection",
#     "geometries": [
#         {"type": "Point", "coordinates": [100.0, 0.0]},
#         {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#         {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#     ]
# }'
#
# fc <- '{
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
#     "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
#   },
#   {
#     "type": "Feature",
# 	    "properties": null,
# 	    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# 	}
#  ]
# }'
#
#
# fc1 <- '{
#   "type": "FeatureCollection",
#   "features": [
#   {
#     "type": "Feature",
#     "properties": null,
#     "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
#   }]
# }'

# geojsonsf:::rcpp_geojson_to_sf(f)
# geojsonsf:::rcpp_geojson_to_sf(g)
# geojsonsf:::rcpp_geojson_to_sf(gc)
# geojsonsf:::rcpp_geojson_to_sf(fc1)
# geojsonsf:::rcpp_geojson_to_sf(fc)

# sf <- sf::st_read(g)
# sf
# sf <- sf::st_read(f)
# sf
# sf <- sf::st_read(gc)
# sf
# sf <- sf::st_read(fc)
# sf
# sf <- sf::st_read(fc1)  ## single FeatureCollection is the single geometry TYPE
# sf


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
#         {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#         {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#     ]
# }
# ]'

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
#     "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
#   },
#   {
#     "type": "Feature",
# 	    "properties": null,
# 	    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
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
# 	  "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# 	},
# 	{
# 	  "type": "Feature",
# 	  "properties": null,
# 	  "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# 	}
#   ]
# }
# ]'

# geojsonsf:::rcpp_geojson_to_sf(garr)
# geojsonsf:::rcpp_geojson_to_sf(gcarr)
# geojsonsf:::rcpp_geojson_to_sf(fcarr)




# library(RCurl)
# myurl <- "https://raw.githubusercontent.com/PublicaMundi/MappingAPI/master/data/geojson/us-states.json"
# geo <- readLines(url(myurl))
# geo <- paste0(geo, collapse = "")
# lst <- geojsonsf:::rcpp_geojson_to_sf(geo)
#

# sf <- sf::st_read(geo, quiet = T)

# str(st_geometry(sf))
# str(lst[[1]][[1]])

# library(microbenchmark)
#
# microbenchmark(
# 	geojsonsf = {
# 		geojsonsf:::rcpp_geojson_to_sf(geo)
# 	},
# 	sf = {
# 		sf::st_read(geo, quiet = T)
# 	},
# 	times = 2
# )
#
# Unit: milliseconds
#      expr       min        lq     mean   median        uq       max neval
# geojsonsf  2.342387  2.342387  2.56786  2.56786  2.793333  2.793333     2
#        sf 20.377601 20.377601 23.52943 23.52943 26.681269 26.681269     2

## mix of features gets class 'sfc_GEOMETRY'
## collection of the same featur egets sfc_TYPE
##
## is the 'classes' attribute necessary?

# nc <- st_read(system.file("shape/nc.shp", package="sf"))
#
# attributes(st_geometry(nc))

## Geometry
## - type: <POINT/LINESTRING/MULTIPOLYGON>
## - coordinates: [ (nested) array of coordinates ]


## Feature
## - type: 'Feature'
## - geometry:     (geometry object)
## - properties:  (the data)

## FeatureCollection
## - 'features' [ array of feature objects ]




# p1 = st_point(c(1,2))
# p2 = st_point(c(1,3))
# l1 <- st_linestring(matrix(1:6, ncol = 2))
#
# sf::st_sfc(list(p1, p2, l1))



# js <- "{\"type\": \"LineString\",\"coordinates\": [[30.5, 50.5], [30.6, 50.6], [25.0, 23.3]]}"
# geojsonsf:::rcpp_geojson_to_sf(js)
#
#
# library(geojsonio)
# library(microbenchmark)
#
# file <- system.file("examples", "california.geojson", package = "geojsonio")
#
# microbenchmark(
#   geojsonio = {
#     ## doesn't output as SF
#     out <- geojson_read(file)
#   },
#   geojsonsf = {
#     geo <- paste0(readLines(file), collapse = "")
#     geojsonsf:::rcpp_geojson_to_sf(geo)
#   },
#   sf = {
#     ## can sf handle a vector of geoJSON?
#     ## or non-Collections? (i.e., array of objects?), or character vector?
#     sf::st_read(file, quiet = T)
#   },
#   times = 2
# )

# Unit: milliseconds
#      expr        min         lq       mean     median          uq         max neval
# geojsonio 979.740715 979.740715 1527.85369 1527.85369 2075.966660 2075.966660     2
# geojsonsf   7.909611   7.909611    8.41771    8.41771    8.925809    8.925809     2
#        sf  56.938019  56.938019   67.65058   67.65058   78.363145   78.363145     2


# js <- '[
# {
#   "type": "Feature",
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
# "type": "Polygon",
#     "coordinates": [
#       [
#         [-10.0, -10.0],
#         [10.0, -10.0],
#         [10.0, 10.0],
#         [-10.0, -10.0]
#       ]
#     ]
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
# }
# ]'

#lst <- geojsonsf:::rcpp_geojson_to_sf(js)


# geo <- c("{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68152563269095,36.43764870908927]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67408758213843,36.43366018922779]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67708346361097,36.44208638659282]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67886661944996,36.44110273135671]}",
# 				 "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68089232041565,36.44173155205561]}")

# geojsonsf:::rcpp_geojson_to_sf(geo)
# sf::st_read(geo, quiet = T)


