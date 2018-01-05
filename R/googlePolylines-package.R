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
## - test the objects created in the vignette are equivalent by plotting in googleway
## - contributor credit for SF/C++ code
## - XYZ and XYM dims
## - sfg
## - decoding
## - print method for encoded geo columns
## - polygons are closed correctly
## - wkt_polyline shoudl fail on non-attributed sfencoded

## TODO(updates):
## - geometry collection

## TODO:
## - sfencoded without attributes on each row

## TODO:
## - test each of my WKTs can be used in boost. 