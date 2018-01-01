#' Polyline WKT
#' 
#' Converts encoded polylines into well-known text. 
#' Note that 'polylines' refers to encoded strings here.
#' Valid inputs include any `sf` object with an encoded column.
#' 
#' The function also assumes Google Web Mercator projection (WSG 84 / EPSG:3857 / EPSG:900913)
#' for inputs and outputs.
#' 
#' @param obj \code{sfencoded} object or \code{encoded_column} of encoded polylines
#' 
#' @return well-known text representation of the encoded polylines
#' 
#' @export
polyline_wkt <- function(obj) UseMethod("polyline_wkt")

#' @export
polyline_wkt.sfencoded <- function(obj){
 
  geomCol <- attr(obj, "encoded_column")
  obj[[geomCol]] <- polyline_wkt(obj[[geomCol]])
  attr(obj, "encoded_column") <- NULL
  attr(obj, "wkt_column") <- geomCol
  return(obj)
}

#' @export
polyline_wkt.encoded_column <- function(obj) polyline_to_wkt(obj)

#' @export
polyline_wkt.default <- function(obj) stop(paste0("I was expecting an sfencoded object or an encoded_column"))
