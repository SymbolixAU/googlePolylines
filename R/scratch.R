
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







