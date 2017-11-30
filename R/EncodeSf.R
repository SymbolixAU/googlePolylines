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
encodeSf <- function(sf) UseMethod("encodeSfGeometry")

## TODO:
## - encodeSf is designed to encode a whole sf object.
## - need a different function for just encoding the st_geometry column


# encodeGeometry <- function(sf) UseMethod("encodeGeometry")

#' @export
encodeSfGeometry.sf <- function(sf) {
  
  geomCol <- attr(sf, "sf_column")
  lst <- encodeSfGeometry(sf[[geomCol]])
  st_geometry(sf) <- NULL

  sf[[geomCol]] <- lst[['encoded']]
  # attr(sf[[geomCol]], 'sfc') <- c(lst[['attributes']])
  sf[['attributes']] <- lst[['attributes']]
  attr(sf, 'class') <- c("sfencoded", attr(sf, 'class'))
  return(sf)
}

#' @export
encodeSfGeometry.default <- function(sf) stop("expecting an sf object") 

