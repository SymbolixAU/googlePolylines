#' @useDynLib googlePolylines
#' @importFrom Rcpp sourceCpp
NULL

#' @export
str.encoded_column <- function(object, ...) {
  n <- length(object)
  cat(paste0(class(object)[1], " of length ", n))
  if (n > 0) {
    cat("; first list element: ")
    utils::str(object[[1]], ...)
  }
}


## TODO:
## - decoding
## - print method for encoded geo columns

## TODO(updates):
## - polygons are closed correctly
## - geometry collection
## - wkt_polyline on non-sfencoded objects: wkt_polyline(x, col = ... )
## - polyline_wkt on non-sfencoded objects: polyline_wkt(x, col = ... )
