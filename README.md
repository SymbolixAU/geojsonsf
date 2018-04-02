# geojsonsf
Conversion between sf and geojson


```
library(sf) ## for print methods
file <- system.file("examples", "california.geojson", package = "geojsonio")

geo <- paste0(readLines(file), collapse = "")
geojsonsf::geojson_sf(geo)

# Simple feature collection with 1 feature and 11 fields
# geometry type:  MULTIPOLYGON
# dimension:      XY
# bbox:           xmin: -124.4096 ymin: 32.53416 xmax: -114.1315 ymax: 42.00952
# epsg (SRID):    4326
# proj4string:    +proj=longlat +datum=WGS84 +no_defs
#  abbreviation   area    capital        city                       geometry     group # 
# houseseats landarea
# 1           CA 423968 Sacramento Los Angeles MULTIPOLYGON (((-120.2485 3... US States         53   403466
#         name population  statehood waterarea
# 1 California   38332521 1850-09-09     20502

```

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
