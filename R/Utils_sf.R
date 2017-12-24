### SF ATTRIBUTES
sfGeometryAttributes <- function(sf) UseMethod("sfGeometryAttributes")

#' @export
sfGeometryAttributes.sf <- function(sf) sfGeometryAttributes(sf[[getGeometryColumn(sf)]])

#' @export
sfGeometryAttributes.sfc <- function(sfc) {
  
  list(
    type = getGeometryType(sfc),
    dim = getDimension(sfc),
    bbox = getBbox(sfc),
    epsg = getEpsg(sfc),
    proj = getProj(sfc)
  )
  
}


### GEOMETRY COLUMN
getGeometryColumn <- function(sf) UseMethod("getGeometryColumn")

#' @export
getGeometryColumn.sf <- function(sf) attr(sf, "sf_column")


### GEOMETRY TYPE
getGeometryType <- function(sf) UseMethod("getGeometryType")

#' @export
getGeometryType.sf <- function(sf) getGeometryType(sf[[getGeometryColumn(sf)]])

#' @export
getGeometryType.sfc <- function(sfc) substr(class(sfc)[1], 5, nchar(class(sfc)[1]))

### DIMENSION
getDimension <- function(sf) UseMethod("getDimension")

#' @export
getDimension.sf <- function(sf) getDimension(sf[[getGeometryColumn(sf)]])

#' @export
getDimension.sfc <- function(sfc) class(sfc[[1]])[1]


### BBOX
getBbox <- function(sf) UseMethod("getBbox")

#' @export
getBbox.sf <- function(sf) getBbox(sf[[getGeometryColumn(sf)]])

getBbox.sfc <- function(sfc) attr(sfc, "bbox")


### EPSG
getEpsg <- function(sf) UseMethod("getEpsg") 

#' @export
getEpsg.sf <- function(sf) getEpsg(sf[[getGeometryColumn(sf)]])

#' @export
getEpsg.sfc <- function(sfc) attr(sfc, "crs")$epsg


### PROJ4STRINg
getProj <- function(sf) UseMethod("getProj")

#' @export
getProj.sf <- function(sf) getProj(sf[[getGeometryColumn(sf)]])

#' @export
getProj.sfc <- function(sfc) attr(sfc, "crs")$proj4string

