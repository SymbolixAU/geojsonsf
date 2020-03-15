context("geojson")

test_that("to_geojson always returns a Feature, even if ther aren't any properties", {

  sf <- structure(list(geometry = structure(list(structure(c(0, 0), class = c("XY",
  "POINT", "sfg"))), class = c("sfc_POINT", "sfc"), precision = 0, bbox = structure(c(xmin = 0,
  ymin = 0, xmax = 0, ymax = 0), class = "bbox"), crs = structure(list(
  epsg = NA_integer_, proj4string = NA_character_), class = "crs"), n_empty = 0L)), row.names = 1L, class = c("sf",
  "data.frame"), sf_column = "geometry", agr = structure(integer(0), class = "factor", .Label = c("constant",
  "aggregate", "identity"), .Names = character(0)))

  geo <- spatialwidget:::rcpp_geojson_sf(sf, "geometry")
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(geometry = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

  df <- data.frame(lon = 0, lat = 0)
  expect_error(
    spatialwidget:::rcpp_geojson_df(df, list("lon", "lat"))
    , 'Expecting a list of geometries, each element is named and contains the lon and lat columns'
  )


})

test_that("geometry field changes with user input", {

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(mygeometryproperty = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"mygeometryproperty\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

})


test_that("MULTI objects are down-casted", {

  js <- '{"type":"Feature","properties":{},"geometry":{"type":"MultiPoint","coordinates":[[1,4],[2,5]]}}'
  sf <- geojsonsf::geojson_sf( js )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  expected <- '[{"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Point","coordinates":[1.0,4.0]}}},
  {"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Point","coordinates":[2.0,5.0]}}}]'
  expect_true(jsonify:::validate_json(geo_down))
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )

  js <- '{"type":"MultiPoint","coordinates":[[1,3,5,7],[2,4,6,8]]}'
  sf <- geojsonsf::geojson_sf( js )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  expected <- '[{"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Point","coordinates":[1.0,3.0,5.0,7.0]}}},
  {"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Point","coordinates":[2.0,4.0,6.0,8.0]}}}]'
  expect_true( jsonify:::validate_json( geo_down ) )
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )

  js <- '{"type":"Feature","properties":{"id":8},"geometry":{"type":"MultiLineString","coordinates":[[[1.0,4.0],[2.0,5.0]],[[6.0,3.0],[5.0,2.0]]]}}'
  sf <- geojsonsf::geojson_sf( js )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  expected <- '[{"type":"Feature","properties":{"id":8.0},"geometry":{"geometry":  {"type":"LineString","coordinates":[[1.0,4.0],[2.0,5.0]]}}},{"type":"Feature","properties":{"id":8.0},"geometry":{"geometry":{"type":"LineString","coordinates":[[6.0,3.0],[5.0,2.0]]}}}]'
  expect_true( jsonify:::validate_json( geo_down ) )
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )


  js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
  sf <- geojsonsf::geojson_sf( js )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  expected <- '[{"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]]}}},{"type":"Feature","properties":{},"geometry":{"geometry":{"type":"Polygon","coordinates":[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]}}}]'
  expect_true( jsonify:::validate_json( geo_down ) )
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )

  ## a combination of some of the above
  js <- '{"type":"FeatureCollection","features":[{"type":"Feature","properties":{"id":2},"geometry":{"type":"MultiPoint","coordinates":[[1,4],[2,5],[3,6]]}},{"type":"Feature","properties":{"id":8},"geometry":{"type":"MultiLineString","coordinates":[[[1.0,4.0],[2.0,5.0],[3.0,6.0]],[[6.0,3.0],[5.0,2.0],[4.0,1.0]],[[1.0,4.0],[2.0,5.0],[3.0,6.0]]]}},{"type":"Feature","properties":{"id":9},"geometry":{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}}]}'
  sf <- geojsonsf::geojson_sf( js )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  expected <- '[{"type":"Feature","properties":{"id":2.0},"geometry":{"geometry":{"type":"Point","coordinates":[1.0,4.0]}}},{"type":"Feature","properties":{"id":2.0},"geometry":{"geometry":{"type":"Point","coordinates":[2.0,5.0]}}},{"type":"Feature","properties":{"id":2.0},"geometry":{"geometry":{"type":"Point","coordinates":[3.0,6.0]}}},{"type":"Feature","properties":{"id":8.0},"geometry":{"geometry":{"type":"LineString","coordinates":[[1.0,4.0],[2.0,5.0],[3.0,6.0]]}}},{"type":"Feature","properties":{"id":8.0},"geometry":{"geometry":{"type":"LineString","coordinates":[[6.0,3.0],[5.0,2.0],[4.0,1.0]]}}},{"type":"Feature","properties":{"id":8.0},"geometry":{"geometry":{"type":"LineString","coordinates":[[1.0,4.0],[2.0,5.0],[3.0,6.0]]}}},{"type":"Feature","properties":{"id":9.0},"geometry":{"geometry":{"type":"Polygon","coordinates":[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]]}}},{"type":"Feature","properties":{"id":9.0},"geometry":{"geometry":{"type":"Polygon","coordinates":[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]}}}]'
  expect_true( jsonify:::validate_json( geo_down ) )
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )
})

