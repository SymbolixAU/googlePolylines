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


test_that("sf_GEOMETRYs are encoded", {
  
  df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
                   lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
                   lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
                   lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
  
  p1 <- as.matrix(df[1:4, c("lon", "lat")])
  p2 <- as.matrix(df[5:8, c("lon", "lat")])
  p3 <- as.matrix(df[9:12, c("lon", "lat")])
  
  point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
  multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
  polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
  linestring <- sf::st_sfc(sf::st_linestring(p3))
  multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
  multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))
  
  sf <- rbind(
    sf::st_sf(geo = point),
    sf::st_sf(geo = multipoint),
    sf::st_sf(geo = linestring),
    sf::st_sf(geo = multilinestring),
    sf::st_sf(geo = polygon),
    sf::st_sf(geo = multipolygon)
  )
  
  
  encoded <- encode(sf)
  
  expect_true(
    encoded$geo[[1]] == encode(point)
  )
  
  expect_true(
    all(encoded$geo[[2]] %in% encode(multipoint)[[1]])
  )
  
  expect_true(
    encoded$geo[[3]] == encode(linestring)
  )
  
  expect_true(
    all(encoded$geo[[4]] %in% encode(multilinestring)[[1]])
  )
  
  expect_true(
    all(encoded$geo[[5]] %in% encode(polygon)[[1]])
  )
  
  expect_true(
    all(encoded$geo[[6]] %in% encode(multipolygon)[[1]])
  )
  
  
})
