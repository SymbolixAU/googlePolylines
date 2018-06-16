context("toimplement")


test_that("encoed objects printed", {

  ## WKT attribute
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('wkt', class(enc))
  attr(enc, 'wkt_column') <- 'polyline'
  
  expect_true(inherits(withVisible(enc)$value, "wkt"))
  expect_true(inherits(withVisible(googlePolylines:::print.wkt(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.wkt(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.wkt(enc))$value, "data.frame"))
  
  ## NO attribute column
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('wkt', class(enc))
  expect_output(print(enc))
})
  
