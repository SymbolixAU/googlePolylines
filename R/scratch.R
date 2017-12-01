# 
# 
# library(sf)
# 
# df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
# 								 lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
# 								 lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
# 								 lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
# 
# p1 <- as.matrix(df[1:4, c("lon", "lat")])
# p2 <- as.matrix(df[5:8, c("lon", "lat")])
# p3 <- as.matrix(df[9:12, c("lon", "lat")])
# 
# point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
# # multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
# polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
# linestring <- sf::st_sfc(sf::st_linestring(p3))
# multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p3, p3)))
# 
# 
# sf <- rbind(
# 	st_sf(geo = polygon),
# 	st_sf(geo = multilinestring),
# 	st_sf(geo = linestring),
# 	st_sf(geo = point)
# 	)
# 
# sfe <- sfencode::encodeSf(sf)
# 
# 
# library(googleway)
# mapKey <- read.dcf("~/Documents/.googleAPI", field = "GOOGLE_MAP_KEY")
# 
# ## polygons
# idx <- vapply(sfe[['attributes']], function(x) { "POLYGON" %in% x || "MULTIPOLYGON" %in% x }, FUN.VALUE = T)
# 
# google_map(key = mapKey) %>%
#   add_polygons(sfe[idx,], polyline = "geo")
# 
# ## lines
# idx <- vapply(sfe[['attributes']], function(x) { "LINESTRING" %in% x || "MULTILINESTRING" %in% x }, FUN.VALUE = T)
# 
# google_map(key = mapKey) %>%
#   add_polylines(sfe[idx,], polyline = "geo")

# library(sf)
# nc <- st_read(system.file("shape/nc.shp", package="sf"))
# 
# nce <- encode(n)


## Attributes
# sf <- nc
# attr(sf, 'class') <- "data.frame"
# 
# sf
# 
# sf1 <- sf[1,]
# 
# nce1 <- nce[1,]
# 
# 
# attr(nce[1, 'geometry'], 'sfc')


# library(spatialdatatable)
# library(microbenchmark)
# 
# microbenchmark(
#   sdt = { spatialdatatable::EncodeSF(nc) },
#   esf = { sfencode::encodeSf(nc) },
#   times = 5
# )

# mapKey <- read.dcf("~/Documents/.googleAPI", field = "GOOGLE_MAP_KEY")
# 
# google_map(key = mapKey) %>%
#   add_polygons(data = nce, polyline = "geometry")
