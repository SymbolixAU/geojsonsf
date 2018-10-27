## v1.3.0

* `df_geojson()` converts data.frame to GeoJSON

## v1.2.0

* `sf_geojson()` and `sfc_geojson()` output "json" class objects
* better handling of `null` objects / geometries [issue 36](https://github.com/SymbolixAU/geojsonsf/issues/36)
* `Date` and `POSIX` objects handled [issue 32](https://github.com/SymbolixAU/geojsonsf/issues/32)
* Z (elevation) and M attributes handled [issue 28](https://github.com/SymbolixAU/geojsonsf/issues/28)
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


