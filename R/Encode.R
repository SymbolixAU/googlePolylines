#' Encode
#' 
#' Encodes coordinates into an encoded polyline
#' 
#' @details 
#' Will work with
#' \itemize{
#'   \item{\code{sf} and \code{sfc} objects}
#'   \item{\code{data.frames}} - It will attempt to find lat & lon coordinates, 
#'   or you can explicitely define them using the \code{lat} and \code{lon} arguments
#'   \item{latitude and longitude coordinate vectors}
#' }
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
#' ## strip attributes
#' encodedLite <- encode(nc, strip = TRUE)
#' 
#' ## data.frame
#' df <- data.frame(polygonId = c(1,1,1,1),
#'   lineId = c(1,1,1,1),
#'   lon = c(-80.190, -66.118, -64.757, -80.190),
#'   lat = c(26.774, 18.466, 32.321, 26.774))
#'   
#' ## on a data.frame, it will attemp to find the lon & lat columns
#' encode(df)
#'   
#' ## Grouping by polygons and lines
#' df <- data.frame(polygonId = c(1,1,1,1,1,1,1,1,2,2,2,2),
#'   lineId = c(1,1,1,1,2,2,2,2,1,1,1,1),
#'   lon = c(-80.190, -66.118, -64.757, -80.190,  -70.579, -67.514, -66.668, -70.579, 
#'   -70, -49, -51, -70),
#'   lat = c(26.774, 18.466, 32.321, 26.774, 28.745, 29.570, 27.339, 28.745, 
#'   22, 23, 22, 22))
#' 
#' 
#' ## using dplyr groups   
#' 
#' library(dplyr)   
#' df %>%
#'   group_by(polygonId, lineId) %>% 
#'   summarise(polyline = encode(lon, lat))
#'   
#' ## using data.table
#' library(data.table)
#' setDT(df)
#' df[, encode(lon = lon, lat = lat), by = .(polygonId, lineId)]
#'   
#' }
#' 
#' 
#' @export
encode <- function(obj, strip = NA, lon = NA, lat = NA) UseMethod("encode")

### # @importFrom sf st_geometry

## TODO:
## - contributor credit for SF/C++ code


#' @export
encode.sf <- function(sf, strip = FALSE, ...) {

  geomCol <- attr(sf, "sf_column")
  lst <- encodeSfGeometry(sf[[geomCol]], strip)
  
  ###sf::st_geometry(sf) <- NULL
  sf[[geomCol]] <- lst

  attr(sf[[geomCol]], 'class') <- c('encoded_column', class(sf[[geomCol]]) )
  attr(sf, 'encoded_column') <- geomCol

  if (! inherits(sf, 'sfencoded'))
    attr(sf, 'class') <- c("sfencoded", attr(sf, 'class'))
  
  return(sf)
}

#' @export
encode.sfc <- function(sfc, strip = FALSE, ...) encodeSfGeometry(sfc, strip)

#' @export
encode.data.frame <- function(df, lat = NULL, lon = NULL, ...) {

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

getPoints <- function(encoded) getColumnType(encoded, "*POINT")

getPolylines <- function(encoded) getColumnType(encoded, "*LINESTRING")

getPolygons <- function(encoded) getColumnType(encoded, "*POLYGON")

getColumnType <- function(encoded, type) which(grepl(type, encodedColumnTypes(encoded)))

encodedColumn <- function(encoded) encoded[[attr(encoded, 'encoded_column')]]

encodedColumnTypes <- function(encoded) {
  vapply(encodedColumn(encoded), function(x) { attr(x, 'sfc')[2] }, '' )
}
