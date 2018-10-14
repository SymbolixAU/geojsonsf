geojsonsf
================

[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/geojsonsf)](https://CRAN.R-project.org/package=geojsonsf)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/geojsonsf)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/geojsonsf)](https://CRAN.R-project.org/package=geojsonsf)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/geojsonsf.svg?style=social&label=Github)](https://github.com/SymbolixAU/geojsonsf)
[![Build
Status](https://travis-ci.org/SymbolixAU/geojsonsf.svg?branch=master)](https://travis-ci.org/SymbolixAU/geojsonsf)
[![Coverage
Status](https://codecov.io/github/SymbolixAU/geojsonsf/coverage.svg?branch=master)](https://codecov.io/github/SymbolixAU/geojsonsf?branch=master)

–

## Warning Note: 2018-09-22

I have found [an
issue](https://github.com/SymbolixAU/geojsonsf/issues/32) with `Dates`
and `POSIXct` columns not being handled correctly.

I have made a fix in the development version and aim to have it on CRAN
by the end of October 2018.

Before then, to handle `Dates` and `POSIXct` columns correctly you will
need to convert them to characters first.

-----

## geojsonsf

A simple, low-dependency and **fast** converter between GeoJSON and
Simple Feature objects in R.

-----

**v1.1**

Converts

  - GeoJSON –\> `sf`
  - GeoJSON –\> `sfc`
  - `sf` –\> GeoJSON
  - `sfc` –\> GeoJSON
  - GeoJSON –\> Well-known text

As per GeoJSON ([RFC 7946
specification)](https://tools.ietf.org/html/rfc7946#page-11), foreign
members are ignored, and nested objects and arrays inside the
`properties` object are converted to string/characters.

## Installation

Install the CRAN version wth

``` r
install.packages("geojsonsf")
```

To install the development version

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/geojsonsf")
```

## Motivation

To quickly parse between GeoJSON and `sf` objects, and to handle cases
not supported by `sf`, e.g. arrays of geometries

### Arrays of GeoJSON

``` r

js <- '[
{
  "type": "FeatureCollection",
  "features": [
  {
    "type": "Feature",
    "properties": {"id":1,"val":true},
    "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
  },
  {
    "type": "Feature",
    "properties": {"id":2,"val":false},
    "geometry": {"type": "LineString", "coordinates": [[201.0, 0.0], [102.0, 1.0]]}
  },
  {
    "type": "Feature",
        "properties": {"id":3},
        "geometry": {"type": "LineString", "coordinates": [[301.0, 0.0], [102.0, 1.0]]}
    }
 ]
},
{
  "type": "FeatureCollection",
    "features": [
    {
      "type": "Feature",
      "properties": {"id":1},
      "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
    },
    {
      "type": "Feature",
      "properties": {"val":false},
      "geometry": {"type": "LineString", "coordinates": [[501.0, 0.0], [102.0, 1.0]]}
    },
    {
      "type": "Feature",
      "properties": {"hello":"world"},
      "geometry": {"type": "LineString", "coordinates": [[601.0, 0.0], [102.0, 1.0]]}
    }
  ]
}
]'

sf <- geojson_sf(js)
sf
#  Simple feature collection with 6 features and 3 fields
#  geometry type:  GEOMETRY
#  dimension:      XY
#  bbox:           xmin: 100 ymin: 0 xmax: 601 ymax: 1
#  epsg (SRID):    4326
#  proj4string:    +proj=longlat +datum=WGS84 +no_defs
#    id  val hello                  geometry
#  1  1    1  <NA>             POINT (100 0)
#  2  2    0  <NA> LINESTRING (201 0, 102 1)
#  3  3 <NA>  <NA> LINESTRING (301 0, 102 1)
#  4  1 <NA>  <NA>             POINT (100 0)
#  5 NA    0  <NA> LINESTRING (501 0, 102 1)
#  6 NA <NA> world LINESTRING (601 0, 102 1)
```

And back again to GeoJSON

``` r
js <- sf_geojson(sf)
jsonlite::prettify(js)
#  {
#      "type": "FeatureCollection",
#      "features": [
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": 1.0,
#                  "val": "1",
#                  "hello": null
#              },
#              "geometry": {
#                  "type": "Point",
#                  "coordinates": [
#                      100.0,
#                      0.0
#                  ]
#              }
#          },
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": 2.0,
#                  "val": "0",
#                  "hello": null
#              },
#              "geometry": {
#                  "type": "LineString",
#                  "coordinates": [
#                      [
#                          201.0,
#                          0.0
#                      ],
#                      [
#                          102.0,
#                          1.0
#                      ]
#                  ]
#              }
#          },
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": 3.0,
#                  "val": null,
#                  "hello": null
#              },
#              "geometry": {
#                  "type": "LineString",
#                  "coordinates": [
#                      [
#                          301.0,
#                          0.0
#                      ],
#                      [
#                          102.0,
#                          1.0
#                      ]
#                  ]
#              }
#          },
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": 1.0,
#                  "val": null,
#                  "hello": null
#              },
#              "geometry": {
#                  "type": "Point",
#                  "coordinates": [
#                      100.0,
#                      0.0
#                  ]
#              }
#          },
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": null,
#                  "val": "0",
#                  "hello": null
#              },
#              "geometry": {
#                  "type": "LineString",
#                  "coordinates": [
#                      [
#                          501.0,
#                          0.0
#                      ],
#                      [
#                          102.0,
#                          1.0
#                      ]
#                  ]
#              }
#          },
#          {
#              "type": "Feature",
#              "properties": {
#                  "id": null,
#                  "val": null,
#                  "hello": "world"
#              },
#              "geometry": {
#                  "type": "LineString",
#                  "coordinates": [
#                      [
#                          601.0,
#                          0.0
#                      ],
#                      [
#                          102.0,
#                          1.0
#                      ]
#                  ]
#              }
#          }
#      ]
#  }
#  
```

### Speed

This benchmark shows a comparison with `library(sf)` for converting a
string of GeoJSON of 3,221 counties in the US in to an `sf`
object

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
#  Unit: milliseconds
#        expr       min        lq      mean    median        uq       max
#   geojsonsf  815.0108  815.0108  835.3831  835.3831  855.7554  855.7554
#          sf 2081.7465 2081.7465 2125.8002 2125.8002 2169.8539 2169.8539
#   neval
#       2
#       2
```

A visual check to see both objects are the same

``` r
library(googleway)
set_key("GOOGLE_MAP_KEY")

gsf <- geojson_sf(geo)

google_map() %>%
    add_polygons(gsf[!gsf$STATE %in% c("02","15","72"), ], 
            fill_colour = "CENSUSAREA", 
            stroke_weight = 0)
```

<img src="./man/figures/GeoJSONSF.png" width="100%" />

``` r
sf <- sf::st_read(geo, quiet = T)
plot(st_geometry(sf[!sf$STATE %in% c("02", "15", "72"), ]))
```

<img src="man/figures/README-unnamed-chunk-8-1.png" width="100%" />
