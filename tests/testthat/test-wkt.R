context("wkt")

test_that("wkt converted back to encoded_column", {

  df <- data.frame(
    x = 1:10
    , y = 10:1
  )

  sf <- sfheaders::sf_point(
    obj = df
  )
  
  expect_error(polyline_wkt(sf),"I was expecting an sfencoded object or an encoded_column")
  
  enc <- encode(sf)
  wkt <- polyline_wkt(enc)
  e <- wkt_polyline(wkt)
  
  expect_true(paste0("sfc_", attr(enc, "sfAttributes")$type ) == class(sf$geometry)[1])
  expect_true(paste0("sfc_", attr(e, "sfAttributes")$type ) == class(sf$geometry)[1])
  expect_true(all.equal(class(enc), class(e))) 
  expect_true(attr(enc, "encoded_column") == attr(e, "encoded_column"))
  r <- 1
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  r <- 2
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  r <- 3
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  r <- 4
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  r <- 5
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  r <- 6
  expect_true(all.equal(attr(enc[r, 'geometry'][[1]], 'sfc'), attr(e[r, 'geometry'][[1]], 'sfc')))
  
  ## test errors
  expect_error(wkt_polyline(enc),"Can not find the wkt_column")
  expect_error(polyline_wkt(wkt),"Can not find the encoded_column")
  expect_error(wkt_polyline(sf),"I was expecting an sfencoded object with a wkt_column")
})

