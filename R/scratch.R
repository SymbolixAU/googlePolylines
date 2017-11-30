

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
# sfencode:::encodeGeometry(st_geometry(sf))

# library(sf)
# nc <- st_read(system.file("shape/nc.shp", package="sf"))
# 
# nce <- encodeSf(nc)

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


# pl_outer <- encode_pl(lat = c(25.774, 18.466,32.321),
#                       lon = c(-80.190, -66.118, -64.757))
# 
# pl_inner <- encode_pl(lat = c(28.745, 29.570, 27.339),
#                       lon = c(-70.579, -67.514, -66.668))
# 
# df <- data.frame(id = c(1, 1),
#                  polyline = c(pl_outer, pl_inner),
#                  stringsAsFactors = FALSE)
# 
# df <- aggregate(polyline ~ id, data = df, list)