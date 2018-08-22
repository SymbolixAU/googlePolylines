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
# pl <- c(0,0,1,1,0,1,1,1,1,0,1,1,0,0,1)
# plz <- sf::st_polygon(x = list(matrix(pl, ncol = 3, byrow = T)))
# pl <- c(0,0,1,2,1,0,1,2,1,1,1,2,0,1,1,2,0,0,1,2)
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
# encode(sflz)
# 
# encode( sf )
# 
# encode(sf)[, 'geometry']
# 
# decode("_seK_ibE")
# 
# mp <- matrix(1:6, ncol = 3)
# mp
# sf <- sf::st_sf(geometry = sf::st_sfc(sf::st_multipoint(x = mp)))
# 
# encode(sf)[, 'geometry']
# 
# decode(c("_}hQ_ibE","_glW_seK","_qo]_}hQ"))
# 
# 
# l <- rbind(c(3.2,4,1), c(3,4.6,3), c(3.8,4.4,2), c(3.5,3.8,5), c(3.4,3.6,3), c(3.9,4.5,1))
# l <- st_linestring(l)
# sf <- sf::st_sf(geometry = sf::st_sfc(l))
# 
# encode(sf)[, 'geometry']
# 
# decode("_eeV__pR~`f@~`f@_xnD_g{C~qjT~qy@_seK~oR~hbE_t`B_}hQ_pR~reK}dtB~reK|`f@")
# 
# ## can there be an sf object which has both an XY and an XYZ element
# 
# sfc1 <- sf::st_sf(geometry = sf::st_sfc(sf::st_linestring(x = matrix(c(1,2,3), ncol = 3))))
# sfc2 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(x = c(1,2))))
# 
# rbind(sfc1, sfc2)
# ## YES
# 
# ## can there be a MULTI object with some with elevation and some without?
# l1 <- sf::st_linestring(x = matrix(c(1,2,3), ncol = 3))
# l2 <- sf::st_linestring(x = matrix(c(1,2), ncol = 2))
# 
# sf::st_multilinestring(x = list(l1, l2))
# ### NO!
# 
# 
# 
