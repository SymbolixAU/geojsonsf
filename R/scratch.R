## TODO
## - nested arrays / objects inside properties
## - test erroneous inputs
## - no need to use / call / create 'properties' in construct_sfc

## - don't attach 'sfc' or 'sf' attributes

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



# library(Rcpp)
#
# cppFunction('Rcpp::NumericMatrix mymat(Rcpp::NumericVector vec) {
#   vec.attr("dim") = Dimension(1, 2);
#   Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix>(vec);
#   return m;
# }')
#
# mymat(c(1:2))




