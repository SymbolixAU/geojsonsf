geojsonsf
================

[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/geojsonsf)](http://cran.r-project.org/package=geojsonsf)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/geojsonsf)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/geojsonsf)](http://cran.r-project.org/web/packages/geojsonsf/index.html)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/geojsonsf.svg?style=social&label=Github)](https://github.com/SymbolixAU/geojsonsf)
[![Build
Status](https://travis-ci.org/SymbolixAU/geojsonsf.svg?branch=master)](https://travis-ci.org/SymbolixAU/geojsonsf)
[![Coverage
Status](https://codecov.io/github/SymbolixAU/geojsonsf/coverage.svg?branch=master)](https://codecov.io/github/SymbolixAU/geojsonsf?branch=master)

geojsonsf
---------

**v0.3+**

(Development / github version)

Added conversions

-   `sf` –&gt; GeoJSON
-   `sfc` –&gt; GeoJSON

**v0.2**

Converts

-   GeoJSON –&gt; `sf`
-   GeoJSON –&gt; `sfc`
-   GeoJSON –&gt; Well-known text

As per GeoJSON ([RFC 7946
specification)](https://tools.ietf.org/html/rfc7946#page-11), foreign
members are ignored, and nested objects and arrays inside the
`properties` object are converted to string/characters.

Installation
------------

When released on CRAN you install it in the usual way

``` r
install.packages("geojsonsf")
```

Install the development version from GitHub with

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/geojsonsf")
```

Motivation
----------

To quickly parse GeoJSON to `sf` objects, and to handle cases not
supported by `sf`, e.g. arrays of geometries

### Array of geometries

``` r
library(geojsonsf)
#  
#  Attaching package: 'geojsonsf'
#  The following object is masked from 'package:googleway':
#  
#      geo_melbourne
library(sf)        ## for sf print methods
#  Linking to GEOS 3.6.1, GDAL 2.1.3, proj.4 4.9.3

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
#  Simple feature collection with 6 features and 0 fields
#  geometry type:  GEOMETRY
#  dimension:      XY
#  bbox:           xmin: 100 ymin: 0 xmax: 601 ymax: 1
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#                     geometry
#  1             POINT (100 0)
#  2 LINESTRING (201 0, 102 1)
#  3 LINESTRING (301 0, 102 1)
#  4             POINT (100 0)
#  5 LINESTRING (501 0, 102 1)
#  6 LINESTRING (601 0, 102 1)
```

### Speed

This benchmark shows a comparison with `library(sf)` for converting a
string of GeoJSON of 3,221 counties in the US in to an `sf` object

``` r
myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
geo <- readLines(myurl)
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
#  Unit: seconds
#        expr      min       lq     mean   median       uq      max neval
#   geojsonsf 1.718010 1.718010 1.812560 1.812560 1.907110 1.907110     2
#          sf 5.269319 5.269319 5.496132 5.496132 5.722944 5.722944     2
```

Reading directly from a URL is comparable between the two

``` r
myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"

library(microbenchmark)

microbenchmark(
    geojsonsf = {
        geojson_sf(myurl)
    },
    sf = {
        sf::st_read(myurl, quiet = T)
    },
    times = 2
)
#  Unit: seconds
#        expr      min       lq     mean   median       uq      max neval
#   geojsonsf 10.06078 10.06078 12.53540 12.53540 15.01002 15.01002     2
#          sf 11.65602 11.65602 12.04578 12.04578 12.43554 12.43554     2
```

    library(rgdal)
    microbenchmark(
        gdal = {
        readOGR(myurl, "OGRGeoJSON")
        },
        geojsonsf = {
            myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
            geo <- readLines(myurl)
            geo <- paste0(geo, collapse = "")
            geojson_sf(geo)
        },
        times = 5
    )
    #      expr      min       lq     mean   median       uq      max neval
    #      gdal 58.51037 60.05683 66.33925 65.07506 72.08371 75.97028     5
    # geojsonsf 11.91515 13.37422 14.02232 13.88782 14.61826 16.31612     5

A visual check to see both objects are the same

``` r
library(googleway)
gsf <- geojson_sf(geo)

google_map() %>%
    add_polygons(gsf[!gsf$STATE %in% c("02","15","72"), ], 
            fill_colour = "CENSUSAREA", 
            stroke_weight = 0)
```

<img src="./man/figures/GeoJSONSF.png" width="100%" />

``` r
sf <- st_read(geo, quiet = T)
plot(st_geometry(sf[!sf$STATE %in% c("02", "15", "72"), ]))
```

<img src="man/figures/README-unnamed-chunk-8-1.png" width="100%" />

sf to GeoJSON
-------------

``` r
nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#  Reading layer `nc' from data source `/Library/Frameworks/R.framework/Versions/3.4/Resources/library/sf/shape/nc.shp' using driver `ESRI Shapefile'
#  Simple feature collection with 100 features and 14 fields
#  geometry type:  MULTIPOLYGON
#  dimension:      XY
#  bbox:           xmin: -84.32385 ymin: 33.88199 xmax: -75.45698 ymax: 36.58965
#  epsg (SRID):    4267
#  proj4string:    +proj=longlat +datum=NAD27 +no_defs
geo <- sf_geojson(nc)

str(geo)
#   chr "{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"AREA\":0.114,\"PERIMETER\"| __truncated__
```

You can set `atomise = TRUE` to convert each row of the `sf` object into
individual GeoJSON objects, returned as an R vector.

``` r

geo <- sf_geojson(nc, atomise = T)

str(geo)
#   chr [1:100] "{\"type\":\"Feature\",\"properties\":{\"AREA\":0.114,\"PERIMETER\":1.442,\"CNTY_\":1825,\"CNTY_ID\":1825,\"NAME"| __truncated__ ...
geo[1]
#  [1] "{\"type\":\"Feature\",\"properties\":{\"AREA\":0.114,\"PERIMETER\":1.442,\"CNTY_\":1825,\"CNTY_ID\":1825,\"NAME\":Ashe,\"FIPS\":37009,\"FIPSNO\":37009,\"CRESS_ID\":5,\"BIR74\":1091,\"SID74\":1,\"NWBIR74\":10,\"BIR79\":1364,\"SID79\":0,\"NWBIR79\":19},\"geometry\":{\"type\":\"MultiPolygon\",\"coordinates\":[[[[-81.472755,36.234356],[-81.54084,36.272507],[-81.561981,36.273594],[-81.633064,36.340687],[-81.741074,36.391785],[-81.69828,36.471779],[-81.702797,36.519341],[-81.669998,36.589649],[-81.345299,36.572865],[-81.347542,36.537914],[-81.324776,36.51368],[-81.313324,36.480698],[-81.266235,36.437206],[-81.26284,36.405041],[-81.240692,36.379417],[-81.239891,36.365364],[-81.264244,36.352413],[-81.328995,36.363503],[-81.361374,36.353161],[-81.365692,36.33905],[-81.354134,36.299717],[-81.367455,36.278698],[-81.406387,36.285053],[-81.412331,36.267292],[-81.431038,36.260719],[-81.452888,36.239586],[-81.472755,36.234356]]]]}}"
```

Examples
--------

Here are more examples of parsing various GeoJSON geometries.

### Geometry

``` r
g <- '{"type": "Point", "coordinates": [100.0, 0.0]}'
geojson_sf(g)
#  Simple feature collection with 1 feature and 0 fields
#  geometry type:  POINT
#  dimension:      XY
#  bbox:           xmin: 100 ymin: 0 xmax: 100 ymax: 0
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#         geometry
#  1 POINT (100 0)
```

### Feature

``` r
f <- '{
    "type": "Feature",
    "properties": null,
    "geometry": {
      "type": "LineString", 
      "coordinates": [[101.0, 0.0], [102.0, 1.0]]
      }
    }'
geojson_sf(f)
#  Simple feature collection with 1 feature and 0 fields
#  geometry type:  LINESTRING
#  dimension:      XY
#  bbox:           xmin: 101 ymin: 0 xmax: 102 ymax: 1
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#                     geometry
#  1 LINESTRING (101 0, 102 1)
```

Geometry Collection
-------------------

``` r
gc <- '{
  "type": "GeometryCollection",
  "geometries": [
    {"type": "Point", "coordinates": [100.0, 0.0]},
    {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
    {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
  ]
}'
geojson_sf(gc)
#  Simple feature collection with 1 feature and 0 fields
#  geometry type:  GEOMETRY
#  dimension:      XY
#  bbox:           xmin: 0 ymin: 0 xmax: 102 ymax: 2
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#                          geometry
#  1 GEOMETRYCOLLECTION (POINT (...
```

### Feature Collection

``` r
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
#  Simple feature collection with 3 features and 2 fields
#  geometry type:  GEOMETRY
#  dimension:      XY
#  bbox:           xmin: 100 ymin: 0 xmax: 102 ymax: 1
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#            bar         foo                  geometry
#  1 feature 1.2 feature 1.1             POINT (100 0)
#  2        <NA>        <NA> LINESTRING (101 0, 102 1)
#  3 feature 3.2 feature 3.1 LINESTRING (101 0, 102 1)
```

Reading from file (using `geojsonio` data)

``` r
library(sf) ## for print methods
file <- system.file("examples", "california.geojson", package = "geojsonio")

geo <- paste0(readLines(file), collapse = "")
geojsonsf::geojson_sf(geo)
#  Simple feature collection with 1 feature and 11 fields
#  geometry type:  MULTIPOLYGON
#  dimension:      XY
#  bbox:           xmin: -124.4096 ymin: 32.53416 xmax: -114.1315 ymax: 42.00952
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#    abbreviation   area    capital        city
#  1           CA 423968 Sacramento Los Angeles
#                          geometry     group houseseats landarea       name
#  1 MULTIPOLYGON (((-120.2485 3... US States         53   403466 California
#    population  statehood waterarea
#  1   38332521 1850-09-09     20502
```

Well-known Text
---------------

It also converts GeoJSON to Well-Known Text and returns a `data.frame`

``` r
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
#            bar         foo                 geometry
#  1 feature 1.2 feature 1.1            POINT (100 0)
#  2        <NA>        <NA> LINESTRING (101 0,102 1)
#  3 feature 3.2 feature 3.1 LINESTRING (101 0,102 1)
```
