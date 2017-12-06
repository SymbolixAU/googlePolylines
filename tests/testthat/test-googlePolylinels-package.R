context("package")


test_that("sf-encoded object structure prints correctly", {
  
  sf <- sf::st_sf(line = sf::st_sfc(sf::st_linestring(matrix(c(144, 144.1, 144.2, -37, -37.1, -37.2), ncol = 2))))
  encoded <- encode(sf)
  
  s <- evaluate_promise(str(encoded))
  
  expect_true(
    grepl("encoded_column of length 1", s$output)
  )
  
})

