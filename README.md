
[![R build status](https://github.com/SymbolixAU/googlePolylines/workflows/R-CMD-check/badge.svg)](https://github.com/SymbolixAU/googlePolylines/actions)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/googlePolylines)](https://CRAN.R-project.org/package=googlePolylines)
[![Codecov test coverage](https://codecov.io/gh/SymbolixAU/googlePolylines/branch/master/graph/badge.svg)](https://codecov.io/gh/SymbolixAU/googlePolylines?branch=master)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/googlePolylines)


# googlePolylines

A **fast** and light-weight implementation of [Google's polyline encoding algorithm](https://developers.google.com/maps/documentation/utilities/polylinealgorithm). 


> Polyline encoding is a lossy compression algorithm that allows you to store a series of coordinates as a single string. 


## Installation

From CRAN

```r
install.packages("googlePolylines")
```

From github (dev version)

```r
remotes::install_github("SymbolixAU/googlePolylines")
```

## Scope

Because `googlePolylines` uses Google's polyline encoding algorithm, all functions assume Google Web Mercator projection (WSG 84 / EPSG:3857 / EPSG:900913) for inputs and outputs. Objects that use other projections should be re-projected into EPSG:3857 before using these functions.

`googlePolylines` supports Simple Feature objects (from `library(sf)`), `data.frame`s, and vectors of lon/lat coordinates.

Supported `sf` types 

- POINT
- MULTIPOINT
- LINESTRING
- MULTILINESTRING
- POLYGON
- MULTIPOLYGON
- GEOMETRY

## Examples

`googlePolylines` contains functions to encode coordinates into polylines, and also to parse polylines to and from well-known text format.

### `encode`

```r
library(googlePolylines)
library(sf)

# create data

df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
				lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
				lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
				lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))

p1 <- as.matrix(df[1:4, c("lon", "lat")])
p2 <- as.matrix(df[5:8, c("lon", "lat")])
p3 <- as.matrix(df[9:12, c("lon", "lat")])

# create `sf` collections

point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
linestring <- sf::st_sfc(sf::st_linestring(p3))
multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))

# combine all types into one collection

sf <- rbind(
	sf::st_sf(geo = polygon),
	sf::st_sf(geo = multilinestring),
	sf::st_sf(geo = linestring),
	sf::st_sf(geo = point),
	sf::st_sf(geo = multipoint)
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

# encode sf objects

encode(sf)

                                       geo
# 1         POLYGON: ohlbDnbmhN~suq@am{tA...
# 2 MULTILINESTRING: ohlbDnbmhN~suq@am{tA...
# 3      LINESTRING: _{geC~zfjL_ibE_qd_C~...
# 4                     POINT: ohlbDnbmhN...
# 5                MULTIPOINT: ohlbDnbmhN...


# encode data frame as a list of points

encode(df)
# [1] "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}Aw}_Kycty@gc`DesuQvvrLofdDorqGtzzVfkdh@uapB_ibE_qd_C~hbE~reK?~|}rB"


```

### Polyline to well-known text

```r

enc <- encode(sf)
wkt <- polyline_wkt(enc)
wkt
                                                                                                                                       geo
# 1 POLYGON ((-80.19 26.774, -66.1...
# 2 MULTILINESTRING ((-80.19 26.77...
# 3 LINESTRING (-70 22, -49 23, -5...
# 4          POINT (-80.19 26.774)...
# 5 MULTIPOINT ((-80.19 26.774),(-...
```

### Well-known text to polyline

```r
enc2 <- wkt_polyline(wkt)
```


## Motivation

Encoding coordinates into polylines reduces the size of objects and can increase the speed in plotting Google Maps and Mapdeck


```r
library(sf)
library(geojsonsf)
sf <- geojsonsf::geojson_sf("https://raw.githubusercontent.com/SymbolixAU/data/master/geojson/SA1_2016_VIC.json")

encoded <- encode(sf, FALSE)
encodedLite <- encode(sf, TRUE)

vapply(mget(c('sf', 'encoded', 'encodedLite') ), function(x) { format(object.size(x), units = "Kb") }, '')
#           sf      encoded  encodedLite 
# "38750.7 Kb" "14707.9 Kb"  "9649.8 Kb"
```

```r
library(microbenchmark)
library(sf)
library(geojsonsf)
library(leaflet)
library(googleway)
library(mapdeck)

sf <- geojsonsf::geojson_sf("https://raw.githubusercontent.com/SymbolixAU/data/master/geojson/SA1_2016_VIC.json")

microbenchmark(

  google = {

    ## you need a Google Map API key to use this function
    google_map(key = mapKey) %>%
      add_polygons(data = sf)
  },
  
  mapdeck = {
    mapdeck(token = mapKey) %>%
      add_polygon(data = sf)
  },

  leaflet = {
    leaflet(sf) %>%
      addTiles() %>%
      addPolygons()
  },
  times = 25
)

# Unit: milliseconds
#     expr       min        lq      mean    median        uq       max neval
#   google  530.4193  578.3035  644.9472  606.3328  726.4577  897.9064    25
#  mapdeck  527.7255  577.2322  628.5800  600.7449  682.2697  792.8950    25
#  leaflet 3247.3318 3445.6265 3554.7433 3521.6720 3654.1177 4109.6708    25
 
```
These benchmarks don't account for the time taken for the browswer to render the maps

