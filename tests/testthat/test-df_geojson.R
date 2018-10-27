context("df_geojson")

test_that("data.frame converted to GeoJSON", {

	n <- 1
	df <- data.frame(lon = c(1:n, NA), lat = c(1:n, NA) )
	geo <- df_geojson( df, lon = "lon", lat = "lat")
	expect_true(length(geo) == 2)
	expect_true(geo[1] == '{"type":"Point","coordinates":[1.0,1.0]}')
	expect_true(geo[2] == 'null')
	expect_true(all(sapply(geo, jsonify::validate_json)))

	df <- data.frame(lon = c(1:n, NA), lat = c(1:n, NA), id = 1:(n+1), val = letters[1:(n+1)])
	geo <- df_geojson( df, lon = "lon", lat = "lat")
	expect_true(length(geo) == 1)
	expect_true(jsonify::validate_json( geo ) )
	geo <- df_geojson( df, lon = "lon", lat = "lat", atomise = T)
	expect_true(all(sapply(geo, jsonify::validate_json)))

})
