

## TODO:

# library(Rcpp)
#
# cppFunction('Rcpp::NumericVector vec() {
#   Rcpp::NumericVector point(2);
#   point[0] = NA_REAL;
#   return point;
# }')
#
# vec()
#
#
# js <- '{"type":"Point","coordinates":[null,null]}'
# sf::st_read(js)
#
# js <- '{"type":"Point","coordinates":[,]}'
# sf::st_read(js)
#
# js <- '{"type":"Point","coordinates":[]}'
# sf::st_read(js)
#
# js <- '{"type":"Point","coordinates":{}}'
# sf::st_read(js)
#
# url <- "https://data.seattle.gov/resource/pdbw-sw7q.geojson"
# sf <- sf::st_read(url, quiet = T)
#
# js <- '{"type","Feature","geometry":null}'
# sf::st_read(js)
#
# js <- '{"type","Feature","geometry":null,"properties":{}}'
# sf::st_read(js)
#
## NULL geometry should be fine / parse
# js <- '{"type":"FeatureCollection","features":[
# {"type":"Feature","properties":{"id":1},"geometry":{"type":"Point","coordinates":[0,0]}},
# {"type":"Feature","properties":{"id":2},"geometry":null}
# ]}'
# sf <- sf::st_read(js)
# sf
# geojson_sf(js)


# js <- '{"type":"Feature","properties":{"id":2},"geometry": null}'
# sf <- sf::st_read(js)
# sf2 <- geojson_sf(js)

# sf
# sf2
#
# str(sf)
# str(sf2)
#
# str(sf$geometry)
# str(sf2$geometry)
#
# attr(sf2$geometry, "class") <- c("sfc_POLYGON", "sfc")
#
# str(sf)
# str(sf2) ## the 'id' value is missing
#
# str(sf$geometry)
# str(sf2$geometry)

