context("sfencoded")


test_that("sfencoded converted to data.frame",  {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  x <- as.data.frame(enc)
  expect_true(!"sfencoded" %in% class(x))
  expect_true("data.frame" == class(x))
  
  ## subsetting without including the geom column
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  x <- enc[, c("AREA", "PERIMETER")]
  expect_true(class(x) == "data.frame")
})

test_that("subsetting retains all class attributes", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  expect_true(all(attr(enc, 'class') == attr(enc[1, ], 'class')))

})

test_that("sfencoded attributes are removed", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  x <- googlePolylines:::removeSfencodedClass(enc)
  expect_true(!"sfencoded" %in% attr(x, "class"))
  x <- googlePolylines:::removeSfEncodedAttributes(enc)
  expect_true(sum(c("encoded_column", "sfAttributes") %in% names(attributes(x))) == 0)
  wkt <- polyline_wkt(enc)
  x <- googlePolylines:::removeSfencodedClass(wkt)
  expect_true(!"sfencoded" %in% attr(x, "class"))
  x <- googlePolylines:::removeSfEncodedAttributes(wkt)
  expect_true(sum(c("encoded_column", "sfAttributes") %in% names(attributes(x))) == 0)
})

test_that("zm attributes are removed", {
  
  testthat::skip_on_cran()
  library(sf)
  
  z <- 1:21
  zm <- 1:36
  pz <- sf::st_point(c(1,2,3))
  pzm <- sf::st_point(1:4)
  sf1 <- sf::st_sf(geometry = sf::st_sfc(pz))
  sf2 <- sf::st_sf(geometry = sf::st_sfc(pzm))
  sf <- rbind(sf1, sf2)
  enc <- encode(sf)
  
  x <- googlePolylines:::removeSfEncodedAttributes(enc)
  expect_true(sum(c("zm_column", "sfAttributes") %in% names(attributes(x))) == 0)
  
  df <- as.data.frame(x)
  # expect_null(attributes(df[, 'geometryZM']))
  
})

test_that("correct structure is printed", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  
  ## not sure these tests do anything...
  expect_true(is.atomic(str( enc[1, 'geometry'][[1]] )))
  expect_output(str( enc ))
})


test_that("encoded attribute is attached", {
  df <- data.frame(polyline = "abc")
  df <- googlePolylines:::attachEncodedAttribute(df, 'polyline', 'encoded_column')
  expect_true(attr(df, 'encoded_column') == 'polyline')
})

test_that("encoded objects printed", {
  
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  attr(enc, 'encoded_column') <- 'polyline'
  
  expect_true(inherits(withVisible(enc)$value, "sfencoded"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencodedLite(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame"))
  
  ## WKT attribute
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  attr(enc, 'wkt_column') <- 'polyline'

  expect_true(inherits(withVisible(enc)$value, "sfencoded"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencodedLite(enc))$value, "data.frame"))
  expect_true(inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame"))
  
  ## NO attribute column
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  expect_output(print(enc))
})

test_that("prefix printed", {
  
  testthat::skip_on_cran()
  library(sf)
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  encl <- encode(nc, strip = TRUE)
  expect_true(substr(googlePolylines:::printSfEncodedPrefix(enc[1, 'geometry'], 'sfencoded'), 1, 13) == "MULTIPOLYGON:")
  expect_true(substr(googlePolylines:::printSfEncodedPrefix(encl[1, 'geometry'], 'sfencodedLite'), 1, 5) == "u_d|E")
})


test_that("subsetting rows and columns works", {
  
  testthat::skip_on_cran()
  library(sf)
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  encl <- encode(nc, strip = T)
  expect_true(ncol(enc[1:5, ]) == ncol(enc))
  expect_true(ncol(enc[1:5, c("AREA","PERIMETER")]) == 2)
  expect_true(ncol(as.data.frame(enc[1:5, c("AREA","PERIMETER")])) == 2)
  expect_true(ncol(encl[1:5, ]) == ncol(enc))
  expect_true(ncol(encl[1:5, c("AREA","PERIMETER")]) == 2)
  expect_true(ncol(as.data.frame(encl[1:5, c("AREA","PERIMETER")])) == 2)
  
  ## elevation (zm) attributes
  sf <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(1:3)))
  sf$id <- 1
  enc <- encode( sf )
  
  ## subsetting removing the elevation
  # expect_true(!"geometryZM" %in% names(enc[1, c("geometry", "id")]))
  ## subsetting keeping the elvation
  # expect_true(all(c("id", "geometryZM") %in% names(enc[1, c("id", "geometryZM")])))
  
})


