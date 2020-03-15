context("test-dl_stats19")

source("../skip-download.R")

test_that("dl_stats19 works for junk", {
  expect_error(dl_stats19(type = "junk"))
  expect_error(dl_stats19(year = "2999", type = "junk"))
})

test_that("dl_stats19 works for no data_dir", {
  skip_on_cran()
  # this test is bound to the next
  skip_download()
  # remove tempdir
  unlink(tempdir(), recursive = TRUE)
  expect_message(dl_stats19(year = "2017"))
  # tempdir created.
})

test_that("dl_stats19 works for 2017", {
  skip_on_cran()
  skip_download()
  # already downloaded
  expect_message(dl_stats19(year = "2017"),
                 "Data already exists in data_dir")
})

test_that("dl_stats19 works for a type", {
  skip_on_cran()
  skip_download()
  # already downloaded
  expect_message(dl_stats19(type = "accid"),
                 "More than one file found, selecting the first")
})

test_that("dl_stats19 works for chosen file name", {
  skip_on_cran()
  skip_download()
  expect_message(dl_stats19(
    file_name = stats19::file_names$DfTRoadSafety_Accidents_2009.zip),
                 "Files identified: DfTRoadSafety_Accidents_2009.zip")
})
