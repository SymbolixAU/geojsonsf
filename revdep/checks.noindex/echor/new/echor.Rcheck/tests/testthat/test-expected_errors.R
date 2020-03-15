context("core functions return expected errors")

test_that("core functions returns expected errors", {
  expect_error(echoAirGetFacilityInfo(), "No valid arguments supplied")
  expect_error(echoGetReports(program = "sdw"),
               "the argument 'program' must be specified as one of 'caa' or 'cwa'")
  expect_error(echoSDWGetSystems(),
               "No valid arguments supplied")

  #echoWaterGetFacilityInto returns error when no args uses, or incorrect output specified
  expect_error(echoWaterGetFacilityInfo(), "No valid arguments supplied")

  ##this test takes to long. need to check the output argument before calling the api.
  #expect_error(echoWaterGetFacilityInfo(p_pid = "ALR040033", output = "JSON"))

  #echoWaterSetParams returns error when both arg used or no args used
  expect_error(echoWaterGetParams(term = "Oxygen, dissolved", code = "00300"))
  expect_error(echoWaterGetParams())

  #echoGetFacilities returns error when specifying sf for sdw program
  expect_error(echoGetFacilities(program = "sdw", p_co = "Brazos", p_st = "tx", verbose = FALSE, output = "sf"))

  #echoGetFacilities returns error when wrong program specified
  expect_error(echoGetFacilities(program = "abc"))
  })
