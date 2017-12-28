


## TODO
# decode <- function(obj, ...) { }  ## - to decode objects


#' Decode Polyline
#' 
#' Decodes encoded polylines 
#' 
#' @param polylines strings of encoded polylines
#' 
#' @examples 
#' polylines <- c(
#'   "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#'   "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
#' )
#' 
#' decodePolyline(polylines)
#' 
decodePolyline <- function(polylines) {
  rcpp_decode_polyline(polylines)
}


