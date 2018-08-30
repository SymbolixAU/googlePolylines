context("encode")

## TODO
## - sf_GEOMETRY

test_that("google's example encodes correctly", {
  df <- data.frame(lat = c(38.5, 40.7, 43.252), lon = c(-120.2, -120.95, -126.453))
  expect_true(encode(df) == "_p~iF~ps|U_ulLnnqC_mqNvxq`@")
})

test_that("encoding by row is accurate", {
  
  testthat::skip_on_cran()
  
  df <- data.frame(lat = c(38, 40, 43),lon = c(-120, -120, -126))
  expect_true(length(encode(df, byrow = T)) == 3)
  expect_equal(df, do.call(rbind, decode( encode( df, byrow = T ) ) ))
})

test_that("encode coordinates algorithim works", {
  expect_equal(
    encodeCoordinates(lon = c(144.9731, 144.9729, 144.9731), 
                      lat = c(-37.8090, -37.8094, -37.8083)),
    "dqweFy`zsZnAd@yEe@")
})


test_that("*POINTs are encoded", {

  testthat::skip_on_cran()
  library(sf)
  encode14437 <- "~py`F__|mZ"
  encode14537 <- "~py`F_i_tZ"
  
  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))
  expect_true(encode(point)[[1]] == encode14437)

  sf <- sf::st_sf(point)
  expect_true(encode(sf)[, 'point'][[1]] == encode14437)
  multipoint <- sf::st_sfc(sf::st_multipoint(x = matrix(c(144, 145, -37, -37), ncol = 2)))
  expect_true(all(encode(multipoint)[[1]] %in% c(encode14437, encode14537)))
  sf <- sf::st_sf(multipoint)
  expect_true(all(encode(sf)[, 'multipoint'][[1]]  %in% c(encode14437, encode14537)))
})


test_that("UNKNOWN geometry & sf type", {
  
  testthat::skip_on_cran()
  library(sf)
  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))
  class(point) <- c("sfc_NEWPOINT", "sfc")
  expect_error(encode(point),"encoding this sf type is currently not supported")
  point <- sf::st_sfc(sf::st_point(x = c(144, -37)))
  enc <- encode(point)
  expect_error(polyline_wkt(enc),"I was expecting an sfencoded object or an encoded_column")
})

test_that("*LINES are encoded", {

  testthat::skip_on_cran()
  library(sf)
  encodedLine <- "~py`F__|mZ~oR_pR~oR}oR"
  line <- sf::st_sfc(sf::st_linestring(matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol = 2)))
  expect_true(encode(line)[[1]] == encodedLine)
  sf <- sf::st_sf(line)
  expect_true(encode(sf)[[1]] == encodedLine)
  multilinestring <- sf::st_sfc(
    sf::st_multilinestring(
      list(matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol =2),
           matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol =2))))
  expect_true(encode(multilinestring)[[1]][1] == encodedLine)
  expect_true(encode(multilinestring)[[1]][2] == encodedLine)
})

test_that("*POLYGONS are encoded", {

  testthat::skip_on_cran()
  library(sf)
  encodedLine <- "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  polygon <- sf::st_sfc(sf::st_polygon(
    list(matrix(c(144, 144.1, 144.2, 144, -37, -37.1, -37.2, -37), ncol = 2))))
  expect_true(encode(polygon)[[1]] == "~py`F__|mZ~oR_pR~oR}oR_af@|`f@")
  sf <- sf::st_sf(geo = polygon)
  expect_true(encode(sf)[[1]] == "~py`F__|mZ~oR_pR~oR}oR_af@|`f@")
  m1 <- matrix(c(144, 144.1, 144.2, 144, -37, -37.1, -37.2, -37), ncol = 2)
  m2 <- m1 + 1
  m1encoded <- "~py`F__|mZ~oR_pR~oR}oR_af@|`f@"
  m2encoded <- encodeCoordinates(m2[1:4], m2[5:8])
  multipolygon <- sf::st_sfc(sf::st_multipolygon(list(list(m1, m2))))
  expect_true(all(encode(multipolygon)[[1]] %in% c(m1encoded, m2encoded)))
})


test_that("sf_GEOMETRYs are encoded", {
  
  testthat::skip_on_cran()
  library(sf)
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
  expect_true(encoded$geo[[1]] == encode(point))
  expect_true(all(encoded$geo[[2]] %in% encode(multipoint)[[1]]))
  expect_true(encoded$geo[[3]] == encode(linestring))
  expect_true(all(encoded$geo[[4]] %in% encode(multilinestring)[[1]]))
  expect_true(all(encoded$geo[[5]] %in% encode(polygon)[[1]]))
  expect_true(all(encoded$geo[[6]] %in% encode(multipolygon)[[1]]))
})


