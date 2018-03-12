## ------------------------------------------------------------------------
library(googlePolylines)

lon <- c(144.9709, 144.9713, 144.9715, 144.9719, 144.9728, 144.9732, 
144.973, 144.9727, 144.9731, 144.9749, 144.9742)

lat <- c(-37.8075, -37.8076, -37.8076, -37.8078, -37.8079, -37.8079, 
-37.8091, -37.8107, -37.8115, -37.8153, -37.8155)

encodeCoordinates(lon, lat)


## ------------------------------------------------------------------------

df <- data.frame(
  lon = c(144.9709, 144.9713, 144.9715, 144.9719, 144.9728, 144.9732, 144.973, 144.9727, 144.9731, 144.9749, 144.9742),
  lat = c(-37.8075, -37.8076, -37.8076, -37.8078, -37.8079, -37.8079, -37.8091, -37.8107, -37.8115, -37.8153, -37.8155)
  )

encode(df)

## or specify the columns to use
# encode(df, lon = "lon", lat = "lat")


## ------------------------------------------------------------------------

library(sf)

## data set of North Carolina states
nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
nc[1:5,]


## ------------------------------------------------------------------------
enc <- encode(nc)
str(enc)

attr(enc, "encoded_column")

enc[1, attr(enc, "encoded_column")]


## ------------------------------------------------------------------------
encLite <- encode(nc, strip = T)
str(encLite)

encLite[1, attr(encLite, "encoded_column")]


## ------------------------------------------------------------------------
vapply(mget(c('nc', 'enc', 'encLite') ), function(x) { format(object.size(x), units = "Kb") }, '')


## ------------------------------------------------------------------------

wkt <- polyline_wkt(enc)
wkt[1, ]


## ------------------------------------------------------------------------
enc2 <- wkt_polyline(wkt)
enc2[1, ]


## ------------------------------------------------------------------------

# sfc from wkt
st_as_sfc(wkt$geometry)

## back to sf - use `as.data.frame` to remove sfencoded attributes
sf_wkt <- as.data.frame(wkt)
sf_wkt$geometry <- st_as_sfc(sf_wkt$geometry)
sf_wkt <- st_sf(sf_wkt)
  
head(sf_wkt[, c("AREA", "PERIMETER", "geometry")])


## ------------------------------------------------------------------------
polylines <- c(
 "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
 "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
)

decode(polylines)


## ------------------------------------------------------------------------
enc[1, 'geometry'][[1]] == enc2[1, 'geometry'][[1]]

