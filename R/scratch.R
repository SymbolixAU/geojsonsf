## CLASSES

## are they only attached when there are mixxed geometries?

## test
## url string
## connection
## file (local)
## file from package
##

# url <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_outline_500k.json"
# sf <- geojson_sf(url)

# url <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
# sf <- geojson_sf(url)
#
# con <- curl::curl(url)
# sf <- geojson_sf(con)
#
# f <- system.file("examples", "california.geojson", package = "geojsonio")
# sf <- geojson_sf(f)

# geojson_sf(("~/Desktop/myjson.json"))


# url <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
# sf <- geojson_sfc(url)
#
# con <- curl::curl(url)
# sf <- geojson_sfc(con)
#
# f <- system.file("examples", "california.geojson", package = "geojsonio")
# sf <- geojson_sfc(f)
#
# geojson_sfc(("~/Desktop/myjson.json"))


# g <- gsf$geometry
#
# g
#
# sfg <- sf::st_sf(g)
# attributes(sfg$g)
#
# library(Rcpp)
#
# con <- curl::curl(url = "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json")
# geo <- readLines(con)
#
#
# cppFunction('Rcpp::StringVector cppPaste(Rcpp::StringVector sv) {
#
#   std::ostringstream os;
#   for (int i = 0; i < sv.size(); i++) {
#     os << sv[i];
#   }
#
#   return os.str();
#
# }')
#
# geo1 <- cppPaste(geo)
#
# geojsonsf::geojson_sf(geo1)
#
# library(microbenchmark)
#
# microbenchmark(
# 	rcpp = {
# 		cppPaste(geo)
# 	},
# 	base = {
# 		paste0(geo)
# 	},
# 	times = 5
# )
