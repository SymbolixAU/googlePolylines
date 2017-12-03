context("encode")


test_that("encode algorithim works", {
  
  
  
})


test_that("*POINTs are encoded", {
  
  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))
  
  expect_true(
    encode(point)[[1]] == encode(lon = 144, lat = -37)
  )
  
  multipoint <- sf::st_sfc(sf::st_multipoint(x = matrix(c(144, 145, -37, -37), ncol = 2)))
  
  expect_true(
    all(encode(multipoint)[[1]] %in% c(encode(lon = 144, lat = -37), encode(lon = 145, lat = -37)))
  )
  
})


test_that("*LINES are encoded", {
  
  
})


