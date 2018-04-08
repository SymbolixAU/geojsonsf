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
# geojsonsf:::rcpp_sf_to_geojson(sf)
#
# js <- '{"type" : "MultiPoint", "coordinates" : [ [0, 0], [1, 1] ]}'
# sf <- geojson_sf(js)
# sf
# geojsonsf:::rcpp_sf_to_geojson(sf)
#
# js <- '{"type" : "Polygon", "coordinates" : [ [ [0, 0], [1, 1] ] ]}'
# sf <- geojson_sf(js)
# sf
# geojsonsf:::rcpp_sf_to_geojson(sf)

# library(Rcpp)
#
# cppFunction('Rcpp::NumericMatrix mymat(Rcpp::NumericVector vec) {
#   vec.attr("dim") = Dimension(2, 2);
#   Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix>(vec);
#   return m;
# }')
#
# mymat(c(1:4))




