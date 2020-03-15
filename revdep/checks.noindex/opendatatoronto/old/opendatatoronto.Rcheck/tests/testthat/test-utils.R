context("test-utils")

test_that("as_id throws error when passed a data frame that is not 1 row.", {
  expect_error(
    as_id(
      data.frame(id = c(1, 2))
    ),
    "must be a 1 row data frame or a length 1 character vector."
  )
  expect_error(
    as_id(
      data.frame(id = character())
    ),
    "must be a 1 row data frame or a length 1 character vector."
  )
})

test_that("as_id throws error when passed a list.", {
  expect_error(
    as_id(list(id = 1)),
    "must be a 1 row data frame or a length 1 character vector."
  )
})

test_that("as_id throws error when passed vector of length greater than 1.", {
  expect_error(
    as_id(c("ab", "cd")),
    "must be a 1 row data frame or a length 1 character vector."
  )
})

test_that("as_id throws error when passed a zero-length vector.", {
  expect_error(
    as_id(character()),
    "must be a 1 row data frame or a length 1 character vector."
  )
})

test_that("as_id throws error when passed a non-character vector.", {
  expect_error(
    as_id(1),
    "must be a 1 row data frame or a length 1 character vector."
  )
  expect_error(
    as_id(TRUE),
    "must be a 1 row data frame or a length 1 character vector."
  )
})

test_that('as_id returns the contents of the "id" column when it is passed a 1 row data frame.', {
  expect_equal(
    as_id(data.frame(id = "abcde")),
    "abcde"
  )
})

test_that("parse_package_title replaces non-alphanumeric characters with '-', converts to lowercase, strips repeating -s, and doesn't allow ending with a -", {
  expect_equal(parse_package_title("here is a test"), "here-is-a-test")
  expect_equal(parse_package_title("HERE IS ANOTHER"), "here-is-another")
  expect_equal(parse_package_title("and another one!"), "and-another-one")
  expect_equal(parse_package_title("one    more for good measure"), "one-more-for-good-measure")
  expect_equal(parse_package_title("1234 better check some numbers more!"), "1234-better-check-some-numbers-more")
})

test_that('check_id_in_df returns an error when passed a data frame that doesn\'t contain an "id" column.', {
  x <- data.frame(a = 1)
  expect_error(
    check_id_in_df(x, "x"),
    '`x` must contain a column "id".'
  )
})

test_that('check_id_in_df returns the "id" column when present.', {
  res <- check_id_in_df(data.frame(id = 5))
  expect_equal(
    names(res),
    "id"
  )
})

test_that("check_found errors when the resource doesn't exist.", {
  res <- try(ckanr::resource_show("12345"), silent = TRUE)
  expect_error(
    check_found(res, "12345", "resource"),
    '`resource` "12345" was not found.'
  )
})

test_that("check_limit returns error if limit is not a length 1 positive integer.", {
  expect_error(
    check_limit(limit = -1),
    "`limit` must be a positive integer."
  )
  expect_error(
    check_limit(limit = 0),
    "`limit` must be a positive integer."
  )
  expect_error(
    check_limit(limit = -Inf),
    "`limit` must be a positive integer."
  )
  expect_error(
    check_limit(limit = 1.2),
    "`limit` must be a positive integer."
  )
  expect_error(
    check_limit(limit = c(1, 2)),
    "`limit` must be a length 1 positive integer."
  )
})
