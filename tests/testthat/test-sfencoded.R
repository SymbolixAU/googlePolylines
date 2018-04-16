context("sfencoded")


test_that("sfencoded converted to data.frame",  {
  
  testthat::skip_on_cran()
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  x <- as.data.frame(enc)
  
  expect_true(
    !"sfencoded" %in% class(x)
  )
  
  expect_true(
    "data.frame" == class(x)
  )
  
  ## subsetting without including the geom column
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  
  x <- enc[, c("AREA", "PERIMETER")]
  
  expect_true(
    class(x) == "data.frame"
  )
  
})

test_that("sfencoded attributes are removed", {
  
  testthat::skip_on_cran()
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  x <- googlePolylines:::removeSfencodedClass(enc)
  
  expect_true(
    !"sfencoded" %in% attr(x, "class")
  )
  
  x <- googlePolylines:::removeSfEncodedAttributes(enc)
  
  expect_true(
    sum(c("encoded_column", "sfAttributes") %in% names(attributes(x))) == 0
  )
  
  

  wkt <- polyline_wkt(enc)
  x <- googlePolylines:::removeSfencodedClass(wkt)
  
  expect_true(
    !"sfencoded" %in% attr(x, "class")
  )
  
  x <- googlePolylines:::removeSfEncodedAttributes(wkt)
  
  expect_true(
    sum(c("encoded_column", "sfAttributes") %in% names(attributes(x))) == 0
  )
  
    
})

test_that("correct structure is printed", {
  
  testthat::skip_on_cran()
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)
  
  ## not sure these tests do anything...
  expect_true(
    is.atomic(str( enc[1, 'geometry'][[1]] ))
  )
  
  expect_output(
    str( enc )
  )
  
})


test_that("encoded attribute is attached", {
  
  testthat::skip_on_cran()
  
  df <- data.frame(polyline = "abc")
  
  df <- googlePolylines:::attachEncodedAttribute(df, 'polyline', 'encoded_column')
  
  expect_true(
    attr(df, 'encoded_column') == 'polyline'
  )
  
})

test_that("encoed objects printed", {
  
  testthat::skip_on_cran()
    
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  attr(enc, 'encoded_column') <- 'polyline'
  
  expect_true(
    inherits(withVisible(enc)$value, "sfencoded")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencodedLite(enc))$value, "data.frame")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame")
  )
  
  ## WKT attribute
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  attr(enc, 'wkt_column') <- 'polyline'
  
  
  expect_true(
    inherits(withVisible(enc)$value, "sfencoded")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencodedLite(enc))$value, "data.frame")
  )
  
  expect_true(
    inherits(withVisible(googlePolylines:::print.sfencoded(enc))$value, "data.frame")
  )
  
  ## NO attribute column
  enc <- data.frame(polyline = "abc", stringsAsFactors = F)
  attr(enc, 'class') <- c('sfencoded', class(enc))
  
  expect_output(
    print(enc)
  )
  
})

test_that("prefix printed", {
  
  testthat::skip_on_cran()
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"), quiet = T)
  enc <- encode(nc)

  expect_true(
    substr(googlePolylines:::printSfEncodedPrefix(enc[1, 'geometry'], 'sfencoded'), 1, 13) == "MULTIPOLYGON:"
  )
  
  enc <- encode(nc, strip = TRUE)
  
  expect_true(
    substr(googlePolylines:::printSfEncodedPrefix(enc[1, 'geometry'], 'sfencodedLite'), 1, 5) == "u_d|E"
  )
  
})



