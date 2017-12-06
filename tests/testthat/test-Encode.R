context("encode")

## TODO
## - sf_GEOMETRY


test_that("encode coordinates algorithim works", {

  expect_equal(
    encodeCoordinates(lon = c(144.9731, 144.9729, 144.9731), 
                      lat = c(-37.8090, -37.8094, -37.8083)),
    "dqweFy`zsZnAd@yEe@"
  )
})


test_that("*POINTs are encoded", {

  encode14437 <- "~py`F__|mZ"
  encode14537 <- "~py`F_i_tZ"
  
  ## sfc
  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))

  expect_true(
    encode(point)[[1]] == encode14437
  )

  ## sf
  sf <- sf::st_sf(point)

  expect_true(
    encode(sf)[, 'point'][[1]] == encode14437
  )

  multipoint <- sf::st_sfc(sf::st_multipoint(x = matrix(c(144, 145, -37, -37), ncol = 2)))

  expect_true(
    all(encode(multipoint)[[1]] %in% c(encode14437, encode14537))
  )

  sf <- sf::st_sf(multipoint)

  expect_true(
    all(encode(sf)[, 'multipoint'][[1]]  %in% c(encode14437, encode14537))
  )

})


test_that("*LINES are encoded", {

  encodedLine <- "~py`F__|mZ~oR_pR~oR}oR"
  line <- sf::st_sfc(sf::st_linestring(matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol = 2)))

  expect_true(
    encode(line)[[1]] == encodedLine
  )

  sf <- sf::st_sf(line)
  
  expect_true(
    encode(sf)[[1]] == encodedLine
  )
  
  multilinestring <- sf::st_sfc(
    sf::st_multilinestring(
      list(
        matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol =2),
        matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol =2)
        )
      )
    )
 
  expect_true(
    encode(multilinestring)[[1]][1] == encodedLine
  )
  
  expect_true(
    encode(multilinestring)[[1]][2] == encodedLine
  )
  
})

test_that("*POLYGONS are encoded", {
  
  encodedLine <- "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  polygon <- sf::st_sfc(sf::st_polygon(
    list(matrix(c(144, 144.1, 144.2, 144, -37, -37.1, -37.2, -37), ncol = 2))
    ))
  
  expect_true(
    encode(polygon)[[1]] == "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  )
  
  sf <- sf::st_sf(geo = polygon)
  
  expect_true(
    encode(sf)[[1]] == "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  )
  
  m1 <- matrix(c(144, 144.1, 144.2, 144, -37, -37.1, -37.2, -37), ncol = 2)
  m2 <- m1 + 1
  
  m1encoded <- "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  m2encoded <- encodeCoordinates(m2[1:4], m2[5:8])
  
  multipolygon <- sf::st_sfc(sf::st_multipolygon(
    list(list(m1, m2))
  ))
  
  expect_true(
    all(encode(multipolygon)[[1]] %in% c(m1encoded, m2encoded))
  )
})


