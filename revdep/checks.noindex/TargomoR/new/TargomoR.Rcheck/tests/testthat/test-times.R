context("Time Service")
library(TargomoR)

# set options to use
opts <- targomoOptions(travelType = "bike")

# set source/target data
s1 <- data.frame(lat = 51.50, lng = -0.12, id = "A")
t1 <- expand.grid(lat = seq(51.49, 51.51, by = 0.005),
                  lng = seq(-0.125, -0.115, by = 0.005))

test_that("GET function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # get times
  times <- getTargomoTimes(source_data = s1, target_data = t1, options = opts)

  # expectations
  expect_is(times, c("sf", "data.frame"))
  expect_equal(dim(times), c(15, 5))
  expect_equal(names(times), c("sourceId", "targetId", "travelType", "travelTime", "geometry"))
  expect_is(times$geometry, c("sfc_POINT", "sfc"))
  expect_equal(sf::st_crs(times), sf::st_crs(4326))

})

test_that("ADD function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map
  l <- leaflet::leaflet()

  # add times
  lt <- addTargomoTimes(l, source_data = s1, target_data = t1, options = opts)

  # expectations
  expect_is(lt, c("leaflet", "htmlwidget"))
  expect_equal(lt$x$calls[[1]]$method, "addCircleMarkers")
  expect_equal(lt$x$calls[[2]]$method, "addLegend")

})

test_that("DRAW function works correctly", {

  # skip on CRAN
  skip_on_cran()

  # make a map and get times
  l <- leaflet::leaflet()
  t <- getTargomoTimes(source_data = s1, target_data = t1, options = opts)
  lt <- drawTargomoTimes(l, t)

  # expectations
  expect_is(lt, c("leaflet", "htmlwidget"))
  expect_equal(lt$x$calls[[1]]$method, "addCircleMarkers")
  expect_equal(lt$x$calls[[2]]$method, "addLegend")

})

test_that("Time draw options work correctly", {

  tdo <- timeDrawOptions()

  expect_is(tdo, "list")
  expect_named(tdo)
  expect_length(tdo, 14)
  expect_equal(tdo$palette, "viridis")

  tlo <- timeLegendOptions(layerId = "Legend")

  expect_is(tlo, "list")
  expect_named(tlo)
  expect_length(tlo, 3)
  expect_equal(tlo$layerId, "Legend")

})

test_that("Time colour palette creation works", {

  expect_error(createTimePalette(type = "blah"), "Invalid 'type': \"blah\"")

  num <- createTimePalette("viridis", "numeric", 1800, reverse = FALSE)
  expect_is(num, "function")
  expect_equal(num(1), "#440154")
  expect_equal(num(1200), "#35B779")

  bin <- createTimePalette("viridis", "bin", 1800, bins = c(0, 600, 1200, 1800), reverse = FALSE)
  expect_is(bin, "function")
  expect_equal(bin(599), "#440154")
  expect_equal(bin(600), "#21908D")

})
