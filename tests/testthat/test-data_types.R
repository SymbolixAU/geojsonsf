context("datatypes")

test_that("r types are converted correctly", {

	# character, integer, numeric, logical, posixct, posixlt, date
	js <- '{"type":"Point","coordinates":[0,0]}'
	sf <- geojson_sf(js)
	sf$test <- as.Date("2018-01-01")
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":\"2018-01-01\"},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)

	sf$test <- as.POSIXct("2018-01-01 01:01:59")
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":\"2018-01-01 01:01:59\"},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)

	sf$test <- TRUE
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":true},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)

	sf$test <- "a"
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":\"a\"},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)

	sf$test <- 1L
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":1},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)

	sf$test <- 1.0
	expect_equal(
		geojsonsf::sf_geojson( sf ),
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{\"test\":1},\"geometry\":{\"type\":\"Point\",\"coordinates\":[0,0]}}]}"
	)
})
