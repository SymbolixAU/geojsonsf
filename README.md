
[![Travis build status](https://travis-ci.org/SymbolixAU/geojsonsf.svg?branch=master)](https://travis-ci.org/SymbolixAU/geojsonsf)
[![Coverage status](https://codecov.io/gh/SymbolixAU/geojsonsf/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/geojsonsf?branch=master)

# geojsonsf

Converts 

- GeoJSON -> sf
- GeoJSON -> wkt


## Install

This is a development package so can be installed directly from github

```
devtools::install_github("SymbolixAU/geojsonsf")
```

## Motivation

To quickly parse GeoJSON to `sf` objects, and to handle cases not supported by `sf`, e.g. arrays of geometries

### Array of geometries

```{r}

js <- '[
{
  "type": "FeatureCollection",
  "features": [
  {
    "type": "Feature",
    "properties": null,
    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
  },
  {
    "type": "Feature",
    "properties": null,
    "geometry": {"type": "LineString", "coordinates": [[201.0, 0.0], [102.0, 1.0]]}
  },
  {
    "type": "Feature",
	    "properties": null,
	    "geometry": {"type": "LineString", "coordinates": [[301.0, 0.0], [102.0, 1.0]]}
	}
 ]
},
{
  "type": "FeatureCollection",
	"features": [
	{
	  "type": "Feature",
	  "properties": null,
	  "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
	},
	{
	  "type": "Feature",
	  "properties": null,
	  "geometry": {"type": "LineString", "coordinates": [[501.0, 0.0], [102.0, 1.0]]}
	},
	{
	  "type": "Feature",
	  "properties": null,
	  "geometry": {"type": "LineString", "coordinates": [[601.0, 0.0], [102.0, 1.0]]}
	}
  ]
}
]'

geojson_sf(js)

```

### Speed

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

myurl <- "https://raw.githubusercontent.com/rowanhogan/australian-states/master/states.min.geojson"

geo <- readLines(url(myurl))

microbenchmark(
  geojson_sf = {
    geojson_sf(geo)
  },
  geojson_wkt = {
    geojson_wkt(geo)
  },
  sf = {
    sf::st_read(geo, quiet = T)
  },
  #wellknown = {
  #  wellknown::geojson2wkt(geo)
  #},
  times = 2
)

```

## Examples

### Geometry
```{r}
library(geojsonsf)
library(sf)        ## for sf print methods

g <- '{"type": "Point", "coordinates": [100.0, 0.0]}'
geojson_sf(g)
```

### Feature
```{r}
f <- '{
	"type": "Feature",
	"properties": null,
	"geometry": {
	  "type": "LineString", 
	  "coordinates": [[101.0, 0.0], [102.0, 1.0]]
	  }
	}'
geojson_sf(f)
```


## Geometry Collection

```{r}
gc <- '{
  "type": "GeometryCollection",
  "geometries": [
    {"type": "Point", "coordinates": [100.0, 0.0]},
    {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
    {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
  ]
}'
geojson_sf(gc)
```

### Feature Collection

```{r}
fc <- '{
  "type": "FeatureCollection",
  "features": [
  {
    "type": "Feature",
    "properties": {"foo" : "feature 1.1", "bar" : "feature 1.2"},
    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
  },
  {
    "type": "Feature",
    "properties": null,
    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
  },
  {
    "type": "Feature",
	    "properties": {"foo" : "feature 3.1", "bar" : "feature 3.2"},
	    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
	}
 ]
}'
geojson_sf(fc)
```

Reading from file (using `geojsonio` data)

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
## Well-known Text

It also converts GeoJSON to Well-Known Text and returns a `data.frame`


```
fc <- '{
  "type": "FeatureCollection",
  "features": [
  {
    "type": "Feature",
    "properties": {"foo" : "feature 1.1", "bar" : "feature 1.2"},
    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
  },
  {
    "type": "Feature",
    "properties": null,
    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
  },
  {
    "type": "Feature",
	    "properties": {"foo" : "feature 3.1", "bar" : "feature 3.2"},
	    "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
	}
 ]
}'
geojson_wkt(fc)
```