test_that("data.frames are encoded", {
  testthat::skip_on_cran()
  df <- data.frame(polygonId = c(1,1,1,1),
    lineId = c(1,1,1,1),
    lon = c(-80.190, -66.118, -64.757, -80.190),
    lat = c(26.774, 18.466, 32.321, 26.774))
  expect_true(encode(df) == "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A")
})

test_that("default encoding method errors", {
  expect_error(encode(list()),"I currently don't know how to encode list objects")
  expect_error(encode(NULL),"I currently don't know how to encode NULL objects")
})

test_that("GEOMETRYCOLLECTIONS error", {
  
  testthat::skip_on_cran()
  library(sf)
  df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
                   lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
                   lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
                   lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
  
  p1 <- as.matrix(df[1:4, c("lon", "lat")])
  p2 <- as.matrix(df[5:8, c("lon", "lat")])
  p3 <- as.matrix(df[9:12, c("lon", "lat")])
  point <- sf::st_point(x = c(df[1,"lon"], df[1,"lat"]))
  polygon <- sf::st_polygon(x = list(p1, p2))
  linestring <- sf::st_linestring(p3)
  sf <- sf::st_sfc(geo = sf::st_geometrycollection(x = list(point, linestring, polygon)))
  expect_error(encode(sf),"encoding this sf type is currently not supported")
})


