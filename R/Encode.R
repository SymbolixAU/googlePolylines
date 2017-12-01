#' Encode sf
#' 
#' Converts an sf object into an encoded sf object
#' 
#' @param sf object
#' 
#' @return \code{sfencoded} object
#' 
#' @examples 
#' 
#' @importFrom sf st_geometry
#' @export
encode <- function(sf) UseMethod("encode")

# encodeGeometry <- function(sf) UseMethod("encodeGeometry")

#' @export
encode.sf <- function(sf) {
  
  geomCol <- attr(sf, "sf_column")
  lst <- encodeSfGeometry(sf[[geomCol]])
  st_geometry(sf) <- NULL

  sf[[geomCol]] <- lst
  #attr(sf[[geomCol]], 'encoded_column') <- geomCol
  
  attr(sf, 'encoded_column') <- geomCol
  
  if (! inherits(sf, 'sfencoded'))
    attr(sf, 'class') <- c("sfencoded", attr(sf, 'class'))
  
  return(sf)
}

#' @export
encode.sfc <- function(sfc) encodeSfGeometry(sfc)


#' @export
encode.default <- function(sf) stop("can't do this at the moment") 





## TODO:
##- extract specific rows of sfencoded depending on the 'type' you want

#' @export
getPoints <- function(encoded) which(grepl("*POINT", encodedColumnTypes(encoded)))

#' @export
getPolylines <- function(encoded) which(grepl("*LINESTRING", encodedColumnTypes(encoded)))

#' @export
getPolygons <- function(encoded)  which(grepl("*POLYGON", encodedColumnTypes(encoded)))


encodedColumn <- function(encoded) encoded[[attr(encoded, 'encoded_column')]]

encodedColumnTypes <- function(encoded) vapply(encodedColumn(encoded), function(x) { attr(x, 'sfc')[2] }, '' )
