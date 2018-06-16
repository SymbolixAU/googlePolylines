context("wkt")


test_that("wkt generated for all geometries", {
  
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

  enc <- encode(sf)
  wkt <- polyline_wkt(enc)
  
  ## TODO(set precision)
  # expect_equal("POINT (-80.19 26.774)", as.character(wkt[1, 'geo']) )
  # expect_equal("MULTIPOINT ((-80.19 26.774),(-66.118 18.466))",as.character(wkt[2, 'geo']))
  # expect_equal("LINESTRING (-70 22, -49 23, -51 22, -70 22)",as.character(wkt[3, 'geo']))
  # expect_equal(
  #   "MULTILINESTRING ((-80.19 26.774, -66.118 18.466, -64.757 32.321, -80.19 26.774),(-70.579 28.745, -67.514 29.57, -66.668 27.339, -70.579 28.745))",
  #   as.character(wkt[4, 'geo'])
  #   )
  # expect_equal(
  #   "POLYGON ((-80.19 26.774, -66.118 18.466, -64.757 32.321, -80.19 26.774),(-70.579 28.745, -67.514 29.57, -66.668 27.339, -70.579 28.745))",
  #   as.character(wkt[5, 'geo'])
  # )
  # expect_equal(
  #   "MULTIPOLYGON (((-80.19 26.774, -66.118 18.466, -64.757 32.321, -80.19 26.774),(-70.579 28.745, -67.514 29.57, -66.668 27.339, -70.579 28.745)),((-70 22, -49 23, -51 22, -70 22)))",
  #   as.character(wkt[6, 'geo'])
  # )
  expect_error(polyline_wkt(sf),"I was expecting an sfencoded object or an encoded_column")
})


test_that("wkt converted back to encoded_column", {
  
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
  
  enc <- encode(sf)
  wkt <- polyline_wkt(enc)
  e <- wkt_polyline(wkt)
  
  expect_true(paste0("sfc_", attr(enc, "sfAttributes")$type ) == class(sf$geo)[1])
  expect_true(paste0("sfc_", attr(e, "sfAttributes")$type ) == class(sf$geo)[1])
  expect_true(all.equal(class(enc), class(e))) 
  expect_true(attr(enc, "encoded_column") == attr(e, "encoded_column"))
  ## TODO(fix precision)
  # r <- 1
  # expect_true(enc[r, 'geo'][[1]] == e[r, 'geo'][[1]])
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  # r <- 2
  # expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  # r <- 3
  # expect_true(enc[r, 'geo'][[1]] == e[r, 'geo'][[1]])
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  # r <- 4
  # expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])  
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  # r <- 5
  # expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  # r <- 6
  # expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])  
  # expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfc'), attr(e[r, 'geo'][[1]], 'sfc')))
  
  ## test errors
  expect_error(wkt_polyline(enc),"I was expecting a charactor vector or a wkt object with a wkt_column")
  expect_error(polyline_wkt(wkt),"I was expecting an sfencoded object or an encoded_column")
  expect_error(wkt_polyline(sf),"I was expecting a charactor vector or a wkt object with a wkt_column")
})

