#' Decode Polyline
#' 
#' Decodes encoded polylines into a list of data.frames.
#' 
#' @param polylines vector of encoded polyline strings
#' 
#' @examples
#' polylines <- c(
#'   "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#'   "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
#' )
#' 
#' decode(polylines)
#' 
#' @export
decode <- function(polylines) UseMethod("decode")

#' @export
decode.character <- function(polylines) {
  rcpp_decode_polyline(polylines)
}

#' @export
decode.default <- function(polylines) stop("I was expecting a vector of encoded polylines")