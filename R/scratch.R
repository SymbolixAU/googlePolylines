
## TODO:
## - geometry collection
## - multiple geometry columns
## - print method for encoded geo columns




### DECODE
## data.table
# library(data.table)
# polylines <- c(
#   "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#   "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
# )
# 
# decodePolyline(polylines)
#  
# dt <- data.table(polyline = polylines)
# 
# dt[, c("lon", "lat") := decodePolyline(polyline)]

### GEOMETRYCOLLECTION
# p <- rbind(c(3.2,4), c(3,4.6), c(3.8,4.4), c(3.5,3.8), c(3.4,3.6), c(3.9,4.5))
# (mp <- st_multipoint(p))
# 
# s1 <- rbind(c(0,3),c(0,4),c(1,5),c(2,5))
# (ls <- st_linestring(s1))
# 
# s2 <- rbind(c(0.2,3), c(0.2,4), c(1,4.8), c(2,4.8))
# s3 <- rbind(c(0,4.4), c(0.6,5))
# (mls <- st_multilinestring(list(s1,s2,s3)))
# 
# p1 <- rbind(c(0,0), c(1,0), c(3,2), c(2,4), c(1,4), c(0,0))
# p2 <- rbind(c(1,1), c(1,2), c(2,2), c(1,1))
# pol <-st_polygon(list(p1,p2))
# p3 <- rbind(c(3,0), c(4,0), c(4,1), c(3,1), c(3,0))
# p4 <- rbind(c(3.3,0.3), c(3.8,0.3), c(3.8,0.8), c(3.3,0.8), c(3.3,0.3))[5:1,]
# p5 <- rbind(c(3,3), c(4,2), c(4,3), c(3,3))
# (mpol <- st_multipolygon(list(list(p1,p2), list(p3,p4), list(p5))))
# 
# (gc <- st_geometrycollection(list(mp, mpol, ls)))
# 
# sf <- sf::st_sf(geo = sf::st_sfc(gc))

# encode(sf)


## Encoding a geometry collection:
## - one row per collection of geometries
## - 





## MultipPoints
# library(sf)
# 
# pts = matrix(1:10, , 2)
# mp1 = st_multipoint(pts)
# mp1 = sf::st_sfc(mp1)
# encode(mp1)
# sf <- sf::st_sf(mp1)
# encode(sf)

# pt <- matrix(c(1,2), ncol = 2)
# 
# mp1 <- st_multipoint(pt)
# mp1 <- sf::st_sfc(mp1)
# encode(mp1)

# pt <- matrix(c(1,2), ncol = 2)
# 
# mp1 <- sf::st_point(pt)
# mp1 <- sf::st_sfc(mp1)
# encode(mp1)


### ---------------------------------------------
### data.table
# library(data.table)
# df <- data.table(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
#                  lineId = c(1,1,1,1,2,2,2,2,1,1,1,1),
#                  lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
#                  lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
# 
# 
# encode(df)
# df[, encode(lon = lon, lat = lat), by = .(myId, lineId)]
# 
# df %>%
#   group_by(myId, lineId) %>%
#   summarise(polyline = encode(lon, lat))


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
# multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
# polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
# linestring <- sf::st_sfc(sf::st_linestring(p3))
# multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
# multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))
# 
# sf <- rbind(
# 	st_sf(geo = polygon),
# 	st_sf(geo = multilinestring),
# 	st_sf(geo = linestring),
# 	st_sf(geo = point)
# 	)
# 
# encode(sf)
# 
# enc <- encode(sf)




### SELECTING SPECIFIC TYPES
# library(googleway)
# mapKey <- read.dcf("~/Documents/.googleAPI", field = "GOOGLE_MAP_KEY")
# 
# encoded <- encode(sf[1:3,])
# 
# encoded[getPolygons(encoded), ]
# 
# encode(sf[4,])
#encode(sf)

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

