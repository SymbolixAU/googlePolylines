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
  rcpp_decode_polyline(polylines, 'coords')
}

## TODO(decode encoded object)

#' @export
decode.encoded_column <- function( polylines ) {
  ## encoded_columns are a list
  ## TODO(use rcpp_decode_polyline_list())
  #lapply(polylines, decode)
  rcpp_decode_polyline_list( polylines, 'sfc' )
}

#' @export
decode.zm_column <- function( polylines ) {
  ## TODO( return ZM, rather than lat/lon )
  ##lapply(polylines, function(x) rcpp_decode_polyline(x, attr(x, 'class')))
  rcpp_decode_polyline_list( polylines, 'zm' )
}

## TODO(rcpp_decode_polyline_list()) to handle the encoded columns of coords and ZM dims

#' @export
decode.default <- function(polylines) stop("I don't know how to decode this object")


