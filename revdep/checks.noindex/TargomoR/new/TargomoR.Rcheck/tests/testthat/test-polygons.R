context("Polygon Service")
library(TargomoR)

# set options to use
opts <- targomoOptions(travelType = "walk")

# set source data
s1 <- data.frame(lat = 51.5, lng = -0.12, id = "A")
s2 <- sf::st_as_sf(s1, coords = c("lng", "lat"), crs = sf::st_crs(4326))

test_that("GET function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # get polygons
  polygons <- getTargomoPolygons(source_data = s2, options = opts)

  # expectations
  expect_is(polygons, c("sf", "data.frame"))
  expect_equal(dim(polygons), c(3, 3))
  expect_is(polygons$geometry, c("sfc_MULTIPOLYGON", "sfc"))
  expect_equal(polygons$time, c(1800, 1200, 600))
  expect_equal(sf::st_crs(polygons), sf::st_crs(4326))

})

test_that("ADD function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map
  l <- leaflet::leaflet()

  # add polygons
  lp <- addTargomoPolygons(l, source_data = s2, options = opts)

  # expectations
  expect_is(lp, c("leaflet", "htmlwidget"))
  expect_equal(lp$x$calls[[1]]$method, "addPolygons")

})

test_that("DRAW function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map and get polygons
  l <- leaflet::leaflet()
  p <- getTargomoPolygons(source_data = s2, options = opts)
  lp <- drawTargomoPolygons(l, p)

  # expectations
  expect_is(lp, c("leaflet", "htmlwidget"))
  expect_equal(lp$x$calls[[1]]$method, "addPolygons")

})

test_that("Polygon draw options work correctly", {

  pdo <- polygonDrawOptions()

  expect_is(pdo, "list")
  expect_named(pdo)
  expect_length(pdo, 9)
  expect_equal(pdo$color, c("red", "orange", "green"))

})
