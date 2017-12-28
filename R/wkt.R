
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
polyline_wkt.sfencoded <- function(sfencoded){
 
  geomCol <- attr(sfencoded, "encoded_column")
  sfencoded[[geomCol]] <- polyline_wkt(sfencoded[[geomCol]])
  return(sfencoded)
}

#' @export
polyline_wkt.encoded_column <- function(encodedCol) polyline_to_wkt(encodedCol)

#' @export
polyline_wkt.default <- function(obj) stop(paste0("I was expecting an sfencoded object or an encoded_column"))
