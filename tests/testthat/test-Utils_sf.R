context("sfattributes")

test_that("sf attributes are extracted", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  
  sfAttrs <- sfAttributes(enc)
  expect_equal(sfAttrs$type,"MULTIPOLYGON")
  expect_equal(sfAttrs$dim,"XY")
  expect_equal(round(sfAttrs$bbox[[1]],3),-84.324)
  expect_equal(round(sfAttrs$bbox[[2]], 3),33.882)
  expect_equal(round(sfAttrs$bbox[[3]],3),-75.457)
  expect_equal(round(sfAttrs$bbox[[4]],3),36.59)
  expect_equal(sfAttrs$epsg,4267)
  expect_equal(sfAttrs$proj,"+proj=longlat +datum=NAD27 +no_defs")
})


test_that("sf attributes extracted", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  ## from sf obj
  sfAttrs <- googlePolylines:::sfGeometryAttributes(nc)
  ## from sfc column
  sfcAttrs <- googlePolylines:::sfGeometryAttributes(nc[['geometry']])
  expect_equal(sfAttrs$type,"MULTIPOLYGON")
  expect_equal(sfcAttrs$type,"MULTIPOLYGON")
  expect_equal(sfAttrs$dim,"XY")
  expect_equal(sfcAttrs$dim,"XY")
  expect_equal(round(sfAttrs$bbox[[1]],3),-84.324)
  expect_equal(round(sfcAttrs$bbox[[1]],3),-84.324)
  expect_equal(round(sfAttrs$bbox[[2]], 3),33.882)
  expect_equal(round(sfcAttrs$bbox[[2]], 3),33.882)
  expect_equal(round(sfAttrs$bbox[[3]],3),-75.457)
  expect_equal(round(sfcAttrs$bbox[[3]],3),-75.457)
  expect_equal(round(sfAttrs$bbox[[4]],3),36.59)  
  expect_equal(round(sfcAttrs$bbox[[4]],3),36.59)
  expect_equal(sfAttrs$epsg,4267)
  expect_equal(sfcAttrs$epsg,4267)
  expect_equal(sfAttrs$proj,"+proj=longlat +datum=NAD27 +no_defs")
  expect_equal(sfcAttrs$proj,"+proj=longlat +datum=NAD27 +no_defs")
})


test_that("geometry rows extracted", {
  
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
    sf::st_sf(geo = polygon),
    sf::st_sf(geo = multilinestring),
    sf::st_sf(geo = linestring),
    sf::st_sf(geo = point)
  )
  enc <- encode(sf)
  expect_equal(geometryRow(enc, "POINT"),4)
  expect_true(all(c(2,3) %in% geometryRow(enc, "LINESTRING")))
  expect_equal(geometryRow(enc, "POLYGON"),1)
  expect_error(geometryRow(sf),"This function should be called on an sfencoded object")
  enc <- encode(sf, strip = TRUE)
  expect_error(polyline_wkt(enc),"No geometry attribute found")
})



