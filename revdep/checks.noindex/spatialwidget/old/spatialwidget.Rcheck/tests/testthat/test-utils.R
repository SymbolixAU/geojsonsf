context("utils.hpp")

test_that("fill_vector returns new list element", {
  lst <- list()
  param <- "my_param"
  val <- 1
  n <- 20
  new_lst <- spatialwidget:::rcpp_fill_vector( lst, param, val, n)
  expect_true( "my_param" %in% names(new_lst))
  expect_true( all( new_lst[["my_param"]] == rep(1, n) ) )
})


test_that("where_is returns correct index", {
  expect_equal(spatialwidget:::rcpp_where_is("a", letters), 0)
  expect_equal(spatialwidget:::rcpp_where_is("b", letters), 1)
  expect_equal(spatialwidget:::rcpp_where_is("z", letters), 25)
  expect_true( all( spatialwidget:::rcpp_where_is(letters, letters) == 0:25 ) )
  expect_true( all( spatialwidget:::rcpp_where_is(letters, rev( letters) )  == 25:0 ) )
})

test_that("list elements are removed", {
  lst <- list(let = letters, vals = 1:5)
  new_lst <- spatialwidget:::rcpp_remove_list_elements(lst, "vals")
  expect_true( all(names(new_lst) == "let") )
})

test_that("hex colour regex works", {

  expect_true( spatialwidget:::is_hex( "#ABC" ) )
  expect_true( spatialwidget:::is_hex( "#ABCF" ) )
  expect_true( spatialwidget:::is_hex( "#1111" ) )
  expect_true( spatialwidget:::is_hex( "#808080FF" ) )

  expect_false( spatialwidget:::is_hex( "#" ) )
  expect_false( spatialwidget:::is_hex( "#0" ) )
  expect_false( spatialwidget:::is_hex( "808080FF" ) )
  expect_false( spatialwidget:::is_hex( "#80" ) )
  expect_false( spatialwidget:::is_hex( "#80808" ) )
  expect_false( spatialwidget:::is_hex( "#808080F" ) )

})
