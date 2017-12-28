
## TODO:
## - sfencoded without attributes on each row

#' Polyline WKT
#' 
#' Converts encoded polylines into well-known text
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
  return(obj)
}

#' @export
polyline_wkt.encoded_column <- function(obj) polyline_to_wkt(obj)

#' @export
polyline_wkt.default <- function(obj) stop(paste0("I was expecting an sfencoded object or an encoded_column"))
