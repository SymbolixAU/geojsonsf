source("../skip-download.R")

context("test-format: accidents")

test_that("format_accidents works", {
  df = format_accidents(stats19::accidents_sample_raw)
  expect_equal(nrow(df), nrow(stats19::accidents_sample_raw))
})

context("test-format: vehicles")

test_that("format_vehicles works", {
  fn = stats19::file_names$dftRoadSafetyData_Vehicles_2016.zip
  skip_download()
  dl_stats19(file_name = fn)
  # read it
  read = read_vehicles(
    year = 2016,
    filename = "Veh.csv"
  )
  df = format_vehicles(head(read))
  expect_true(is(df, "data.frame"))
})

context("test-format: casualties")

test_that("format_casualties works", {
  fn = stats19::file_names$dftRoadSafetyData_Casualties_2016.zip
  skip_download()
  dl_stats19(file_name = fn)
  # read it
  read = read_casualties(
    year = 2016,
    filename = "Cas.csv"
  )
  df = format_casualties(head(read))
  expect_true(is(df, "data.frame"))
})

context("test-format: sf")
test_that("format_column_names works", {
  # basic
  rd = names(stats19::accidents_sample_raw)
  expect_equal(nrow(rd), nrow(format_column_names(rd)))
})
test_that("format_sf works", {
  rd = format_accidents(stats19::accidents_sample_raw)
  df1 = format_sf(rd)
  df2 = format_sf(rd, lonlat = TRUE)
  expect_equal(nrow(df1), nrow(rd))
  expect_equal(nrow(df2), nrow(rd))
  expect_true(is(df1, "sf"))
  expect_true(is(df2, "sf"))
})

test_that("format_ppp returns ppp object", {
  rd = accidents_sample
  rd_ppp = format_ppp(rd)
  expect_true(is(rd_ppp, "ppp"))
})

test_that("is it possible to change window object in format_ppp", {
  rd = accidents_sample
  rd_ppp = format_ppp(rd)
  rd_ppp2 = format_ppp(
    rd,
    # bounding box of leeds which is smaller the default bbox which
    # covers all UK
    window = spatstat::owin(c(425046.1, 435046.1), c(428577.2, 438577.2))
  )
  # since the bbox is smaller there must be fewer points
  expect_true(rd_ppp2$n <= rd_ppp$n)
})

test_that("format_ppp exclude events with missing coordinates", {
  rd = accidents_sample
  rd_ppp = format_ppp(rd)
  rd2 = rd
  rd2[1, "location_easting_osgr"] = NA
  rd2[1, "location_northing_osgr"] = NA
  rd_ppp2 = format_ppp(rd2)
  # since the bbox is smaller there must be fewer points
  expect_true(rd_ppp2$n <= rd_ppp$n)
})
