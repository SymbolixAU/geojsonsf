

context("Test the otp_connect function")

skip_if_no_otp <- function() {
  if(!identical(Sys.getenv("OTP_ON_LOCALHOST"), "TRUE"))
    skip("Not running test as the environment variable OTP_ON_LOCALHOST is not set to TRUE")
}

test_that("default object is created and make_url method works", {
  otpcon <- otp_connect(check = FALSE)
  expect_is(otpcon, "otpconnect")
  skip_if_no_otp()
  expect_match(make_url(otpcon), "http://localhost:8080/otp/routers/default")
})

# the following tests require an OTP instance at http://localhost:8080/otp with "default" router

test_that("object returned when check is TRUE and router exists", {
  skip_if_no_otp()
  otpcon <- otp_connect()
  expect_is(otpcon, "otpconnect")
})

test_that("correct message when check is TRUE and router exists", {
  skip_if_no_otp()
  expect_message(otp_connect(), "Router http://localhost:8080/otp/routers/default exists")
})


test_that("object is not returned when check is TRUE and router does not exist", {
  skip_if_no_otp()
  otpcon <- otp_connect(router = "test")
  expect_false(exists("otpcon"))
})

test_that("correct error when check is TRUE and router does not exist", {
  skip_if_no_otp()
  expect_error(otp_connect(router = "test"), "Router http://localhost:8080/otp/routers/test does not exist")
})