test_that("Z and M attributes are encoded", {
  
  testthat::skip_on_cran()
  library(sf)

  z <- 1:21
  zm <- 1:36
  
  ## POINT
  pz <- sf::st_point(c(1,2,3))
  pzm <- sf::st_point(1:4)
  
  ## MULTIPOINT
  mpz <- sf::st_multipoint(x = matrix(z, ncol = 3))
  mpzm <- sf::st_multipoint(x = matrix(zm, ncol = 4))
  
  ## LINESTRING
  lz <- sf::st_linestring(x = matrix(z, ncol = 3))
  lzm <- sf::st_linestring(x = matrix(zm, ncol = 4))
  
  lz2 <- sf::st_linestring(x = matrix(z, ncol = 3))
  lzm2 <- sf::st_linestring(x = matrix(zm, ncol = 4))
  
  ## MULTILINESTRING
  mlz <- sf::st_multilinestring(x = list(lz,lz))
  mlzm <- sf::st_multilinestring(x = list(lzm, lzm))
  
  ## POLYGON
  pl1 <- c(0,0,1,1,0,2,1,1,3,0,1,4,0,0,1)  ## start and end elevation must match
  plz <- sf::st_polygon(x = list(matrix(pl1, ncol = 3, byrow = T)))
  pl2 <- c(0,0,1,2,1,0,1,3,1,1,1,6,0,1,1,9,0,0,1,2)
  plzm <- sf::st_polygon(x = list(matrix(pl2, ncol = 4, byrow = T)))
  
  ## MULTIPOLYGON
  mplz <- sf::st_multipolygon(x = list(plz, plz))
  mplzm <- sf::st_multipolygon(x = list(plzm, plzm))

  sfcpz <- sf::st_sfc(pz)
  sfpz <- sf::st_sf(geometry = sfcpz)
  sfcpzm <- sf::st_sfc(pzm)
  sfpzm <- sf::st_sf(geometry = sfcpzm)
  
  sfcmpz <- sf::st_sfc(mpz)
  sfmpz <- sf::st_sf(geometry = sfcmpz)
  
  sfcmpzm <- sf::st_sfc(mpzm)
  sfmpzm <- sf::st_sf(geometry = sfcmpzm)
  
  sfclz <- sf::st_sfc(lz)
  sflz <- sf::st_sf(geometry = sfclz)
  sfclzm <- sf::st_sfc(lzm)
  sflzm <- sf::st_sf(geometry = sfclzm)
  
  sfclz2 <- sf::st_sfc(lz2)
  sflz2 <- sf::st_sf(geometry = sfclz2)
  sfclzm2 <- sf::st_sfc(lzm2)
  sflzm2 <- sf::st_sf(geometry = sfclzm2)
  
  sfcmlz <- sf::st_sfc(mlz)
  sfmlz <- sf::st_sf(geometry = sfcmlz)
  sfcmlzm <- sf::st_sfc(mlzm)
  sfmlzm <- sf::st_sf(geometry = sfcmlzm)
  
  sfcplz <- sf::st_sfc(plz)
  sfplz <- sf::st_sf(geometry = sfcplz)
  sfcplzm <- sf::st_sfc(plzm)
  sfplzm <- sf::st_sf(geometry = sfcplzm)
  
  sfcmplz <- sf::st_sfc(mplz)
  sfmplz <- sf::st_sf(geometry = sfcmplz)
  sfcmplzm <- sf::st_sfc(mplzm)
  sfmplzm <- sf::st_sf(geometry = sfcmplzm)
  
  ## TESTING the lon & lats, AND the Z and M are encoded
  
  ## POINT
  ep <- encodeCoordinates(lon = 1, lat = 2)
  epz <- encodeCoordinates(lon = 3, lat = 0)
  epzm <- encodeCoordinates(lon = 3, lat = 4)
  
  # expect_true( encode( sfcpz )[['XY']] == ep )
  # expect_true( encode( sfcpz )[['ZM']] == epz )
  
  expect_true( encode( sfpz )[, 'geometry'] == ep )
  # expect_true( encode( sfpz)[, 'geometryZM'] == epz )
  
  # expect_true( encode( sfcpzm )[['XY']] == ep )
  # expect_true( encode( sfcpzm )[['ZM']] == epzm )
  
  expect_true( encode( sfpzm )[, 'geometry'] == ep )
  # expect_true( encode( sfpzm )[, 'geometryZM'] == epzm )
  
  ## MULTIPOINT
  dfz <- stats::setNames( data.frame(matrix(z, ncol = 3)), c("lon", "lat", "Z"))
  dfz$M <- 0
  
  dfzm <- stats::setNames( data.frame(matrix(zm, ncol = 4)), c("lon","lat","Z","M"))
  
  # expect_true( all( encode( sfcmpz )[['XY']][[1]] == encode( dfz, byrow = T ) ) )
  # expect_true( all( encode( sfcmpz )[['ZM']][[1]] == encode( dfz, lon = "Z", lat = "M", byrow = T)))
  expect_true( all( encode( sfmpz )[, 'geometry'][[1]] == encode( dfz, byrow = T ) ))
  # expect_true( all( encode( sfmpz )[, 'geometryZM'][[1]] == encode( dfz, lon = "Z", lat = "M", byrow = T) ))
  # expect_true( all( encode( sfcmpzm )[['XY']][[1]] == encode( dfzm, byrow = T )))
  # expect_true( all( encode( sfcmpzm )[['ZM']][[1]] == encode( dfzm, lon = "Z", lat = "M", byrow = T)))
  expect_true( all( encode( sfmpzm )[, 'geometry'][[1]] == encode( dfzm, byrow = T ) ))
  # expect_true( all( encode( sfmpzm )[, 'geometryZM'][[1]] == encode( dfzm, lon = "Z", lat = "M", byrow = T)))
  
  ## LINESTRING
  # expect_true( encode( sfclz )[['XY']] == encode( dfz ) )
  # expect_true( encode( sfclz )[['ZM']] == encode( dfz, lon = "Z", lat = "M"))
  expect_true( encode( sflz )[, 'geometry'][[1]] == encode( dfz ) )
  # expect_true( encode( sflz )[, 'geometryZM'][[1]] == encode( dfz, lon = "Z", lat = "M"))
  # expect_true( encode( sfclzm )[['XY']][[1]] == encode( dfzm ) )
  # expect_true( encode( sfclzm )[['ZM']][[1]] == encode( dfzm, lon = "Z", lat = "M"))
  expect_true( encode( sflzm )[, 'geometry'][[1]] == encode( dfzm ) )
  # expect_true( encode( sflzm )[, 'geometryZM'][[1]] == encode( dfzm, lon = "Z", lat = "M"))
  
  ## MULTILINESTRING
  # expect_true( all( encode( sfcmlz )[['XY']][[1]] == rep( encode( dfz ), 2) ) )
  # expect_true( all( encode( sfcmlz )[['ZM']][[1]] == rep( encode( dfz, lon = "Z", lat = "M"), 2)))
  expect_true( all( encode( sfmlz )[, 'geometry'][[1]] == rep( encode( dfz ), 2)))
  # expect_true( all( encode( sfmlz )[, 'geometryZM'][[1]] == rep( encode( dfz, lon = "Z", lat = "M"), 2)))
  # expect_true( all( encode( sfcmlzm )[['XY']][[1]] == rep( encode( dfzm ), 2) ))
  # expect_true( all( encode( sfcmlzm )[['ZM']][[1]] == rep( encode( dfzm, lon = "Z", lat = "M"), 2)))
  expect_true( all( encode( sfmlzm )[, 'geometry'][[1]] == rep( encode( dfzm ), 2)))
  # expect_true( all( encode( sfmlzm )[, 'geometryZM'][[1]] == rep( encode( dfzm, lon = "Z", lat = "M"), 2)))
  
  ## POLYGON
  dfplz <- stats::setNames( data.frame( matrix( pl1 , ncol = 3, byrow = T)), c("lon","lat","Z"))
  dfplz$M <- 0
  dfplzm <- stats::setNames( data.frame( matrix( pl2, ncol = 4, byrow = T)), c("lon","lat","Z","M"))
  
  # expect_true( encode( sfcplz )[['XY']][[1]] == encode( dfplz ) )
  # expect_true( encode( sfcplz )[['ZM']][[1]] == encode( dfplz, lon = "Z", lat = "M") )
  expect_true( encode( sfplz )[, 'geometry'][[1]] == encode( dfplz ) )
  # expect_true( encode( sfplz )[, 'geometryZM'][[1]] == encode( dfplz, lon = "Z", lat = "M"))
  # expect_true( encode( sfcplzm )[['XY']] == encode( dfplzm ))
  # expect_true( encode( sfcplzm )[['ZM']][[1]] == encode( dfplzm, lon = "Z", lat = "M"))
  expect_true( encode( sfplzm )[, 'geometry'][[1]] == encode( dfplzm ))
  # expect_true( encode( sfplzm )[, 'geometryZM'][[1]] == encode( dfplzm, lon = "Z", lat = "M"))
  
  ## MULTIPOLYGON
  # expect_true( all( encode( sfcmplz )[['XY']][[1]] == c( encode( dfplz ), "-", encode( dfplz ))))
  # expect_true( all( encode( sfcmplz )[['ZM']][[1]] == c( encode( dfplz, lon = "Z", lat = "M"), "-", encode( dfplz, lon = "Z", lat = "M"))))
  expect_true( all( encode( sfmplz )[, 'geometry'][[1]] == c(encode( dfplz ), "-", encode( dfplz ))))
  # expect_true( all( encode( sfmplz )[, 'geometryZM'][[1]] == c( encode( dfplz, lon = "Z", lat = "M"), "-", encode( dfplz, lon = "Z", lat = "M"))))
  # expect_true( all( encode( sfcmplzm )[['XY']][[1]] == c( encode( dfplzm ), "-", encode( dfplzm ) ) ))
  # expect_true( all( encode( sfcmplzm )[['ZM']][[1]] == c( encode( dfplzm, lon = "Z", lat = "M"), "-", encode( dfplzm, lon = "Z", lat = "M"))))
  expect_true( all( encode( sfmplzm )[, 'geometry'][[1]] == c( encode( dfplzm ), "-", encode( dfplzm ))))
  # expect_true( all( encode( sfmplzm )[, 'geometryZM'][[1]] == c( encode( dfplzm, lon = "Z", lat = "M"), "-", encode( dfplzm, lon = "Z", lat = "M"))))

  ## Mixture of dimensions
  sf <- rbind(sfpz, sfpzm, sflz, sflzm, sfmlz, sfmlzm, sfplz, sfmplzm)
  enc <- encode( sf )
  expect_true(enc[1, 'geometry'][[1]] == encode( sfpz )[['geometry']] )
  expect_true(enc[2, 'geometry'][[1]] == encode( sfpzm )[['geometry']] )
  expect_true(enc[3, 'geometry'][[1]] == encode( sflz )[['geometry']] )
  expect_true(enc[4, 'geometry'][[1]] == encode( sflzm )[['geometry']] )
  expect_true(all( enc[5, 'geometry'][[1]] == encode( sfmlz )[['geometry']][[1]] ) )
  expect_true(all( enc[6, 'geometry'][[1]] == encode( sfmlzm )[['geometry']][[1]] ))
  expect_true(all( enc[7, 'geometry'][[1]] == encode( sfplz )[['geometry']][[1]]))
  expect_true(all( enc[8, 'geometry'][[1]] == encode( sfmplzm )[['geometry']][[1]] ) )
})