test_that("MULTI OD sf objects are downcast and atomised", {

  geo1 <- '[
{"type":"MultiPoint","coordinates":[[0,0],[1,1],[2,2]]},
{"type":"MultiPoint","coordinates":[[0,0],[1,1],[2,2],[3,3]]}
]'
  geo2 <- '[
{"type":"MultiPoint","coordinates":[[9,9],[8,8],[7,7],[6,6],[5,5]]},
{"type":"MultiPoint","coordinates":[[9,9]]}
]'

  sf1 <- geojsonsf::geojson_sf( geo1 )
  sf2 <- geojsonsf::geojson_sf( geo2 )
  names( sf1 ) <- "origin"
  names( sf2 ) <- "destination"
  sf <- cbind( sf1, sf2 )
  sf$id <- 1:nrow( sf )
  geo_down <- spatialwidget:::rcpp_sf_to_geojson_multi_column_downcast( sf, geometries = c("origin", "destination"))
  expected <- '[{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[8.0,8.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[8.0,8.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[8.0,8.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[7.0,7.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[7.0,7.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[7.0,7.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[6.0,6.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[6.0,6.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[6.0,6.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[5.0,5.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[5.0,5.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":1},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[5.0,5.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":2},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":2},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[1.0,1.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":2},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[2.0,2.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}},{\"type\":\"Feature\",\"properties\":{\"id\":2},\"geometry\":{\"origin\":{\"type\":\"Point\",\"coordinates\":[3.0,3.0]},\"destination\":{\"type\":\"Point\",\"coordinates\":[9.0,9.0]}}}]'
  expect_true( jsonify:::validate_json( geo_down ) )
  expect_equal( as.character( geo_down ), gsub("\\n| ","", expected ) )

})

test_that("data.frame with z elevation converted", {

  df <- data.frame( id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expected <- '[{"type":"Feature","properties":{"id":1},"geometry":{"geometry":{"type":"Point","coordinates":[0.0,0.0,1.0]}}},{"type":"Feature","properties":{"id":2},"geometry":{"geometry":{"type":"Point","coordinates":[0.0,0.0,1.0]}}}]'
  res <- spatialwidget:::rcpp_geojson_dfz( df, list( geometry = c( "lon","lat","z" ) ) )
  expect_equal( expected, as.character( res ) )

  df <- data.frame(id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expect_error(
    spatialwidget:::rcpp_geojson_dfz(df, c("lon","lat","z"))
    , 'Expecting a list of geometries, each element is named and contains the lon, lat and z columns'
  )

  df <- data.frame(id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expect_error(
    spatialwidget:::rcpp_geojson_dfz(df, c(lon = "lon", lat = "lat", z = "z"))
    , 'Expecting a list of geometries, each element is named and contains the lon, lat and z columns'
  )

})

