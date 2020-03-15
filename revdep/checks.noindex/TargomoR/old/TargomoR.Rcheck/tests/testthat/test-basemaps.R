context("Basemaps Service")
library(TargomoR)

test_that("URL creation works", {

  expect_error(getTargomoMapURL(style = "blah"), "Invalid Map Style - check targomoMapStyles()")
  expect_equal(getTargomoMapURL(api_key = NULL),
               "https://maps.targomo.com/styles/klokantech-basic-gl-style/rendered/{z}/{x}/{y}.png?key=")

})

test_that("Adding map tiles works", {

  # skip on CRAN
  skip_on_cran()

  # make map
  l <- leaflet::leaflet()
  lt <- addTargomoTiles(l)

  # expectations
  expect_is(lt, c("leaflet", "htmlwidget"))
  expect_equal(lt$x$calls[[1]]$method, "addTiles")

})

test_that("Map attributions work", {

  # make map
  l <- leaflet::leaflet()
  la1 <- addTargomoAttribution(l, free_plan = TRUE)
  la2 <- addTargomoAttribution(l, free_plan = FALSE)

  # expectations
  expect_is(la1, c("leaflet", "htmlwidget"))
  expect_is(la1, c("leaflet", "htmlwidget"))
  expect_equal(la1$x$calls[[1]]$method, "addControl")
  expect_equal(la2$x$calls[[1]]$method, "addControl")
  expect_equal(la1$x$calls[[1]]$args[[1]], attributionFreeIframe())
  expect_equal(la2$x$calls[[1]]$args[[1]], attributionOtherIframe())
  expect_equal(attributionLink(), "https://targomo.com/developers/resources/attribution/")

})
