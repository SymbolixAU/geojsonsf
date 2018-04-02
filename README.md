# geojsonsf
Conversion between sf and geojson

---

Some benchmark

```
library(RCurl)
myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
geo <- readLines(url(myurl))
geo <- paste0(geo, collapse = "")

library(microbenchmark)

microbenchmark(
	geojsonsf = {
		geojson_sf(geo)
	},
	sf = {
		sf::st_read(geo, quiet = T)
	},
	times = 2
)
# Unit: seconds
#       expr      min       lq     mean   median       uq      max neval
#  geojsonsf 1.049637 1.049637 1.073559 1.073559 1.097481 1.097481     2
#         sf 4.445201 4.445201 4.565980 4.565980 4.686758 4.686758     2
```
