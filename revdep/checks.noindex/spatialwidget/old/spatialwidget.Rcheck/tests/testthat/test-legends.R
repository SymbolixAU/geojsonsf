context("legends")


test_that("legends are formatted", {

  ## Numeric
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = 1:4)

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["1.00","2.00","3.00","4.00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## factor
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = letters[1:4])

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["1.00","2.00","3.00","4.00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## character
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = letters[1:4], stringsAsFactors = FALSE)

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["a","b","c","d"],"colourType":["fill_colour"],"type":["category"],"title":["col"],"css":[""]}}')

  ## Logical
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = c(T,F,T,T))

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#FDE725FF"],"variable":["FALSE","TRUE"],"colourType":["fill_colour"],"type":["category"],"title":["col"],"css":[""]}}')

  ## Date
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = seq(as.Date("2018-01-01"), as.Date("2018-01-04"), length.out = 4))

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01","2018-01-02","2018-01-03","2018-01-04"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## POSIXct
  df <- data.frame(
    lon = c(1,2,-5,0.3)
    , lat = 1:4
    , col = seq(as.POSIXct("2018-01-01", tz= "UTC")
                , as.POSIXct("2018-01-04", tz="UTC")
                , length.out = 4)
    )

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01T00:00:00","2018-01-02T00:00:00","2018-01-03T00:00:00","2018-01-04T00:00:00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## POSIXlt (as POSIXct because in data.frame)
  df <- data.frame(
    lon = c(1,2,-5,0.3)
    , lat = 1:4
    , col = seq(as.POSIXlt("2018-01-01", tz="UTC")
                , as.POSIXlt("2018-01-04", tz="UTC")
                , length.out = 4)
    )

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01T00:00:00","2018-01-02T00:00:00","2018-01-03T00:00:00","2018-01-04T00:00:00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')


})
