## TODO
## - nested arrays / objects inside properties
## - test erroneous inputs
## - no need to use / call / create 'properties' in construct_sfc

## - don't attach 'sfc' or 'sf' attributes



## wellknown can't handle properties?
# install.packages("wellknown")
#
# library(RCurl)
# myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
# geo <- readLines(url(myurl))
# geo <- paste0(geo, collapse = "")
#
# library(microbenchmark)
#
# str <- '{"type":"LineString","coordinates":[[0,0,10],[2,1,20],[4,2,30],[5,4,40]]}'
# wellknown::geojson2wkt(str)
#
# microbenchmark(
# 	geojsonsf = {
# 		geojson_wkt(geo)
# 	},
# 	wellknown = {
# 		wellknown::geojson2wkt(geo)
# 	},
# 	times = 2
# )

