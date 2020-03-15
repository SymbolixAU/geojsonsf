context("Route Service")
library(TargomoR)

# set options to use
opts <- targomoOptions(travelType = c("walk", "bike", "car", "transit"))

# set source/target data
s1 <- data.frame(lat = 51.50, lng = -0.12, id = "A")
t1 <- data.frame(lat = 51.51, lng = -0.13, id = "B")

test_that("GET function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # get routes
  routes <- getTargomoRoutes(source_data = s1, target_data = t1, options = opts)

  # expectations
  expect_is(routes, c("list"))
  expect_length(routes, 4)
  expect_equal(names(routes), c("walk", "bike", "car", "transit"))
  expect_equal(dim(routes$walk[[1]]), c(3, 3))
  expect_equal(names(routes$walk[[1]]), c("sourceId", "targetId", "features"))
  expect_is(routes$bike[[1]]$features$geometry, c("sfc_GEOMETRY", "sfc"))
  expect_equal(sf::st_crs(routes$bike[[1]]$features), sf::st_crs(4326))

})

test_that("ADD function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map
  l <- leaflet::leaflet()

  # add routes
  lr <- addTargomoRoutes(l, source_data = s1, target_data = t1, options = opts)

  # expectations
  expect_is(lr, c("leaflet", "htmlwidget"))
  expect_equal(lr$x$calls[[1]]$method, "addMarkers")
  expect_equal(lr$x$calls[[2]]$method, "addMarkers")
  expect_equal(lr$x$calls[[3]]$method, "addPolylines")
  expect_equal(lr$x$calls[[4]]$method, "addMarkers")
  expect_equal(lr$x$calls[[5]]$method, "addMarkers")
  expect_equal(lr$x$calls[[6]]$method, "addPolylines")

})

test_that("DRAW function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map and get route
  l <- leaflet::leaflet()
  r <- getTargomoRoutes(source_data = s1, target_data = t1, options = opts)
  lr <- drawTargomoRoutes(l, r)

  # expectations
  expect_is(lr, c("leaflet", "htmlwidget"))
  expect_equal(lr$x$calls[[1]]$method, "addMarkers")
  expect_equal(lr$x$calls[[2]]$method, "addMarkers")
  expect_equal(lr$x$calls[[3]]$method, "addPolylines")
  expect_equal(lr$x$calls[[4]]$method, "addMarkers")
  expect_equal(lr$x$calls[[5]]$method, "addMarkers")
  expect_equal(lr$x$calls[[6]]$method, "addPolylines")

})

test_that("Route draw options work correctly", {

  rdo <- routeDrawOptions()

  expect_is(rdo, "list")
  expect_named(rdo)
  expect_length(rdo, 13)
  expect_equal(rdo$walkDashArray, "1,10")

})

test_that("Route popup creation works", {

  # skip on CRAN
  skip_on_cran()

  # get routes
  routes <- getTargomoRoutes(source_data = s1, target_data = t1, options = opts)
  w_features <- routes$walk[[1]]$features
  w_segment <- w_features[sf::st_is(w_features, "LINESTRING"), ]
  t_features <- routes$transit[[1]]$features
  t_segment <- t_features[sf::st_is(t_features, "LINESTRING"), ]

  # expectations
  expect_match(createRoutePopup(w_segment),
               "<b>WALK</b></br>Journey time: [\\d+min ]?[\\d+s]?")
  expect_true(all(grepl("<b>[A-Z]+</b></br>Journey time: [\\d+min ]?[\\d+s]?",
                        createRoutePopup(t_segment))))


})
