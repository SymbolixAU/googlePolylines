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

