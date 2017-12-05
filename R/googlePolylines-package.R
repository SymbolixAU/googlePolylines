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