# test_that("dimension attributes attached", {
#   
#   # testthat::skip_on_cran()
#   # library(sf)
#   # 
#   # z <- 1:21
#   # zm <- 1:36
#   # 
#   # ## POINT
#   # pz <- sf::st_point(c(1,2,3))
#   # pzm <- sf::st_point(1:4)
#   # 
#   # ## MULTIPOINT
#   # mpz <- sf::st_multipoint(x = matrix(z, ncol = 3))
#   # mpzm <- sf::st_multipoint(x = matrix(zm, ncol = 4))
#   # 
#   # ## LINESTRING
#   # lz <- sf::st_linestring(x = matrix(z, ncol = 3))
#   # lzm <- sf::st_linestring(x = matrix(zm, ncol = 4))
#   # 
#   # sfcpz <- sf::st_sfc(pz)
#   # sfpz <- sf::st_sf(geometry = sfcpz)
#   # sfcpzm <- sf::st_sfc(pzm)
#   # sfpzm <- sf::st_sf(geometry = sfcpzm)
#   # 
#   # sfcmpz <- sf::st_sfc(mpz)
#   # sfmpz <- sf::st_sf(geometry = sfcmpz)
#   # 
#   # sfcmpzm <- sf::st_sfc(mpzm)
#   # sfmpzm <- sf::st_sf(geometry = sfcmpzm)
#   # 
#   # sfclz <- sf::st_sfc(lz)
#   # sflz <- sf::st_sf(geometry = sfclz)
#   # sfclzm <- sf::st_sfc(lzm)
#   # sflzm <- sf::st_sf(geometry = sfclzm)
#   # 
#   # sf <- rbind(sfpz, sfpzm, sfmpz, sfmpzm, sflz, sflzm)
#   # enc <- encode( sf )
#   # 
#   # expect_true( attr(enc, 'zm_column') == 'geometryZM')
#   # expect_true( attr(enc[1, 'geometryZM'][[1]], 'zm') == "XYZ" )
#   # expect_true( attr(enc[2, 'geometryZM'][[1]], 'zm') == "XYZM")
#   # 
#   # encLite <- encode( sf, strip = T)
#   # expect_null( attributes(encLite[['geometryZM']][[1]]))
#   
# })
# 
# 
# test_that("ZM column deconflicts existing columns", {
#   
#   # testthat::skip_on_cran()
#   # library(sf)
#   # 
#   # z <- 1:21
#   # zm <- 1:36
#   # pz <- sf::st_point(c(1,2,3))
#   # pzm <- sf::st_point(1:4)
#   # sf1 <- sf::st_sf(geometry = sf::st_sfc(pz))
#   # sf2 <- sf::st_sf(geometry = sf::st_sfc(pzm))
#   # sf <- rbind(sf1, sf2)
#   # 
#   # sf$geometryZM <- 1:2
#   # 
#   # expect_true(all(names(encode( sf )) == c(names(sf), 'geometryZM.1')))
#   
# })

