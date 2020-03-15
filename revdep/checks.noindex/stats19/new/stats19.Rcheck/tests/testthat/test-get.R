context("test-get")

test_that("get_stats19 works", {
  skip_download()
  veh = get_stats19(year = 2009, type = "veh")
  expect_true(nrow(veh) > 100000)
  cas = get_stats19(year = 2009, type = "cas")
  expect_true(nrow(cas) > 100000)
  acc = get_stats19(year = 2009, type = "acc")
  expect_true(nrow(acc) > 100000)
  acc = get_stats19(year = 2009)
  expect_true(nrow(acc) > 100000)
  # get_stats19 defaults to accidents and downloads first
  # from menu (2017) so multilple will found for read_
  # which is expected.
  expect_error(get_stats19(type = "veh"))

  # check class of output_format
  acc_tibble = get_stats19(year = 2009, type = "acc")
  acc_data_frame = get_stats19(year = 2009, type = "acc", output_format = "data.frame")
  acc_sf = get_stats19(year = 2009, type = "acc", output_format = "sf")
  acc_ppp = get_stats19(year = 2009, type = "acc", output_format = "ppp")

  expect_true(is(acc_tibble, "tbl_df"))
  expect_s3_class(acc_data_frame, "data.frame")
  expect_true(is(acc_sf, "sf"))
  expect_true(is(acc_ppp, "ppp"))

  # if the output format is not c("tibble", "sf", "ppp") then it returns NULL
  expect_warning({acc = get_stats19(2009, "acc", output_format = "abcdef")})
  expect_true(is(acc, "tbl_df"))

  # raise warning if output_format = "sf" and type = "cas". Defaulting to
  # tbl output format.
  expect_warning({acc = get_stats19(2010, type = "cas", output_format = "sf")})
  expect_true(is(acc, "tbl_df"))
})

test_that("get_stats19 multiple years", {
  t09 = get_stats19(year = 2009)
  t15 = get_stats19(year = 2015)
  t16 = get_stats19(year = 2016)
  t = get_stats19(year = c(2009, 2015, 2016))

  expect_equal(nrow(t), sum(nrow(t09), nrow(t15), nrow(t16)))
})

test_that("get_stats19 works with multiple years and formats", {
  cas_2013 <- get_stats19(2013, type = "cas", silent = TRUE)
  cas_2014 <- get_stats19(2014, type = "cas", silent = TRUE)
  cas_2015 <- get_stats19(2015, type = "cas", silent = TRUE)
  expect_equal(
    length(
    names(cas_2014)[!names(cas_2014) %in% names(cas_2013)]),
    1)
  expect_equal(
    length(
      names(cas_2015)[!names(cas_2015) %in% names(cas_2014)]),
    1)
  t1315 <- get_stats19(2013:2015, output_format = "sf", silent = TRUE)
  expect_s3_class(t1315, "sf")

  t1315 <- get_stats19(2013:2015, output_format = "ppp", silent = TRUE)
  expect_s3_class(t1315, "ppp")

  t1315 <- get_stats19(2013:2015, silent = TRUE)
  expect_s3_class(t1315, "tbl_df")

  cas1315 = get_stats19(2013:2015, type = "cas")
  # not missing cols
  expect_true(any(grepl("age_of_casualty", names(cas1315))))
  expect_true(any(grepl("casualty_imd_decile", names(cas1315))))
  # not missing rows
  expect_equal(
    nrow(cas_2013) + nrow(cas_2014) + nrow(cas_2015),
    nrow(cas1315)
  )
})


