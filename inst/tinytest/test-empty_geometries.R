##"empty features are allowed", {

geo <- '{"type":"FeatureCollection","features":[]}'
sf <- geojsonsf::geojson_sf( geo )
expect_true( nrow(sf) == 0)
expect_true( "sfc_GEOMETRY" %in% attr( sf$geometry , "class" ) )

## round-trip
geo2 <- geojsonsf::sf_geojson( sf, simplify = FALSE )
expect_equal( geo, as.character( geo2 ) )


geo <- '{
  "type": "FeatureCollection",
  "features": [
  { "type": "Feature", "properties": null, "geometry": {"type":"Point","coordinates":[]} },
  { "type": "Feature", "properties": null, "geometry": {"type":"MultiPoint","coordinates":[]} },
  { "type": "Feature", "properties": null, "geometry": {"type":"LineString","coordinates":[]} },
  { "type": "Feature", "properties": null, "geometry": {"type":"MultiLineString","coordinates":[]} },
  { "type": "Feature", "properties": null, "geometry": {"type":"Polygon","coordinates":[]} },
  { "type": "Feature", "properties": null, "geometry": {"type":"MultiPolygon","coordinates":[]} }
  ]}'


sf <- geojsonsf::geojson_sf(geo)
geo <- geojsonsf::sf_geojson(sf)

geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"Point","coordinates":[]} }')
geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"MultiPoint","coordinates":[]}}')
geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"LineString","coordinates":[]}}')
geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"MultiLineString","coordinates":[]}}')
geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"Polygon","coordinates":[]}}')
geojson_sf('{ "type": "Feature", "properties": null, "geometry": {"type":"MultiPolygon","coordinates":[]}}')
