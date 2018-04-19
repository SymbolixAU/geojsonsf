context("read geojson")

test_that("can read from various sources", {

	skip_on_cran()
	skip_on_travis()

	url <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_outline_500k.json"

	## direct from url
	sf <- geojson_sf(url)
	sfc <- geojson_sfc(url)

	expect_true(all(class(sf) == c("sf", "data.frame")))
	expect_true(all(class(sfc) == c("sfc_LINESTRING", "sfc")))

	expect_true(nrow(sf) == 615)
	expect_true(length(sfc) == 615)

	## connection
	con <- curl::curl(url)
	sf <- geojson_sf(con)
	con <- curl::curl(url)
	sfc <- geojson_sfc(con)

	expect_true(all(class(sf) == c("sf", "data.frame")))
	expect_true(all(class(sfc) == c("sfc_LINESTRING", "sfc")))

	expect_true(nrow(sf) == 615)
	expect_true(length(sfc) == 615)

	## local file
	sf <- geojson_sf(geo_melbourne)
	sfc <- geojson_sfc(geo_melbourne)

	expect_true(nrow(sf) == length(sfc))
	expect_true(nrow(sf) == 1)
})
