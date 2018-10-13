## v1.2.0

* `simplify` argument for `geojson_sf()` to keep `FeatureCollection`s when converting `sf` without properties
* `sf_geojson()` performance improvments using `jsonify`

### Changes
* factors are now treated as-is (numeric)


## v1.1.0

* fix for GeometryCollection not being [closed correctly](https://github.com/SymbolixAU/geojsonsf/issues/26)

## v1.0.0

* `sf_geojson()` and `sfc_geojson()` to convert from `sf` to GeoJSON
* `geojson_sf()` and `geojson_sfc()` can now read from a url or file


## v0.2.0 First release

* `geojson_sf()`  convert GeoJSON to `sf` object
* `geojson_sfc()` convert GeoJSON to `sfc` object
* `geojson_wkt()` convert GeoJSON to `data.frame` with a Well-known text column


