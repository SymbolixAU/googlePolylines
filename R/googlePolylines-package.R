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
## - having drop = FALSE will override the default `[.data.frame` method
## is this what I want?
## - if drop = TRUE, and a single column is selected (the encoded_column), 
## return the list, give it an 'sfencoded' class, and make it usable in googleway
## - should I remove 'sfencoded' class if the geometry is dropped? 
## because they could re-attach it....


#' @export
`[.sfencoded` <- function(x, i, j, drop = TRUE) { 
  
  geomColumn <- attr(x, "encoded_column")
  wktColumn <- attr(x, "wkt_column")
#  sfAtts <- attr(x, "sfAttributes")
  
  x <- `[.data.frame`(x, i, j, drop)
  
  if( !is.null(geomColumn) ) { 
    if( geomColumn %in% names(x) ) {
      attr(x, "encoded_column") <- geomColumn
    }
  }
  
  if( !is.null(wktColumn) ) {  
    if( wktColumn %in% names(x) ) {
      attr(x, "wkt_column") <- wktColumn
    }
  }
  
  
  ## sfAttributes relates to the whole data.frame, so attaching it 
  ## back on doesn't make sense
  # if( !is.null(sfAtts) ) {
  #   attr(x, "sfAttributes") <- sfAtts
  # }
  # 
  # if( inherits(x, "list") ) 
  #   class(x) <- c("sfencoded_list", class(x))
  
  # if ( is.null(geomColumn) && is.null(wktColumn) ) 
  #   class(x) <- setdiff(class(x),"sfencoded")
   
  return(x)
}

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