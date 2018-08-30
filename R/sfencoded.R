
#' @export
as.data.frame.sfencoded <- function(x, ...) {
  x <- removeSfencodedClass(x)
  x <- removeSfEncodedAttributes(x)
  NextMethod()
}

strSfEncoded <- function(object, ...) {
  n <- length(object)
  cat(paste0(class(object)[1], " of length ", n))
  if (n > 0) {
    cat("; first element: ")
    utils::str(object[1], ...)
  }
}

#' @export
str.encoded_column <- strSfEncoded

#' @export
str.wkt_column <- strSfEncoded

#' @export
str.zm_column <- strSfEncoded


#' @export
`[.sfencoded` <- function(x, i, j, ..., drop = TRUE) {
  
  encodedClass <- attr(x, 'class')[1]
  geomColumn <- attr(x, "encoded_column")
  wktColumn <- attr(x, "wkt_column")
  # zmColumn <- attr(x, "zm_column")
  attr(x, "sfAttributes") <- NULL

  x <- NextMethod()
  x <- attachEncodedAttribute(x, geomColumn, "encoded_column")
  x <- attachEncodedAttribute(x, wktColumn, "wkt_column")
  # x <- attachEncodedAttribute(x, zmColumn, "zm_column")

  if( is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column")) ){
    x <- removeSfencodedClass(x)
  } else {
    ## re-attach 'sfencoded' attribute?
    attr(x, 'class') <- unique(c(encodedClass, attr(x, 'class')))
  }
  
  return(x)
}

#' @export
`[.sfencodedLite` <- `[.sfencoded`



attachEncodedAttribute <- function(x, attrCol, attribute) {
  if ( !is.null(attrCol) ) {
    if ( attrCol %in% names(x) ) {
      attr(x, attribute) <- attrCol
    }
  }
  return(x)
}

removeSfencodedClass <- function(x) {
  attr(x, "class") <- setdiff(class(x), c("sfencoded", "sfencodedLite"))
  return(x)
}

removeSfEncodedAttributes <- function(x) {

  geomCol <- attr(x, "encoded_column")
  wktCol <- attr(x, "wkt_column")
  # zmCol <- attr(x, "zm_column")
  
  if(!is.null(geomCol) && geomCol %in% names(x)) {
    x[[geomCol]] <- sapply(x[[geomCol]], function(y) { 
      attr(y, "sfc") <- NULL 
      return(y) 
      })
    
    attr(x[[geomCol]], "class") <- NULL
    
  }
  
  if(!is.null(wktCol) && wktCol %in% names(x)) {
    attr(x[[wktCol]], "class") <- NULL
  }
  
  # if(!is.null(zmCol) && zmCol %in% names(x)) {
  #   x[[zmCol]] <- sapply(x[[zmCol]], function(y) { 
  #     attr(y, "zm") <- NULL 
  #     return(y) 
  #   })
  #   
  #   attr(x[[zmCol]], "class") <- NULL
  # }
  
  attr(x, "encoded_column") <- NULL
  attr(x, "wkt_column") <- NULL
  # attr(x, "zm_column") <- NULL
  attr(x, "sfAttributes") <- NULL
  
  return(x)
}



#' @export
print.sfencoded <- function(x, ... ){
  
  if(is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column"))) {
    NextMethod()
    return()
  }
  
  printSfEncoded(x, ... )
}

#' @export
print.sfencodedLite <- print.sfencoded

printSfEncoded <- function(x, ...) {
  
  encType <- ifelse(inherits(x, 'sfencoded'), 'sfencoded', 'sfencodedLite')
  
  encoded <- attr(x, "encoded_column")
  wkt <- attr(x, "wkt_column")
  # zm <- attr(x, 'zm_column')

  if(!is.null(encoded)) {
    e <- x[[encoded]]
    e <- printSfEncodedPrefix(e, encType)
    e <- stats::setNames(data.frame(e), encoded)
    x[, encoded] <- e
  }

  if(!is.null(wkt)) {
    w <- x[[wkt]]
    w <- paste0(substr(w, 1, pmin(nchar(w), 30)), "...")
    w <- stats::setNames(data.frame(w), wkt)
    x[, wkt] <- w
  }
  
  # if(!is.null(zm) ) {
  #   z <- x[[zm]]
  #   z <- printZMattributes(z)
  #   z <- stats::setNames(data.frame(z), zm)
  #   x[, zm] <- z
  # }
  
  x <- removeSfencodedClass(x)
  
  print(x)
  invisible(x)
}

# printZMattributes <- function(zm) {
#   z <- vapply(zm, function(x) {
#     paste0(
#       substr(x[1], 1, pmin(nchar(x[1]), 20))
#       , "..."
#     )
#   }, "" )
#   return(z)
# }

printSfEncodedPrefix <- function(e, encType) {
  
  if(encType == "sfencoded") {
    e <- vapply(e, function(z) {
      m <- pmin(nchar(z[1]), 20)
      a <- attr(z, "sfc")[2]
      ifelse(is.na(m), paste0(a, ": EMPTY"), 
        paste0(
          a, ": ",
             substr(z[1], 1, m) 
          , ifelse(m >= 20, "...", "")
        )
      )
    }, "" )
  } else {
    e <- vapply(e, function(z) {
      m <- pmin(nchar(z[1]), 20)
      ifelse(is.na(m), "EMPTY", 
        paste0(
          substr(z[1], 1, m),
          ifelse(m >= 20, "...", "")
        )
      )
    }, "" )
  }
  return(e)
}

