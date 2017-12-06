context("encode")

# test_that("encode algorithim works", {
#   
#   expect_equal(
#     encode(lon = c(144.9731, 144.9729, 144.9731), lat = c(-37.8090, -37.8094, -37.8083)),
#     "dqweFy`zsZnAd@yEe@"
#   )
# })


test_that("*POINTs are encoded", {

  ## sfc
  # p <- c(144, -37)
  # attr(p, 'class') <- c("XY", "POINT", "sfg")


  # p <- list(p)
  # attr(p, 'class') <- c("sfc_POINT", "sfc", class(p))
  encode14437 <- "~py`F__|mZ"
  encode14537 <- "~py`F_i_tZ"

  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))

  expect_true(
    encode(point)[[1]] == encode14437
  )

  ## sf
  sf <- sf::st_sf(point)

  expect_true(
    encode(sf)[, 'point'][[1]] == encode14437
  )

  ## sfc
  multipoint <- sf::st_sfc(sf::st_multipoint(x = matrix(c(144, 145, -37, -37), ncol = 2)))

  expect_true(
    all(encode(multipoint)[[1]] %in% c(encode14437, encode14537))
  )

  ## sf
  sf <- sf::st_sf(multipoint)

  expect_true(
    all(encode(sf)[, 'multipoint'][[1]]  %in% c(encode14437, encode14537))
  )

})


# test_that("*LINES are encoded", {
# 
#   line <- sf::st_sfc(sf::st_linestring(matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol = 2)))
# 
#   expect_true(
#     encode(line)[[1]] == encode(lon = c(144, 144.1, 144.2), lat = c(-37, -37.1, -37.2))
#   )
# 
#   sf <- sf::st_sf(line)
# 
# })
