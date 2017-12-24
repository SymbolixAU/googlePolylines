### SF ATTRIBUTES
sfGeometryAttributes <- function(sf) UseMethod("sfGeometryAttributes")

#' @export
sfGeometryAttributes.sf <- function(sf) sfGeometryAttributes(sf[[sfGeometryColumn(sf)]])

#' @export
sfGeometryAttributes.sfc <- function(sfc) {
  
  list(
    type = sfGeometryType(sfc),
    dim = sfDimension(sfc),
    bbox = sfBbox(sfc),
    epsg = sfEpsg(sfc),
    proj = sfProj(sfc)
  )
  
}


### GEOMETRY COLUMN
sfGeometryColumn <- function(sf) UseMethod("sfGeometryColumn")

#' @export
sfGeometryColumn.sf <- function(sf) attr(sf, "sf_column")


### GEOMETRY TYPE
sfGeometryType <- function(sf) UseMethod("sfGeometryType")

#' @export
sfGeometryType.sf <- function(sf) sfGeometryType(sf[[sfGeometryColumn(sf)]])

#' @export
sfGeometryType.sfc <- function(sfc) substr(class(sfc)[1], 5, nchar(class(sfc)[1]))

### DIMENSION
sfDimension <- function(sf) UseMethod("sfDimension")

#' @export
sfDimension.sf <- function(sf) sfDimension(sf[[sfGeometryColumn(sf)]])

#' @export
sfDimension.sfc <- function(sfc) class(sfc[[1]])[1]


### BBOX
sfBbox <- function(sf) UseMethod("sfBbox")

#' @export
sfBbox.sf <- function(sf) sfBbox(sf[[sfGeometryColumn(sf)]])

sfBbox.sfc <- function(sfc) attr(sfc, "bbox")


### EPSG
sfEpsg <- function(sf) UseMethod("sfEpsg") 

#' @export
sfEpsg.sf <- function(sf) sfEpsg(sf[[sfGeometryColumn(sf)]])

#' @export
sfEpsg.sfc <- function(sfc) attr(sfc, "crs")$epsg


### PROJ4STRINg
sfProj <- function(sf) UseMethod("sfProj")

#' @export
sfProj.sf <- function(sf) sfProj(sf[[sfGeometryColumn(sf)]])

#' @export
sfProj.sfc <- function(sfc) attr(sfc, "crs")$proj4string

