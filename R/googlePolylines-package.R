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


#' @export
`[.sfencoded` <- function(x, i, j, ...) { 
  
  geomColumn <- attr(x, "encoded_column")
  x <- NextMethod()
  if( geomColumn %in% names(x)) attr(x, "encoded_column") <- geomColumn
  return(x)
}

