context("API Request Creation")
library(TargomoR)

# set options to use
opts <- targomoOptions(travelType = c("car", "transit", "bike"))
dopts <- deriveOptions(opts)

# set source data
s1 <- data.frame(lat = 51, lng = 0, id = "A")
s2 <- sf::st_as_sf(s1, coords = c("lng", "lat"), crs = sf::st_crs(4326))

# create points
p1 <- createPoints(s2)

# derive sources and targets
sources <- deriveSources(p1, dopts)
targets <- deriveTargets(p1)

# create bodies
p_body <- createRequestBody("polygon", sources, targets, dopts)
r_body <- createRequestBody("route", sources, targets, dopts)
t_body <- createRequestBody("time", sources, targets, dopts)

# Tests -------------------------------------------------------------------

test_that("URL creation works for different endpoints", {

  # URL expecations
  expect_equal(targomoAPI(), "https://api.targomo.com/")
  expect_equal(createRequestURL("britishisles", "polygon"),
               "https://api.targomo.com/britishisles/v1/polygon")
  expect_equal(createRequestURL("asia", "route"),
               "https://api.targomo.com/asia/v1/route")

})

test_that("API options lists are created correctly", {

  # option expectations
  expect_is(opts, "list")
  expect_is(dopts, "list")
  expect_named(opts)
  expect_named(dopts)
  expect_length(opts, 16)
  expect_length(dopts, 6)

})

test_that("Point creation works on different types of data", {

  # data frame expectations
  expect_message(createPoints(s1, id = ~id), 'Assuming "lng" and "lat" are longitude and latitude, respectively')
  expect_is(createPoints(s1, lat = ~lat, lng = ~lng, id = ~id), "data.frame")
  expect_equal(createPoints(s1), data.frame(lng = 0, lat = 51, id = 1))

  # sf expectations
  expect_silent(createPoints(s2, id = ~id))
  expect_is(createPoints(s2), "data.frame")
  expect_equal(createPoints(s2)$id, 1)
  expect_equal(createPoints(s2), data.frame(lng = 0, lat = 51, id = 1))

  # vector expectations
  expect_silent(createPoints(NULL, lat = 51, lng = 0, id = "A"))
  expect_is(createPoints(NULL, lat = 51, lng = 0, id = "A"), "data.frame")
  expect_equal(createPoints(NULL, lat = 51, lng = 0, id = "A"),
               data.frame(lng = 0, lat = 51, id = "A", stringsAsFactors = FALSE))

})

test_that("ID creation works with different data types", {

  df <- data.frame(letters, stringsAsFactors = FALSE)

  expect_null(createIds())
  expect_equal(createIds(id = letters), letters)
  expect_equal(createIds(data = df), 1:26)
  expect_equal(createIds(data = df, id = ~letters), letters)
  expect_equal(createIds(data = df, id = 2:27), 2:27)
  expect_error(createIds(data = df, id = 1),
               "'id' values different length to 'data'")
  expect_error(createIds(data = df, id = x ~ y),
               "Unexpected 2-sided formula: x ~ y")

})

test_that("Source/Target derivation returns correct lists", {

  # source expectations
  expect_is(sources, "list")
  expect_length(sources, 1)
  expect_length(sources[[1]], 4)
  expect_named(sources[[1]])
  expect_equal(sources[[1]], list(id = 1, lat = 51, lng = 0,
                                  tm = list(
                                    car = list(rushHour = FALSE),
                                    transit = list(frame = list(earliestArrival = FALSE)),
                                    bike = list(speed = 15, uphill = 20, downhill = -10)
                                  )
                              )
  )

  # target expectations
  expect_is(targets, "list")
  expect_length(targets, 1)
  expect_length(targets[[1]], 3)
  expect_named(targets[[1]])

})

test_that("Body creation returns correct JSON", {

  # error expectations
  expect_error(createRequestBody(service = NULL), "No Targomo service specified")
  expect_error(createRequestBody(service = "time", sources = NULL), "No source data provided")

  # class expectations
  expect_is(p_body, "json")
  expect_is(r_body, "json")
  expect_is(t_body, "json")

  # field expecations
  expect_match(p_body, "polygon")
  expect_false(grepl("polygon", r_body))
  expect_false(grepl("polygon", t_body))
  expect_match(r_body, "pathSerializer")
  expect_false(grepl("pathSerializer", p_body))
  expect_false(grepl("pathSerializer", t_body))

  # length expectations
  expect_equal(nchar(p_body), 669)
  expect_equal(nchar(r_body), 544)
  expect_equal(nchar(t_body), 513)

})

test_that("Calls to the API return correct responses", {

  # skip on CRAN
  skip_on_cran()

  # helper function
  expect_status <- function(service, body, status,
                            api_key = Sys.getenv("TARGOMO_API_KEY"),
                            region = Sys.getenv("TARGOMO_REGION")) {
    x <- callTargomoAPI(api_key = api_key, region = region,
                        service = service, body = body)
    expect_equal(x$status_code, status)
  }

  # 200 expectations
  expect_status("polygon", p_body, 200)
  expect_status("route",   r_body, 200)
  expect_status("time",    t_body, 200)

  # 404 expectations
  expect_status("some_service", p_body, 404)
  expect_status("time", t_body, region = "mars", status = 404)

  # 400 expectation
  expect_status("polygon", "blah", 400)

  # 403 expectation
  expect_status("time", t_body, api_key = "fake", status = 403)

})

test_that("API responses are processed correctly", {

  # skip on CRAN
  skip_on_cran()

  # good responses
  p_response <- callTargomoAPI(service = "polygon", body = p_body)
  r_response <- callTargomoAPI(service = "route",   body = r_body)
  t_response <- callTargomoAPI(service = "time",    body = t_body)

  # bad responses
  bad1 <- callTargomoAPI(service = "blah", body = p_body)
  bad2 <- callTargomoAPI(service = "time", body = t_body, api_key = "blah")
  bad3 <- callTargomoAPI(service = "time", body = "blah")

  # process responses
  polygons <- processResponse(p_response, "polygon")
  routes   <- processResponse(r_response, "route")
  times    <- processResponse(t_response, "time")

  # bad response catching expectations
  expect_error(catchBadResponse(bad1))
  expect_error(catchBadResponse(bad2, "User with key 'blah' not authorized/activated for the requested Targomo service"))
  expect_error(catchBadResponse(bad3, "400 - Bad Request. Check your settings and try again."))

  # good responses
  expect_equal(catchBadResponse(p_response), p_response)
  expect_equal(catchBadResponse(r_response), r_response)
  expect_equal(catchBadResponse(t_response), t_response)

  # processing responses
  expect_is(polygons, c("sf", "data.frame"))
  expect_is(routes, "list")
  expect_is(routes[[1]], c("tbl_df", "tbl", "data.frame"))
  expect_is(times, "data.frame")

  # check dimensions and geometry cols
  expect_equal(dim(polygons), c(3, 3))
  expect_is(polygons$geometry, c("sfc_MULTIPOLYGON", "sfc"))
  expect_equal(dim(routes[[1]]), c(3, 3))
  expect_is(routes[[1]]$features$geometry, c("sfc_GEOMETRY", "sfc"))
  expect_equal(names(routes[[1]]), c("sourceId", "targetId", "features"))
  expect_equal(names(polygons), c("time", "area", "geometry"))

})

test_that("Messaging about multiple travel modes works", {

  expect_silent(messageMultipleTravelModes("car"))
  expect_message(messageMultipleTravelModes(c("car", "bike")))

})
