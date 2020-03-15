context("test-utils")

source("../skip-download.R")

test_that("geturl works", {
  expect_equal(get_url(),
               file.path("http://data.dft.gov.uk.s3.amazonaws.com",
                         "road-accidents-safety-data/")
               )
})

test_that("find_file_name works", {
  expect_true(length(find_file_name(type = "accid")) > 10)
  expect_equal(find_file_name(year = 2016, type = "accid"),
               "dftRoadSafety_Accidents_2016.zip")
  expect_equal(find_file_name(years ="2015", type = "accid"),
               "RoadSafetyData_Accidents_2015.zip")
  expect_equal(find_file_name(years = c("2005", "2006")),
               "Stats19_Data_2005-2014.zip")
  expect_silent(find_file_name(years = c("2014", "2015")))
  expect_silent(find_file_name(years = 2009))
  expect_equal(length(find_file_name(years = c("2014", "2015"),
                                      type = "Accident")), 2)
  # cover https://github.com/ITSLeeds/stats19/issues/21
  expect_equal (length (find_file_name(years = 1980:2001)), 1)
  # start OR end year is between 79 and 04
  expect_error (find_file_name(years = 1974:2004))
  expect_error (find_file_name(years = -1))
  #expect_error (find_file_name(years = "text"))
  # TODO: Should this be a message rather than error?:
  expect_error (find_file_name(years = 1973))
})

test_that("locate_files & locate_one_file works", {
  fn = stats19::file_names$dftRoadSafetyData_Casualties_2017.zip
  skip_download()
  dl_stats19(file_name = fn)
  x = locate_files(years = 2017, type = "cas")
  expect_true(length(x) > 0) # other files would have been downloaded already
  x1 = locate_one_file(filename = "Cas.csv", year = 2017, type = "casualties")
  expect_true(length(x1) == 1)
  # now multiple
  fn = stats19::file_names$dftRoadSafetyData_Casualties_2016.zip
  dl_stats19(file_name = fn)
  x2 = locate_one_file(filename = "Cas.csv", year = 2017, type = "cas")
  expect_true(length(x1) == 1)
  # more tests on locate_files
  expect_error(locate_files(year = 2045))
  # from clean start
  unlink(tempdir(), recursive = TRUE)
  dir.create(tempdir())
  expect_error(locate_files(data_dir = "/junking"),
               "dir.exists\\(data_dir\\) is not TRUE")
})
