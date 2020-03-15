context("test-mot")

test_that("stop if not", {
  expect_error(get_MOT())
  expect_error(get_MOT(c(1)))
  expect_error(get_MOT(c("REG")))

})
