#' Decode Polyline
#' 
#' Decodes encoded polylines into a list of data.frames.
#' 
#' @param polylines vector of encoded polyline strings
#' @param precision 
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
decode <- function(polylines, precision) UseMethod("decode")

#' @export
decode.character <- function(polylines, precision) {
  rcpp_decode_polyline(polylines, 'coords', precision)
}

#' @export
decode.encoded_column <- function( polylines, precision ) {
  ## encoded_columns are a list
  rcpp_decode_polyline_list( polylines, 'sfc', precision )
}

#' @export
decode.zm_column <- function( polylines, precision ) {
  rcpp_decode_polyline_list( polylines, 'zm', precision )
}

## TODO(rcpp_decode_polyline_list()) to handle the encoded columns of coords and ZM dims

#' @export
decode.default <- function(polylines, precision) stop("I don't know how to decode this object")


