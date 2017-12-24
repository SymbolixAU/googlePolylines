context("sfattributes")


test_that("sf attributes extracted", {
  
  nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
  
  sfAttrs <- googlePolylines:::sfGeometryAttributes(nc)
  
  expect_equal(
    sfAttrs$type,
    "MULTIPOLYGON"
  )
  
  expect_equal(
    sfAttrs$dim,
    "XY"
  )
  
  expect_equal(
    round(sfAttrs$bbox[[1]],3),
    -84.324
  )
  
  expect_equal(
    round(sfAttrs$bbox[[2]], 3),
    33.882
  )
  
  expect_equal(
    round(sfAttrs$bbox[[3]],3),
    -75.457
  )
  
  expect_equal(
    round(sfAttrs$bbox[[4]],3),
    36.59
  )
  
  expect_equal(
    sfAttrs$epsg,
    4267
  )
  
  expect_equal(
    sfAttrs$proj,
    "+proj=longlat +datum=NAD27 +no_defs"
  )
  
})

