# 
# 
# library(sf)
# 
# ## POINT
# pz <- sf::st_point(c(1,2,3))
# pzm <- sf::st_point(1:4)
# 
# ## MULTIPOINT
# mpz <- sf::st_multipoint(x = matrix(1:6, ncol = 3))
# mpzm <- sf::st_multipoint(x = matrix(1:8, ncol = 4))
# 
# ## LINESTRING
# lz <- sf::st_linestring(x = matrix(1:6, ncol = 3))
# lzm <- sf::st_linestring(x = matrix(1:8, ncol = 4))
# 
# lz2 <- sf::st_linestring(x = matrix(1:15, ncol = 3))
# lzm2 <- sf::st_linestring(x = matrix(1:36, ncol = 4))
# 
# ## MULTILINESTRING
# mlz <- sf::st_multilinestring(x = list(lz,lz))
# mlzm <- sf::st_multilinestring(x = list(lzm, lzm))
# 
# ## POLYGON
# pl <- c(0,0,1,1,0,2,1,1,3,0,1,4,0,0,1)  ## start and end elevation must match
# plz <- sf::st_polygon(x = list(matrix(pl, ncol = 3, byrow = T)))
# pl <- c(0,0,1,2,1,0,1,3,1,1,1,6,0,1,1,9,0,0,1,2)
# plzm <- sf::st_polygon(x = list(matrix(pl, ncol = 4, byrow = T)))
# 
# ## MULTIPOLYGON
# mplz <- sf::st_multipolygon(x = list(plz, plz))
# mplzm <- sf::st_multipolygon(x = list(plzm, plzm))
# 
# ### Regular SF's
# sfpz <- sf::st_sf(geometry = sf::st_sfc(pz))
# sfpzm <- sf::st_sf(geometry = sf::st_sfc(pzm))
# 
# sfmpz <- sf::st_sf(geometry = sf::st_sfc(mpz))
# sfmpzm <- sf::st_sf(geometry = sf::st_sfc(mpzm))
# 
# sflz <- sf::st_sf(geometry = sf::st_sfc(lz))
# sflzm <- sf::st_sf(geometry = sf::st_sfc(lzm))
# 
# sflz2 <- sf::st_sf(geometry = sf::st_sfc(lz2))
# sflzm2 <- sf::st_sf(geometry = sf::st_sfc(lzm2))
# 
# sfmlz <- sf::st_sf(geometry = sf::st_sfc(mlz))
# sfmlzm <- sf::st_sf(geometry = sf::st_sfc(mlzm))
# 
# sfplz <- sf::st_sf(geometry = sf::st_sfc(plz))
# sfplzm <- sf::st_sf(geometry = sf::st_sfc(plzm))
# 
# sfmplz <- sf::st_sf(geometry = sf::st_sfc(mplz))
# sfmplzm <- sf::st_sf(geometry = sf::st_sfc(mplzm))

# 
# ### combinations
# 
# sf <- rbind(sfpz, sfpzm, sfmpz, sfmpzm, sflz, sflzm, sfmlz, sfmlzm, sfplz, sfplzm, sfmplz, sfmplzm)
# 
# sf <- rbind(sfpzm, sfmpz, sfmpzm, sflz, sflzm, sfmlz, sfmlzm, sfplz, sfplzm, sfmplz)
# 
# 
# "XYZM == 4"
# "XYZ == 3"
# "XYM == 3"
# "XY == 2"
# 
# ### LINESTRING ZM -
# 
# 
# ### Encoding POINT Z
# 
# library(googlePolylines)
# ## expecting
# expected <- encodeCoordinates(lon = 1, lat = 2)
# expected
# 
# encode(sfpz)
# encode(sfpzm)
# encode(sfmpz)
# encode(sfmpzm)
# 
# encode(sflz)
# encode(sflz2)
# encode(sflzm2)
# lz2
# 
# tests
# encode( sf::st_zm(sflzm2) )[, 'geometry'][[1]]
# encode( sflzm2 )[, 'geometry'][[1]]
# 
# encode( sfpz )
# encode( sfpzm )
# 
# 
# encode( sfplz )
# encode( sf::st_zm(sfplz) )
# 
# encode( sfplzm )
# encode( sf::st_zm(sfplzm))
