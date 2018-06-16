#' Polyline WKT
#' 
#' Converts encoded polylines into well-known text. 
#' 
#' @param obj \code{sfencoded} object or \code{encoded_column} of encoded polylines
#' 
#' @return well-known text representation of the encoded polylines
#' 
#' @examples 
#' \dontrun{
#' 
#' library(sf)
#' nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#' 
#' ## encode to polylines
#' enc <- encode(nc)
#' 
#' ## convert encoded lines to well-known text
#' wkt <- polyline_wkt(enc)
#' 
#' }
#' 
#' @note This will not work if you have specified \code{strip = TRUE} for \code{encode()}
#' 
#' @details
#' 'Polylines' refers to lat/lon coordinates encoded into strings using Google's 
#' polyline encoding algorithm.
#' 
#' The function assumes Google Web Mercator projection (WSG 84 / EPSG:3857 / EPSG:900913)
#' for inputs and outputs.
#' 
#' @export
polyline_wkt <- function(obj) UseMethod("polyline_wkt")

#' @export
polyline_wkt.sfencoded <- function(obj) {
  
  if(is.null(attr(obj, "encoded_column"))) stop("Can not find the encoded_column")
 
  geomCol <- attr(obj, "encoded_column")

  obj[[geomCol]] <- polyline_wkt(obj[[geomCol]])

  attr(obj[[geomCol]], "class") <- c("wkt_column", class(obj[[geomCol]] ) )
  attr(obj, "class") <- c("wkt", setdiff(attr(obj, "class"), "sfencoded"))
  
  attr(obj, "encoded_column") <- NULL
  attr(obj, "wkt_column") <- geomCol
  return(obj)
}

#' @export
polyline_wkt.sfencodedLite <- polyline_wkt.sfencoded

#' @export
polyline_wkt.encoded_column <- function(obj) polyline_to_wkt(obj)


#' @export
polyline_wkt.default <- function(obj) stop(paste0("I was expecting an sfencoded object or an encoded_column"))

#' @export
`[.wkt` <- `[.sfencoded`


#' @export
print.wkt <- function(x, ... ){

  if( is.null(attr(x, "wkt_column")) ) {
    NextMethod()
    return()
  }

  printwkt(x, ... )
}

printwkt <- function(x, ...) {

  wkt <- attr(x, "wkt_column")

  if(!is.null(wkt)) {
    for (i in wkt) {
      w <- as.character( x[[i]] )
      w <- paste0(substr(w, 1, pmin(nchar(w), 30)), "...")
      w <- stats::setNames(data.frame(w), i)
      x[, i] <- w 
    }
  }

  x <- removeWktClass(x)

  print(x)
  invisible(x)
}

removeWktClass <- function(x) { 
  attr(x, "class") <- setdiff(class(x), "wkt")
  return(x)
}

removeWktAttributes <- function(x) {
  
  wktCol <- attr(x, "wkt_column")
  
  if(!is.null(wktCol) && wktCol %in% names(x)) {
    attr(x[[wktCol]], "class") <- NULL
  }
  
  attr(x, "wkt_column") <- NULL
  attr(x, "sfAttributes") <- NULL
  return(x)
}

#' WKT Polyline
#' 
#' Converts well-known text into encoded polylines.
#' 
#' @param obj \code{sfencoded} object, \code{wkt_column} or character vector
#'  of well-known text
#' 
#' @return encoded polyline representation of geometries
#' 
#' @examples 
#' \dontrun{
#' 
#' library(sf)
#' nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#' 
#' ## encode to polylines
#' enc <- encode(nc)
#' 
#' ## convert encoded lines to well-known text
#' wkt <- polyline_wkt(enc)
#' 
#' ## convert well-known text back to polylines
#' enc2 <- wkt_polyline(wkt)
#' 
#' ## data.frame column of well-known text
#' df <- data.frame(
#'   wkt = c("LINESTRING(0 0, 1 1, 1 2, 2 2)")
#' )
#' 
#' df$polyline <- wkt_polyline(df$wkt)
#' 
#' ## use \code{unlist} to strip attributes
#' df$polyline <- unlist(df$polyline)
#' 
#' 
#' }
#' 
#' @details
#' 'Polylines' refers to lat/lon coordinates encoded into strings using Google's 
#' polyline encoding algorithm.
#' 
#' @export
wkt_polyline <- function(obj) UseMethod("wkt_polyline")

#' @export
wkt_polyline.wkt <- function(obj) {
  
  if(is.null(attr(obj, "wkt_column"))) stop("Can not find the wkt_column")
  
  geomCol <- attr(obj, "wkt_column")
  
  obj[[geomCol]] <- wkt_polyline(obj[[geomCol]])
  
  attr(obj[[geomCol]], "class") <- c("encoded_column", class(obj[[geomCol]]))
  
  attr(obj, "wkt_column") <- NULL
  
  attr(obj, "class") <- c("sfencoded", setdiff(attr(obj, "class"), "wkt"))
  
  attr(obj, "encoded_column") <- geomCol
  return(obj)
}

#' @export
wkt_polyline.wkt_column <- function(obj) wkt_to_polyline(obj)

#' @export
wkt_polyline.character <- function(obj) wkt_to_polyline(obj)

#' @export
wkt_polyline.factor <- function(obj) wkt_to_polyline(obj)

#' @export
wkt_polyline.default <- function(obj) stop(paste0("I was expecting a charactor vector or a wkt object with a wkt_column"))
