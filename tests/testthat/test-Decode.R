context("decode")

test_that("decode works", {
  
  polylines <- "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A"
  
  lst <- list(
    list(
      lon = c(-80.1899, -66.11799, -64.75700, -80.18999),
      lat = c(26.774, 18.466, 32.321, 26.774)
      )
  )
  
  expect_equal(
    round(decodePolyline(polylines)[[1]]$lon, 3),
    round(lst[[1]]$lon, 3)
  )
  
  expect_equal(
    round(decodePolyline(polylines)[[1]]$lat, 3),
    round(lst[[1]]$lat, 3)
  )
  
})