test_that("emptry geometries are handled", {
  
  testthat::skip_on_cran()
  testthat::skip_on_travis()
  
  library(sf)
  
  ept <- sf::st_sfc(sf::st_point())
  sfept <- sf::st_sf(geometry = ept)
  emp <- sf::st_sfc(sf::st_multipoint())
  sfemp <- sf::st_sf(geometry = emp)
  el <- sf::st_sfc(sf::st_linestring())
  sfel <- sf::st_sf(geometry = el )
  eml <- sf::st_sfc(sf::st_multilinestring())
  sfeml <- sf::st_sf(geometry = eml )
  epl <- sf::st_sfc(sf::st_polygon())
  sfepl <- sf::st_sf(geometry = epl)
  empl <- sf::st_sfc(sf::st_multipolygon())
  sfempl <- sf::st_sf(geometry = empl)
  
  enc <- encode(ept)
  expect_true(enc[[1]] == ">>")
  enc <- encode(sfept)
  expect_true(enc$geometry[[1]] == ">>")
  
  enc <- encode(emp)
  expect_true(length(enc[[1]]) == 0)
  enc <- encode( sfemp )
  expect_true(length(enc$geometry[[1]]) == 0)
  
  enc <- encode(el)
  expect_true(length(enc[[1]]) == 0)
  enc <- encode( sfel )
  expect_true(length(enc$geometry[[1]]) == 0)
  
  enc <- encode(eml)
  expect_true(length(enc[[1]]) == 0)
  enc <- encode( sfeml )
  expect_true(length(enc$geometry[[1]]) == 0)
  
  enc <- encode(epl)
  expect_true(length(enc[[1]]) == 0)
  enc <- encode( sfepl )
  expect_true(length(enc$geometry[[1]]) == 0)
  
  enc <- encode(empl)
  expect_true(length(enc[[1]]) == 0)
  enc <- encode( sfempl )
  expect_true(length(enc$geometry[[1]]) == 0)
})
