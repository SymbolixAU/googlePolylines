
# library(sf)
# 
# pl1 <- c(0,0,1,0,1,1,0,1,0,0)  ## start and end elevation must match
# pl1 <- sf::st_polygon(x = list(matrix(pl1, ncol = 2, byrow = T)))
# pl2 <- c(0,0,-1,0,-1,-1,0,-1,0,0)
# pl2 <- sf::st_polygon(x = list(matrix(pl2, ncol = 2, byrow = T)))
# 
# ## MULTIPOLYGON
# sf <- sf::st_sf(geometry = sf::st_sfc(sf::st_multipolygon(x = list(pl1, pl2))))
# 
# enc <- encode( sf )
# 
# enc$geometry[[1]]


### Benchmarks

# library(microbenchmark)
# 
# microbenchmark(
#   r = { googlePolylines:::geometryRow.sfencoded( e, "POLYGON", multi = T) },
#   rcpp = { googlePolylines:::rcpp_get_geometry_types( e$geometry, "MULTIPOLYGON") },
#   rcpp_mult = { googlePolylines:::rcpp_get_geometry_types_multi( e$geometry, "POLYGON", "MULTIPOLYGON") }
# )

# Unit: microseconds
#      expr     min       lq      mean   median       uq      max neval
#         r 482.355 493.4985 603.21041 505.5890 555.5125 2831.437   100
#      rcpp  44.740  46.9655  65.92212  49.3310  57.4835  487.616   100
# rcpp_mult  46.289  48.6280  59.73938  51.6655  57.9990  304.934   100


