
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


## TODO:
## - if drop = TRUE, and a single column is selected (the encoded_column),
## return the list, give it an 'sfencoded' class, and make it usable in googleway
## - should I remove 'sfencoded' class if the geometry is dropped?
## because they could re-attach it....
## - include sfAttributes in polyline_wkt


#' @export
`[.sfencoded` <- function(x, i, j, ..., drop = TRUE) {

  geomColumn <- attr(x, "encoded_column")
  wktColumn <- attr(x, "wkt_column")
  attr(x, "sfAttributes") <- NULL

  x <- NextMethod()
  x <- attachEncodedAttribute(x, geomColumn, "encoded_column")
  x <- attachEncodedAttribute(x, wktColumn, "wkt_column")

  if( is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column")) ){
    x <- removeSfencodedClass(x)
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


#' @export
print.sfencoded <- function(x, ... ){
  
  if(is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column"))) {
    NextMethod()
    return()
  }
  
  printSfEncoded(x, "sfencoded", ... )
}

#' @export
print.sfencodedLite <- function(x, ... ){
  
  if(is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column"))) {
    NextMethod()
    return()
  }
  
  printSfEncoded(x, "sfencodedLite", ...)
}


printSfEncodedPrefix <- function(e, encType) {
  
  if(encType == "sfencoded") {
    e <- vapply(e, function(z) {
      paste0(
        attr(z, "sfc")[2], ": ",
        substr(z[1], 1, pmin(nchar(z[1]), 20)),
        "..."
      )
    }, "" )
  }else{
    e <- vapply(e, function(z) {
      paste0(
        substr(z[1], 1, pmin(nchar(z[1]), 20)),
        "..."
      )
    }, "" )
  }
  return(e)
  
}

printSfEncoded <- function(x, encType, ...) {
  
  encoded <- attr(x, "encoded_column")
  wkt <- attr(x, "wkt_column")

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
  
  x <- removeSfencodedClass(x)
  
  print(x)
  invisible(x)
}


# nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
# enc <- encode(nc)
# wkt <- polyline_wkt(enc)
# df <- enc
# df$wkt <- wkt$geometry

# nc2 <- rbind(nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc, nc)
# nc3 <- rbind(nc2, nc2, nc2, nc2, nc2, nc2, nc2, nc2, nc2, nc2, nc2, nc2)


# library(sf)
# df <- data.frame(myId = c(1,1,1,1,1,1,1,1,2,2,2,2),
# 								 lineId = c(1,1,1,1,2,2,2,2,1,1,1,2),
# 								 lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, -70, -49, -51, -70),
# 								 lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 22, 23, 22, 22))
#
# p1 <- as.matrix(df[4:1, c("lon", "lat")])
# p2 <- as.matrix(df[8:5, c("lon", "lat")])
# p3 <- as.matrix(df[9:12, c("lon", "lat")])
#
# point <- sf::st_sfc(sf::st_point(x = c(df[1,"lon"], df[1,"lat"])))
# multipoint <- sf::st_sfc(sf::st_multipoint(x = as.matrix(df[1:2, c("lon", "lat")])))
# polygon <- sf::st_sfc(sf::st_polygon(x = list(p1, p2)))
# linestring <- sf::st_sfc(sf::st_linestring(p3))
# multilinestring <- sf::st_sfc(sf::st_multilinestring(list(p1, p2)))
# multipolygon <- sf::st_sfc(sf::st_multipolygon(x = list(list(p1, p2), list(p3))))
# #
# sf <- rbind(
# 	st_sf(geometry = polygon),
# 	st_sf(geometry = multipolygon),
# 	st_sf(geometry = multilinestring),
# 	st_sf(geometry = linestring),
# 	st_sf(geometry = point),
#   st_sf(geometry = multipoint)
# 	)
# enc <- encode(sf)

