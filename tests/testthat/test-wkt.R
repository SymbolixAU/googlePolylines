context("wkt")

test_that("wkt converted back to encoded_column", {

  sf <- structure(list(geo = structure(list(structure(c(-80.19, 26.774
  ), class = c("XY", "POINT", "sfg")), structure(c(-80.19, -66.118, 
  26.774, 18.466), .Dim = c(2L, 2L), .Dimnames = list(c("1", "2"
  ), c("lon", "lat")), class = c("XY", "MULTIPOINT", "sfg")), structure(c(-70, 
  -49, -51, -70, 22, 23, 22, 22), .Dim = c(4L, 2L), .Dimnames = list(
  c("9", "10", "11", "12"), c("lon", "lat")), class = c("XY", 
  "LINESTRING", "sfg")), structure(list(structure(c(-80.19, -66.118, 
  -64.757, -80.19, 26.774, 18.466, 32.321, 26.774), .Dim = c(4L, 
  2L), .Dimnames = list(c("1", "2", "3", "4"), c("lon", "lat"))), 
  structure(c(-70.579, -67.514, -66.668, -70.579, 28.745, 29.57, 
  27.339, 28.745), .Dim = c(4L, 2L), .Dimnames = list(c("5", 
  "6", "7", "8"), c("lon", "lat")))), class = c("XY", "MULTILINESTRING", 
  "sfg")), structure(list(structure(c(-80.19, -66.118, -64.757, 
  -80.19, 26.774, 18.466, 32.321, 26.774), .Dim = c(4L, 2L), .Dimnames = list(
  c("1", "2", "3", "4"), c("lon", "lat"))), structure(c(-70.579, 
  -67.514, -66.668, -70.579, 28.745, 29.57, 27.339, 28.745), .Dim = c(4L, 
  2L), .Dimnames = list(c("5", "6", "7", "8"), c("lon", "lat")))), class = c("XY", 
  "POLYGON", "sfg")), structure(list(list(structure(c(-80.19, -66.118, 
  -64.757, -80.19, 26.774, 18.466, 32.321, 26.774), .Dim = c(4L, 
  2L), .Dimnames = list(c("1", "2", "3", "4"), c("lon", "lat"))), 
  structure(c(-70.579, -67.514, -66.668, -70.579, 28.745, 29.57, 
  27.339, 28.745), .Dim = c(4L, 2L), .Dimnames = list(c("5", 
  "6", "7", "8"), c("lon", "lat")))), list(structure(c(-70, 
  -49, -51, -70, 22, 23, 22, 22), .Dim = c(4L, 2L), .Dimnames = list(
  c("9", "10", "11", "12"), c("lon", "lat"))))), class = c("XY", 
  "MULTIPOLYGON", "sfg"))), precision = 0, bbox = structure(c(xmin = -80.19, 
  ymin = 18.466, xmax = -49, ymax = 32.321), class = "bbox"), crs = structure(list(
  epsg = NA_integer_, proj4string = NA_character_), class = "crs"), n_empty = 0L, classes = c("POINT", 
  "MULTIPOINT", "LINESTRING", "MULTILINESTRING", "POLYGON", "MULTIPOLYGON"
  ), class = c("sfc_GEOMETRY", "sfc"))), row.names = c(NA, 6L), sf_column = "geo", agr = structure(integer(0), class = "factor", .Label = c("constant", 
  "aggregate", "identity"), .Names = character(0)), class = c("sf", "data.frame"))

  expect_error(polyline_wkt(sf),"I was expecting an sfencoded object or an encoded_column")
  
  enc <- encode(sf)
  wkt <- polyline_wkt(enc)
  e <- wkt_polyline(wkt)
  
  expect_true(paste0("sfc_", attr(enc, "sfAttributes")$type ) == class(sf$geo)[1])
  expect_true(paste0("sfc_", attr(e, "sfAttributes")$type ) == class(sf$geo)[1])
  expect_true(all.equal(class(enc), class(e))) 
  expect_true(attr(enc, "encoded_column") == attr(e, "encoded_column"))
  r <- 1
  #expect_true( enc[r, 'geo'][[1]] == e[r, 'geo'][[1]] )
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfg')))
  r <- 2
  #expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfg')))
  r <- 3
  #expect_true(enc[r, 'geo'][[1]] == e[r, 'geo'][[1]])
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfc')))
  r <- 4
  #expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])  
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfc')))
  r <- 5
  #expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfc')))
  r <- 6
  #expect_true(enc[r, 'geo'][[1]][1] == e[r, 'geo'][[1]][1])  
  expect_true(all.equal(attr(enc[r, 'geo'][[1]], 'sfg'), attr(e[r, 'geo'][[1]], 'sfc')))
  
  ## test errors
  expect_error(wkt_polyline(enc),"Can not find the wkt_column")
  expect_error(polyline_wkt(wkt),"Can not find the encoded_column")
  expect_error(wkt_polyline(sf),"I was expecting an sfencoded object with a wkt_column")
})

