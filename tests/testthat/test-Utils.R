context("utils")


test_that("lat and lon columns found", {
  
  df <- data.frame(lats = 1:3, long = 1:3)
  
  expect_true(
    googlePolylines:::find_lat_column(names(df)) == "lats"
  )
  
  expect_true(
    googlePolylines:::find_lon_column(names(df)) == "long"
  )
  
  df <- data.frame(myLat = 1:3, myLongitudes = 1:3)
  
  expect_error(
    googlePolylines:::find_lat_column(names(df)),
    "Couldn't infer latitude column"
  )
  
  expect_error(
    googlePolylines:::find_lon_column(names(df)),
    "Couldn't infer longitude column"
  )
  
})

