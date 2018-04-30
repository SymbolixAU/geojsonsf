## TODO:
## null geometries in GeoJSON
## - does it go the other way too?
## - e.g. if there's a null geometry in 'sf', how is it written to GeoJSON?


## NULL geometry
# url <- "https://data.seattle.gov/resource/pdbw-sw7q.geojson"
# sf <- sf::st_read(url, quiet = T)
# sf2 <- geojson_sf(url)


# js <- '{"type":"FeatureCollection","features":[
# {"type":"Feature","properties":{"id":2},"geometry":null},
# {"type":"Feature","properties":{"id":1},"geometry":{"type":"Point","coordinates":[0,0]}}
# ]}'
#
# sf <- sf::st_read(js)
#
# sf_geojson(sf)
#
#
# js <- '{"type":"FeatureCollection","features":[
# {"type":"Feature","properties":{"id":1},"geometry":{"type":"LineString","coordinates":[[0,0],[1,1]]}},
# {"type":"Feature","properties":{"id":2},"geometry":null}
# ]}'
#
# sf <- sf::st_read(js)
#
# sf_geojson(sf)

# ## TODO:
# ## - there needs to handle the case where the `sf` object will have any geometry type.
# ## - in this example, it's a POLYGON.
#
# ## - whereas I've currently specified it to create an Empty POINT:
# sf <- geojson_sf(js)
# ## - Therefore, when using `sf_geojson(sf)` on the `sf::st_read()` version, it doesn't
# ## - work correctly.


