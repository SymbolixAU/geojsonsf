context("palette.hpp")

test_that("resolve_palette works", {

  lst_params <- list(parameter = c("stroke_colour", "palette", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", palette = "mypalette", stroke_width = 3)
  expect_equal( spatialwidget:::rcpp_resolve_palette( lst_params, params ), "mypalette" )

  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", stroke_width = 3)
  spatialwidget:::rcpp_resolve_palette( lst_params, params )
  expect_equal( spatialwidget:::rcpp_resolve_palette( lst_params, params ), "viridis" )

})


test_that("colour_with_palette works for nums and strs", {

  res <- spatialwidget:::rcpp_colour_str_with_palette("viridis", letters, 255.0, "#808080FF", TRUE, "fill_colour" )
  col <- colourvalues::color_values(letters, summary = T)

  expect_equal( res$colours, col$colours )
  expect_equal( res$summary_colours, col$summary_colours )
  expect_equal( res$summary_values, col$summary_values )

  res <- spatialwidget:::rcpp_colour_num_with_palette("viridis", 1:26, 255.0, "#808080FF", TRUE, "fill_colour" )
  col <- colourvalues::color_values(1:26, n_summaries = 5, format = T)

  expect_equal( res$colours, col$colours )
  expect_equal( res$summary_colours, col$summary_colours )
  expect_equal( res$summary_values, col$summary_values )

})
