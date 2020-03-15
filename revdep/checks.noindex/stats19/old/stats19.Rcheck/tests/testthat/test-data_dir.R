context("Get/Set STATS19_DOWNLOAD_DIRECTORY envvar")

test_that("Set STATS19_DOWNLOAD_DIRECTORY ", {
  expect_error(set_data_directory())

  test_path = file.path(tempdir(), "stats19")
  dir.create(test_path)
  # hold value
  c = get_data_directory()
  Sys.setenv(STATS19_DOWNLOAD_DIRECTORY = "")
  set_data_directory(test_path)
  expect_true(identical(get_data_directory(), test_path))
  # reset test user's prefs
  if(!identical(c, tempdir())) {
    set_data_directory(c)
  }
})

test_that("Get STATS19_DOWNLOAD_DIRECTORY ", {
  # TODO: we can do this abit more sophisticated
  c = Sys.getenv("STATS19_DOWNLOAD_DIRECTORY")
  if(c == "") c = tempdir()
  expect_true(identical(get_data_directory(), c))
})

test_that("Reset STATS19_DOWNLOAD_DIRECTORY ", {
  test_path = file.path(tempdir(), "stats19")
  dir.create(test_path)
  # hold value
  c = get_data_directory()
  Sys.setenv(STATS19_DOWNLOAD_DIRECTORY = "")
  set_data_directory(test_path)
  expect_true(identical(get_data_directory(), test_path))
  # reset test user's prefs
  if(!identical(c, tempdir())) {
    set_data_directory(c)
  }
})
