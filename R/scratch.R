#
# myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
#
# library(microbenchmark)
#
# microbenchmark(
# 	geojsonsf = {
# 		geojson_sf(myurl)
# 	},
# 	sf = {
# 		sf::st_read(myurl, quiet = T)
# 	},
# 	times = 2
# )
#
#
#
# myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
# geo <- readLines(myurl)
# geo <- paste0(geo, collapse = "")
#
# library(microbenchmark)
#
# microbenchmark(
# 	geojsonsf = {
# 		geojson_sf(geo)
# 	},
# 	sf = {
# 		sf::st_read(geo, quiet = T)
# 	},
# 	times = 2
# )
