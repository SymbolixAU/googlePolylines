# 
# 
# 
# library(sf)
# 
# str( sf::st_sfc( sf::st_point() ) )
# str( sf::st_sfc( sf::st_multipoint() ) )
# 
# str( sf::st_sfc( sf::st_linestring() ) )
# str( sf::st_sfc( sf::st_multilinestring() ) )
# 
# str( sf::st_sfc( sf::st_polygon() ) )
# str( sf::st_sfc( sf::st_multipolygon() ) )
# 
# pt <- sf::st_sfc( sf::st_point() )
# mpt <- sf::st_sfc( sf::st_multipoint())
# 
# attributes(pt)
# attributes(mpt)
# 
# pt[[1]][1]
# mpt[[1]][1]
# 
# ept <- sf::st_sfc(sf::st_point())
# pt <- sf::st_sfc(sf::st_point(c(1,1)))
# 
# emp <- sf::st_sfc(sf::st_multipoint())
# mp <- sf::st_sfc(sf::st_multipoint(matrix(1:4, ncol = 2)))
# 
# el <- sf::st_sfc(sf::st_linestring())
# l <- sf::st_sfc(sf::st_linestring(matrix(1:4, ncol = 2)))
# 
# eml <- sf::st_sfc(sf::st_multilinestring())
# ml <- sf::st_sfc(sf::st_multilinestring(x = list(matrix(1:4, ncol = 2))))
# 
# epl <- sf::st_sfc(sf::st_polygon())
# pl <- sf::st_sfc(sf::st_multipolygon(x = list(sf::st_polygon(list(x = matrix(c(0,0,1,0,1,1,0,1,0,0), ncol = 2, byrow = T))))))
# 
# encode(ept)
# encode(pt)
# encode(emp)
# encode(mp)
# encode(el)
# encode(l)
# encode(eml)
# encode(ml)
# encode(epl)
# encode(pl)
# 
