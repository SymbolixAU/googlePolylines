
## decoding
##
## - will return two vectors, lon & lat...



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
# enc <- encode(pts)
# decode(enc)
