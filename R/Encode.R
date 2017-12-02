#' Encode
#' 
#' Encodes coordinates into an encoded polyline
#' 
#' @param obj object
#' @param strip (optional) logical indicating if \code{sf} attributes should be stripped. 
#' Useful if the object contains only one type of geometry and you want to reduce the size
#' even further
#' @param lon (optional) vector of longitudes
#' @param lat (optional) vector of latitudes
#' 
#' @return encoded object
#' 
#' @examples 
#' \dontrun{
#' 
#' ## sf objects
#' library(sf)
#' nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#' 
#' encoded <- encode(nc)
#' 
#' ## strip off attributes
#' encodedLite <- encode(nc, TRUE)
#' 
#' 
#' }
#' 
#' 
#' @importFrom sf st_geometry
#' @export
encode <- function(obj, strip = NA, lon = NA, lat = NA) UseMethod("encode")

## TODO:
## - non-sf objects
## - will require other parameters, such as lat & long

#' @export
encode.sf <- function(sf, strip = FALSE) {

  geomCol <- attr(sf, "sf_column")
  lst <- encodeSfGeometry(sf[[geomCol]], strip)
  
  sf::st_geometry(sf) <- NULL

  sf[[geomCol]] <- lst

  attr(sf[[geomCol]], 'class') <- c('encoded_column', class(sf[[geomCol]]) )
  attr(sf, 'encoded_column') <- geomCol

  if (! inherits(sf, 'sfencoded'))
    attr(sf, 'class') <- c("sfencoded", attr(sf, 'class'))
  
  return(sf)
}

#' @export
encode.sfc <- function(sfc, strip = FALSE) encodeSfGeometry(sfc, strip)

#' @export
encode.data.frame <- function(df, lat = NULL, lon = NULL ) {

 if(is.null(lat)) lat <- find_lat_column(names(df))
 if(is.null(lon)) lon <- find_lon_column(names(df))

 rcpp_encode_polyline(df[[lon]], df[[lat]])
}

#' @export
encode.numeric <- function(lon, lat, ...) {
  rcpp_encode_polyline(lon, lat)
}

#' @export
encode.default <- function(obj, ...) {
  stop(paste0("I currently don't know how to encode ", class(obj), " objects"))
}




## TODO:
##- extract specific rows of sfencoded depending on the 'type' you want

#' @export
getPoints <- function(encoded) which(grepl("*POINT", encodedColumnTypes(encoded)))

#' @export
getPolylines <- function(encoded) which(grepl("*LINESTRING", encodedColumnTypes(encoded)))

#' @export
getPolygons <- function(encoded)  which(grepl("*POLYGON", encodedColumnTypes(encoded)))


encodedColumn <- function(encoded) encoded[[attr(encoded, 'encoded_column')]]

encodedColumnTypes <- function(encoded) {
  vapply(encodedColumn(encoded), function(x) { attr(x, 'sfc')[2] }, '' )
}
