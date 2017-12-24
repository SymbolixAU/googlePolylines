
[![Travis-CI Build Status](https://travis-ci.org/SymbolixAU/googlePolylines.svg?branch=master)](https://travis-ci.org/SymbolixAU/googlePolylines)
[![Coverage Status](https://img.shields.io/codecov/c/github/SymbolixAU/googlePolylines/master.svg)](https://codecov.io/github/SymbolixAU/googlePolylines?branch=master)

# googlePolylines

The goal of googlePolylines is to encode and decode objects using [Google's polyline encoding algorithm](https://developers.google.com/maps/documentation/utilities/polylinealgorithm)

> Polyline encoding is a lossy compression algorithm that allows you to store a series of coordinates as a single string. 

## Installation

You can install googlePolylines from github with:


```
# install.packages("devtools")
devtools::install_github("SymbolixAU/googlePolylines")
```



## Examples

Supported `sf` types

- POINT
- MULTIPOINT
- LINESTRING
- MULTILINESTRING
- POLYGON
- MULTIPOLYGON
- GEOMETRY

Unsupported `sf` types

- GEOMETRYCOLLECTION



```
df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
				lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
				lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
				lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))

p1 <- as.matrix(df[1:4, c("lon", "lat")])
p2 <- as.matrix(df[5:8, c("lon", "lat")])
p3 <- as.matrix(df[9:12, c("lon", "lat")])

point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
linestring <- sf::st_sfc(sf::st_linestring(p3))
multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))


sf <- rbind(
	st_sf(geo = polygon),
	st_sf(geo = multilinestring),
	st_sf(geo = linestring),
	st_sf(geo = point),
	st_sf(geo = multipoint)
	)

sf
# Simple feature collection with 5 features and 0 fields
# geometry type:  GEOMETRY
# dimension:      XY
# bbox:           xmin: -80.19 ymin: 18.466 xmax: -49 ymax: 32.321
# epsg (SRID):    NA
# proj4string:    NA
#                              geo
# 1 POLYGON ((-80.19 26.774, -6...
# 2 MULTILINESTRING ((-80.19 26...
# 3 LINESTRING (-70 22, -49 23,...
# 4          POINT (-80.19 26.774)
# 5 MULTIPOINT (-80.19 26.774, ...

encode(sf)
#                                                                           geo
# 1 ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A, ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV
# 2 ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A, ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV
# 3                                           _{geC~zfjL_ibE_qd_C~hbE~reK?~|}rB
# 4                                                                  ohlbDnbmhN
# 5                                                      ohlbDnbmhN, osuoBltprK

```


## Motivation

Encoding coordinates into polylines reduces the size of objects and can increase the speed in plotting Google Maps


```
library(sf)
nc <- st_read(system.file("shape/nc.shp", package="sf"))

encoded <- encode(nc, FALSE)
encodedLite <- encode(nc, TRUE)

vapply(mget(c('nc', 'encoded', 'encodedLite') ), function(x) { format(object.size(x), units = "Kb") }, '')
#         nc   encoded  encodedLite 
# "132.2 Kb"  "83.3 Kb"   "50.5 Kb"
```

```
library(leaflet)
library(microbenchmark)
library(sf)
library(googleway)

nc <- st_read(system.file("shape/nc.shp", package="sf"))

microbenchmark(

  google = {
    df <- encode(nc)

    google_map(key = mapKey) %>%
      add_polygons(data = df, polyline = "geometry")
  },

  leaflet = {
    leaflet(nc) %>%
      addTiles() %>%
      addPolygons()
  },
  times = 25
)

# Unit: milliseconds
#     expr      min        lq     mean    median       uq      max neval
#   google  8.16810  9.164254 10.18863  9.776755 11.50545 13.22828    25
#  leaflet 53.90745 58.151913 61.50368 60.217514 64.08792 74.51588    25
 
```
These benchmarks don't account for the time taken for the browswer to render the maps

