#' @useDynLib googlePolylines
#' @importFrom Rcpp sourceCpp
NULL

#' @export
str.encoded_column <- function(encoded, ...) {
  n <- length(encoded)
  cat(paste0(class(encoded)[1], " of length ", n))
  if (n > 0) {
    cat("; first list element: ")
    str(encoded[[1]], ...)
  }
}


