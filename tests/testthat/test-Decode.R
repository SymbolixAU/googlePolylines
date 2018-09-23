context("decode")

test_that("decode works", {
  polylines <- "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A"
  lst <- list(
    list(
      lon = c(-80.1899, -66.11799, -64.75700, -80.18999),
      lat = c(26.774, 18.466, 32.321, 26.774)
      )
  )
  expect_equal(round(decode(polylines)[[1]]$lon, 3),round(lst[[1]]$lon, 3))
  expect_equal(round(decode(polylines)[[1]]$lat, 3),round(lst[[1]]$lat, 3))
  expect_error(decode(data.frame()),"I don't know how to decode this object")
})

test_that("NA inputs handled properly", {
  expect_equal(decode(NA_character_), 
               list(data.frame("lat" = NA_real_, "lon" = NA_real_)))
})


# test_that("decoding ZM columns", {
#   
#   ## the correct Z and M columns are returned
#   testthat::skip_on_cran()
#   library(sf)
#   
#   z <- 1:21
#   zm <- 1:36
#   
#   ## POINT
#   pz <- sf::st_point(c(1,2,3))
#   pzm <- sf::st_point(1:4)
#   
#   ## MULTIPOINT
#   mpz <- sf::st_multipoint(x = matrix(z, ncol = 3))
#   mpzm <- sf::st_multipoint(x = matrix(zm, ncol = 4))
#   
#   ## LINESTRING
#   lz <- sf::st_linestring(x = matrix(z, ncol = 3))
#   lzm <- sf::st_linestring(x = matrix(zm, ncol = 4))
#   
#   sfcpz <- sf::st_sfc(pz)
#   sfpz <- sf::st_sf(geometry = sfcpz)
#   sfcpzm <- sf::st_sfc(pzm)
#   sfpzm <- sf::st_sf(geometry = sfcpzm)
#   
#   sfcmpz <- sf::st_sfc(mpz)
#   sfmpz <- sf::st_sf(geometry = sfcmpz)
#   
#   sfcmpzm <- sf::st_sfc(mpzm)
#   sfmpzm <- sf::st_sf(geometry = sfcmpzm)
#   
#   sfclz <- sf::st_sfc(lz)
#   sflz <- sf::st_sf(geometry = sfclz)
#   sfclzm <- sf::st_sfc(lzm)
#   sflzm <- sf::st_sf(geometry = sfclzm)
#   
#   sf <- rbind(sfpz, sfpzm, sfmpz, sfmpzm, sflz, sflzm)
#   enc <- encode( sf )
#   
#   ## 1: Z
#   ## 2: ZM
#   ## 3: Z
#   ## 4: ZM
#   ## 5: Z
#   ## 6: ZM
#   
#   dec <- decode( enc$geometryZM )
#   expect_true( dec[[1]][[1]][['M']] == 0 )
#   expect_true( dec[[2]][[1]][['Z']] == sf[2, ][[1]][[1]][3] )
#   expect_true( dec[[2]][[1]][['M']] == sf[2, ][[1]][[1]][[4]] )
#   expect_true( all( sapply( dec[[3]], function(x) x[['M']] ) == 0 ))
#   expect_true( all( sapply( dec[[4]], function(x) x[["Z"]] ) == 19:27 ))
#   expect_true( all( sapply( dec[[4]], function(x) x[["M"]] ) == 28:36 ))
#   expect_true( all( dec[[5]][[1]][['Z']] == 15:21 ))
#   expect_true( all( dec[[5]][[1]][['M']] == 0))
#   expect_true( all( sapply( dec[[6]], function(x) x[["Z"]] ) == 19:27 ))
#   expect_true( all( sapply( dec[[6]], function(x) x[["M"]] ) == 28:36 ))
#   
# })
