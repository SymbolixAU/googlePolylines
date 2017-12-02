# googlePolylines

The goal of sfencode is to encode sf objects using [Google's polyline encoding algorithm](https://developers.google.com/maps/documentation/utilities/polylinealgorithm)

> Polyline encoding is a lossy compression algorithm that allows you to store a series of coordinates as a single string. 

## Installation

You can install sfencode from github with:


```
# install.packages("devtools")
devtools::install_github("SymbolixAU/sfencode")
```

## Examples


## Motivation


```
library(sf)
nc <- st_read(system.file("shape/nc.shp", package="sf"))

nce <- encode(nc, FALSE)
ncest <- encode(nc, TRUE)

vapply(mget(c('nc', 'nce', 'ncest') ), function(x) { format(object.size(x), units = "Kb") }, '')
#         nc        nce      ncest 
# "132.2 Kb"  "83.3 Kb"  "50.5 Kb"
```


