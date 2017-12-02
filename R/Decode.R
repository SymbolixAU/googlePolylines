


## TODO
# decode <- function(obj, ...) { }  ## - to decode objects


## TODO

#' Decode Polyline
#' 
#' Decodes encoded polylines 
#' 
#' @param polylines
#' 
#' @examples 
#' polylines <- c(
#'   "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#'   "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
#' )
#' 
#' decodePolyline(polylines)
#' 
#' @export
decodePolyline <- function(polylines) {
  rcpp_decode_polyline(polylines)
}


