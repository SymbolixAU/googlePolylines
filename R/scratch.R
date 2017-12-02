
### ---------------------------------------------
### data.table
# library(data.table)
# df <- data.table(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
#                  lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
#                  lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
#                  lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
# 
# 
# encode(df)
# df[, encode(lon = lon, lat = lat), by = myId]


### ---------------------------------------------
### MULTI*
### nested list of lists

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
# multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
# multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))

# encode(multipolygon)

# library(googleway)
# mapKey <- read.dcf("~/Documents/.googleAPI", field = "GOOGLE_MAP_KEY")
# 
# sf <- sf::st_sf(geometry = multipolygon)
# df <- encode(sf)
# 
# google_map(key = mapKey) %>%
#   add_polygons(df, polyline = "geometry")

# encode(multilinestring)
# sf <- sf::st_sf(line = multilinestring)
# df <- encode(sf)
#
# library(googleway)
# google_map(key = mapKey) %>%
#  add_polygons(df, polyline = "line")
# 
# decode_pl(df$line[[1]][2])

# 
# 
# m <- melbourne[1:5,]
# m <- aggregate(polyline ~ polygonId, data = m, list)
# 
# google_map(key = mapKey) %>%
#   add_polylines(m, polyline = "polyline", stroke_colour = "polygonId")
# 
# google_map(key = mapKey) %>%
#   add_polygons(m, polyline = "polyline", fill_colour = "polygonId")

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
# library(sf)
# library(sfencode)
# nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
# 
# nce <- encode(nc, FALSE)
# ncest <- encode(nc, TRUE)
# 
# vapply(mget(c('nc', 'nce', 'ncest') ), function(x) { format(object.size(x), units = "Kb") }, '')
# #         nc        nce      ncest 
# # "132.2 Kb"  "82.9 Kb"  "50.1 Kb"

# df <- encode(nc)
# 
# ## if sfencoded; get the encoded column
# polyline <- attr(nce, 'encoded_column')
# attr(df, 'encoded_column') <- NULL
# 
# library(googleway)
# mapKey <- read.dcf("~/Documents/.googleAPI", field = "GOOGLE_MAP_KEY")


# attr(df, 'encoded_column') <- NULL
# str(df)
# 
# attr(df[['geometry']], 'class') <- 'character'
# 

# library(leaflet)
# library(microbenchmark)
# 
# microbenchmark(
#   
#   google = { 
#     df <- encode(nc)
#     attr(df, 'encoded_column') <- NULL
#     
# google_map(key = mapKey) %>%
#   add_polygons(data = df, polyline = "geometry")
#   },
#   
#   leaflet = {
#     leaflet(nc) %>%
#       addTiles() %>%
#       addPolygons() 
#   },
#   times = 25
# )

