
<!-- README.md is generated from README.Rmd. Please edit that file -->

# geojsonsf

The goal of geojsonsf is to …

## Installation

You can install geojsonsf from GitHub with:

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/geojsonsf")
```

## Motivation

To quickly parse GeoJSON to `sf` objects, and to handle cases not
supported by `sf`, e.g. arrays of geometries

### Array of geometries

``` r
library(geojsonsf)
library(sf)        ## for sf print methods
#> Linking to GEOS 3.6.1, GDAL 2.1.3, proj.4 4.9.3

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
#> Simple feature collection with 6 features and 0 fields
#> geometry type:  GEOMETRY
#> dimension:      XY
#> bbox:           xmin: 100 ymin: 0 xmax: 601 ymax: 1
#> epsg (SRID):    4326
#> proj4string:    +proj=longlat +datum=WGS84 +no_defs
#>                    geometry
#> 1             POINT (100 0)
#> 2 LINESTRING (201 0, 102 1)
#> 3 LINESTRING (301 0, 102 1)
#> 4             POINT (100 0)
#> 5 LINESTRING (501 0, 102 1)
#> 6 LINESTRING (601 0, 102 1)
```

### Speed

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

## Examples

### Geometry

``` r
g <- '{"type": "Point", "coordinates": [100.0, 0.0]}'
geojson_sf(g)
#> Simple feature collection with 1 feature and 0 fields
#> geometry type:  POINT
#> dimension:      XY
#> bbox:           xmin: 100 ymin: 0 xmax: 100 ymax: 0
#> epsg (SRID):    4326
#> proj4string:    +proj=longlat +datum=WGS84 +no_defs
#>        geometry
#> 1 POINT (100 0)
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
#> Simple feature collection with 1 feature and 0 fields
#> geometry type:  LINESTRING
#> dimension:      XY
#> bbox:           xmin: 101 ymin: 0 xmax: 102 ymax: 1
#> epsg (SRID):    4326
#> proj4string:    +proj=longlat +datum=WGS84 +no_defs
#>                    geometry
#> 1 LINESTRING (101 0, 102 1)
```

## Geometry Collection

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
#> Simple feature collection with 1 feature and 0 fields
#> geometry type:  GEOMETRY
#> dimension:      XY
#> bbox:           xmin: 0 ymin: 0 xmax: 102 ymax: 2
#> epsg (SRID):    4326
#> proj4string:    +proj=longlat +datum=WGS84 +no_defs
#>                         geometry
#> 1 GEOMETRYCOLLECTION (POINT (...
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
#> Simple feature collection with 3 features and 2 fields
#> geometry type:  GEOMETRY
#> dimension:      XY
#> bbox:           xmin: 100 ymin: 0 xmax: 102 ymax: 1
#> epsg (SRID):    4326
#> proj4string:    +proj=longlat +datum=WGS84 +no_defs
#>           bar         foo                  geometry
#> 1 feature 1.2 feature 1.1             POINT (100 0)
#> 2        <NA>        <NA> LINESTRING (101 0, 102 1)
#> 3 feature 3.2 feature 3.1 LINESTRING (101 0, 102 1)
```

Reading from file (using `geojsonio` data)

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

## Well-known Text

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
#>           bar         foo                  geometry
#> 1 feature 1.2 feature 1.1             POINT (100 0)
#> 2        <NA>        <NA> LINESTRING (101 0, 102 1)
#> 3 feature 3.2 feature 3.1 LINESTRING (101 0, 102 1)
```
