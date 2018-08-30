#' sf Attributes
#' 
#' Retrieves the sf attributes stored on the \code{sfencoded} object
#' 
#' @param x \code{sfencoded} object
#' 
#' @return \code{list} of \code{sf} attributes
#' 
#' @export
sfAttributes <- function(x) UseMethod("sfAttributes")

#' @export
sfAttributes.sfencoded <- function(x) attr(x, "sfAttributes")

### SF ATTRIBUTES
sfGeometryAttributes <- function(sf) UseMethod("sfGeometryAttributes")

#' @export
sfGeometryAttributes.sf <- function(sf) sfGeometryAttributes(sf[[sfGeometryColumn(sf)]])

#' @export
sfGeometryAttributes.sfc <- function(sfc) {
  
  list(
    type = sfGeometryType(sfc),
    dim  = sfDimension(sfc),
    bbox = sfBbox(sfc),
    epsg = sfEpsg(sfc),
    proj = sfProj(sfc),
    prec = sfPrecision(sfc),
    n_em = sfNEmpty(sfc)
  )
}

### GEOMETRY COLUMN
sfGeometryColumn <- function(sf) UseMethod("sfGeometryColumn")

#' @export
sfGeometryColumn.sf <- function(sf) attr(sf, "sf_column")

### GEOMETRY TYPE
sfGeometryType <- function(sf) UseMethod("sfGeometryType")

#' @export
sfGeometryType.sfc <- function(sfc) substr(class(sfc)[1], 5, nchar(class(sfc)[1]))

### DIMENSION
sfDimension <- function(sf) UseMethod("sfDimension")

#' @export
sfDimension.sfc <- function(sfc) class(sfc[[1]])[1]

### BBOX
sfBbox <- function(sf) UseMethod("sfBbox")

sfBbox.sfc <- function(sfc) attr(sfc, "bbox")

### EPSG
sfEpsg <- function(sf) UseMethod("sfEpsg") 

#' @export
sfEpsg.sfc <- function(sfc) attr(sfc, "crs")$epsg

### PROJ4STRINg
sfProj <- function(sf) UseMethod("sfProj")

#' @export
sfProj.sfc <- function(sfc) attr(sfc, "crs")$proj4string

### PRECISION
sfPrecision <- function(sf) UseMethod("sfPrecision")

#' @export
sfPrecision.sfc <- function(sfc) attr(sfc, "precision")

### N_EMPTY
sfNEmpty <- function(sf) UseMethod("sfNEmpty")

#' @export
sfNEmpty.sfc <- function(sfc) attr(sfc, "n_empty")


#' Geometry Row
#' 
#' Extracts specific geometry rows of an \code{sfencoded} object
#' 
#' @param x \code{sfencoded} object
#' @param geometry the specific geometry to extract
#' @param multi logical indicating if MULTI geometry objects are included
#' 
#' @return the row indeces for the requested geometry
#' 
#' @examples 
#' \dontrun{
#' 
#'df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
#' 	lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
#' 	lon = c(-80.190,-66.118,-64.757,-80.190,-70.579,-67.514,-66.668,-70.579,-70,-49,-51,-70),
#' 	lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
#' 
#' p1 <- as.matrix(df[1:4, c("lon", "lat")])
#' p2 <- as.matrix(df[5:8, c("lon", "lat")])
#' p3 <- as.matrix(df[9:12, c("lon", "lat")])
#' 
#' point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
#' multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
#' polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
#' linestring <- sf::st_sfc(sf::st_linestring(p3))
#' multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
#' multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))
#' 
#' sf <- rbind(
#' 	st_sf(geo = polygon),
#' 	st_sf(geo = multilinestring),
#' 	st_sf(geo = linestring),
#' 	st_sf(geo = point)
#' 	)
#' 
#' encode(sf)
#' 
#' enc <- encode(sf)
#' geometryRow(enc, "POINT")
#' geometryRow(enc, "LINESTRING")
#' geometryRow(enc, "POLYGON")
#' 
#' }
#' 
#' @export
geometryRow <- function(x, geometry = c("POINT", "LINESTRING", "POLYGON"), multi = TRUE) {
  geometry <- match.arg(geometry)
  UseMethod("geometryRow")
}

#' @export
geometryRow.sfencoded <- function(x, geometry, multi = TRUE) {
  encodedColumnType(x, ifelse(multi, paste0("*", geometry), paste0("^",geometry,"$")))
}

#' @export
geometryRow.default <- function(x, ... ){
  stop("This function should be called on an sfencoded object")
}

encodedColumnType <- function(encoded, type) which(grepl(type, encodedColumnTypes(encoded)))

encodedColumn <- function(encoded) encoded[[attr(encoded, 'encoded_column')]]

encodedColumnTypes <- function(encoded) vapply(encodedColumn(encoded), function(x) { attr(x, 'sfc')[2] }, '' )



