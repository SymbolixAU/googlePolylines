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

## TODO:
## - encodeSf is designed to encode a whole sf object.
## - need a different function for just encoding the st_geometry column


# encodeGeometry <- function(sf) UseMethod("encodeGeometry")

#' @export
encode.sf <- function(sf) {
  
  geomCol <- attr(sf, "sf_column")
  lst <- encodeSfGeometry(sf[[geomCol]])
  st_geometry(sf) <- NULL

  sf[[geomCol]] <- lst
  
  attr(sf, 'class') <- c("sfencoded", attr(sf, 'class'))
  #attr(sf[[geomCol]], 'class') <- "encoded"
  return(sf)
}

#' @export
encodeSfGeometry.default <- function(sf) stop("can't do this at the moment") 

