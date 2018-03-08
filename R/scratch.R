
## decoding
##
## - will return two vectors, lon & lat...
## - TESTS: encode(sfc) object - do I do this??


# pl <- "umlbDndmhNhvuq@il{tAkcqsAozhGrmz`@~je}A"


## how does it work with data.table

# pls <- c(
#  "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#  "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
# )
# 
# library(data.table)
# 
# dt <- data.table(polyId  = 3:4, polylines = pls)
# 
# dt[, rbindlist(decodePolyline(pls), idcol = T)]
# 
# rbindlist(decodePolyline(pls), idcol = T)
# 
# decodePolyline(polylines)
# 
# 
# myFun <- function(dummy) {
#   return(list(data.frame(let = letters[1:5], val = 1:5), 
#               data.frame(let = letters[6:10], val=6:10))
#          )
# }
# 
# dt <- data.table(foo = c("bar", "baz"))
# 
# ## what should `myFun` return to get a function call likek this to work?
# dt[, myFun(foo) ]
# 
# dt[, rbindlist(myFun(foo), idcol = T)]



# pt1 <- sf::st_point(x = c(-38, 144))
# pt2 <- sf::st_point(x = c(-39, 145))
# pts <- sf::st_sfc(list(pt1, pt2))
# pts <- sf::st_sf(geometry = pts)
# 
# mpt <- sf::st_multipoint(matrix(c(-38, 144, -39, 145), ncol = 2, byrow = T))
# mpts <- sf::st_sf(geometry = sf::st_sfc(mpt))
# 
# lst <- sf::st_linestring(x = matrix(c(-38, 144, -39, 145), ncol = 2, byrow = T))
# lst <- sf::st_sfc(lst)
# lst <- sf::st_sf(geometry = lst)
# 
# sf <- rbind(mpts, pts, lst)
# sfc <- st_geometry(sf)
# str(sfc)
# 
# enc <- encode(mpts)
# d <- decode(enc)
# 
# 
# sf
# sfc
# sfc[[1]]
# sfc[[2]]
# sfc[[3]]
# 
# str(sf)
# str(d)
# 
# attributes(sf)
# attributes(sfc)
# 
# 
# crs <- list(epsg = sfAttributes(enc)[['epsg']],
#             proj4string = sfAttributes(enc)[['proj']])
# attr(crs, "class") <- "crs"
# attr(d[[1]], 'crs') <- crs
# 
# attr(d[[1]], 'bbox') <- sfAttributes(enc)[['bbox']]
# attr(d[[1]], 'precision') <- sfAttributes(enc)[['prec']]
# attr(d[[1]], 'n_empty') <- sfAttributes(enc)[['n_em']]
# 
# attr(d, "agr") <- attr(pts, "agr")
# 
# attr(d, "sf_column") <- 'geometry'
# attr(d, "class") <- c("sf", "data.frame")

## TODO:
## dims - e.g. attributes(sfc[[4]])



# library(sf)
# nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
# 
# encoded <- encode(nc)
# wkt <- polyline_wkt(encoded)
# 
# st_as_sfc(encoded)
# st_as_sfc(wkt)
# 
# st_as_sfc(wkt$geometry)
# st_as_sfc(encoded$geometry)
# 
# st_as_sf(encoded)
# st_as_sf(wkt)
# 
# st_as_sf(encoded$geometry)
# st_as_sf(wkt$geometry)

