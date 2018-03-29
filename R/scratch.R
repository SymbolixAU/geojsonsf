
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
