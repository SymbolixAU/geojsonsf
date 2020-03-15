context("Miscellaneous")
library(TargomoR)

test_that("Setup function works", {

  # skip on CRAN and Travis
  skip_on_cran()
  skip_on_travis()

  # if .Renviron file exists, delete it
  if (file.exists(".Renviron")) {
    unlink(".Renviron")
  }

  expect_equal(setTargomoVariables(), Sys.getenv("TARGOMO_API_KEY"))
  expect_message(
    setTargomoVariables(overwrite = TRUE),
    "Writing TARGOMO_API_KEY and TARGOMO_REGION to .Renviron file:\n"
  )

  expect_null(setTargomoVariables())
  expect_message(
    setTargomoVariables(),
    "Pre-existing TargomoR variables in .Renviron.\nSet overwrite = TRUE to alter them."
  )

  # remove .Renviron
  if (file.exists(".Renviron")) {
    unlink(".Renviron")
  }

})

test_that("Capabilities service works", {

  # skip on CRAN
  skip_on_cran()

  # get capabilities
  caps <- getTargomoCapabilities()

  # expectations
  expect_is(caps, c("tgm_capabilities", "list"))
  expect_length(caps, 3)
  expect_named(caps)
  expect_equal(names(caps), c("general", "transit", "speeds"))

})

test_that("Printing capabilities works correctly", {

  # skip on CRAN and travis
  skip_on_cran()
  skip_on_travis()

  # get capabilities
  caps <- getTargomoCapabilities()

  verify_output(test_path("print-capabilities.txt"), {
    print.tgm_capabilities(caps)
  })

})

test_that("Formatting works for edgeweights", {

  expect_time <- function(string, time) {
    expect_equal(numericEdgeWeight(string, "time"), time)
  }

  expect_distance <- function(string, distance) {
    expect_equal(numericEdgeWeight(string, "distance"), distance)
  }

  # errors
  expect_error(numericEdgeWeight(500, type = "blah"),
               "'type' must be 'time' or 'distance', not 'blah'")
  expect_error(numericEdgeWeight("1a", "time"),
               "Invalid time string specified: 1a")
  expect_error(numericEdgeWeight("2b", "distance"),
               "Invalid distance string specified: 2b")

  # times
  expect_time("1h", 3600)
  expect_time("1h20m", 4800)
  expect_time("30m15s", 1815)
  expect_time("2h1s", 7201)
  expect_time(1, 1)

  # distances
  expect_distance("1ml", 1609)
  expect_distance("2km", 2000)
  expect_distance("450m", 450)
  expect_distance("1km100m", 1100)

})

test_that("Pretty formatting for edgeweights works", {

  expect_time <- function(value, time) {
    expect_equal(prettyEdgeWeight(value, "time"), time)
  }

  expect_distance <- function(value, distance) {
    expect_equal(prettyEdgeWeight(value, "distance"), distance)
  }

  # errors
  expect_error(numericEdgeWeight(500, type = "blah"),
               "'type' must be 'time' or 'distance', not 'blah'")
  expect_error(prettyEdgeWeight("a", "time"), "Invalid time string specified: a")
  expect_error(prettyEdgeWeight("b", "distance"), "Invalid distance string specified: b")
  expect_error(prettyEdgeWeight(factor("a"), "time"), "Invalid edgeweight class: factor")

  # correct times
  expect_time("1h 30m", "1h 30m")
  expect_time(3600, "1hr")
  expect_time(1800, "30min")
  expect_time(54, "54s")
  expect_time(5454, "1hr 30min 54s")
  expect_time(0, "0s")

  # correct distances
  expect_distance("1km 500m", "1km 500m")
  expect_distance(1000, "1km")
  expect_distance(500, "500m")
  expect_distance(1500, "1km 500m")
  expect_distance(0, "0m")

})
