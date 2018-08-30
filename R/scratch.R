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
# sfept <- sf::st_sf(geometry = ept)
# sfpt <- sf::st_sf(geometry = pt)
# 
# emp <- sf::st_sfc(sf::st_multipoint())
# mp <- sf::st_sfc(sf::st_multipoint(matrix(1:4, ncol = 2)))
# 
# sfemp <- sf::st_sf(geometry = emp)
# sfmp <- sf::st_sf(geometry = mp )
# 
# el <- sf::st_sfc(sf::st_linestring())
# l <- sf::st_sfc(sf::st_linestring(matrix(1:4, ncol = 2)))
# 
# sfel <- sf::st_sf(geometry = el )
# sfl <- sf::st_sf(geometry = l )
# 
# eml <- sf::st_sfc(sf::st_multilinestring())
# ml <- sf::st_sfc(sf::st_multilinestring(x = list(matrix(1:4, ncol = 2))))
# 
# sfeml <- sf::st_sf(geometry = eml )
# sfml <- sf::st_sf(geometry = ml )
# 
# epl <- sf::st_sfc(sf::st_polygon())
# pl <- sf::st_sfc(sf::st_polygon(list(x = matrix(c(0,0,1,0,1,1,0,1,0,0), ncol = 2, byrow = T))))
# 
# sfepl <- sf::st_sf(geometry = epl)
# sfpl <- sf::st_sf(geometry = pl)
# 
# empl <- sf::st_sfc(sf::st_multipolygon())
# mpl <- sf::st_sfc(sf::st_multipolygon(x = list(sf::st_polygon(list(x = matrix(c(0,0,1,0,1,1,0,1,0,0), ncol = 2, byrow = T))))))
# 
# sfempl <- sf::st_sf(geometry = empl)
# sfmpl <- sf::st_sf(geometry = mpl)
# 
# 
# 
# encode(ept)
# encode(pt)
# 
# encode(sfept)
# encode(sfpt)
# 
# encode(emp)
# encode(mp)
# 
# encode( sfemp )
# encode( sfmp )
# 
# encode(el)
# encode(l)
# 
# encode( sfel )
# encode( sfl )
# 
# encode(eml)
# encode(ml)
# 
# encode( sfeml )
# encode( sfml )
# 
# encode(epl)
# encode(pl)
# 
# encode( sfepl )
# encode( sfpl )
# 
# encode(empl)
# encode(mpl)
# 
# encode( sfempl )
# encode( sfmpl )
# 
# 
# library(googleway)
# set_key(read.dcf("~/Documents/.googleAPI", fields = "GOOGLE_MAP_KEY"))
# 
# google_map() %>%
#   add_markers(sfemp)
# 
# google_map() %>%
#   add_polylines(data = sfel)
# 
# google_map() %>%
#   add_polylines(data = sfeml)
# 
