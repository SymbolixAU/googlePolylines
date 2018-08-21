
# 
# library(sf)
# 
# sf <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1,2,3))))
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
# 
# 
# 
