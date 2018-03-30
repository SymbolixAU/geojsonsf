# geojsonsf
Conversion between sf and geojson

---

Some benchmark

```
# library(RCurl)
# myurl <- "https://raw.githubusercontent.com/PublicaMundi/MappingAPI/master/data/geojson/us-states.json"
# geo <- readLines(url(myurl))
# geo <- paste0(geo, collapse = "")
# geojsonsf:::rcpp_geojson_to_sf(geo)
#
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
```
