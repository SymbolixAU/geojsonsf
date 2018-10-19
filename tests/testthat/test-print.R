context("print")

test_that("print method called",{

	geo <- '{"type":"Point","coordinates":[0,0]}'
	attr(geo, "class") <- "geojson"

	expect_output(print(geo))

})
