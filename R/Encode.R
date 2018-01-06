#' Encode
#' 
#' Encodes coordinates into an encoded polyline. 
#' 
#' The function assumes Google Web Mercator projection (WSG 84 / EPSG:3857 / EPSG:900913)
#' for inputs and outputs.
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
#' @param obj either an \code{sf} or \code{data.frame}
#' @param ... other parameters passed to methods
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
#'
#' ## Vector of lon/lat coordinates
#' 
#'   
#' }
#' 
#' @seealso encodeCoordinates
#' 
#' @export
encode <- function(obj, ...) UseMethod("encode")

#' @rdname encode
#'  
#' @param strip logical indicating if \code{sf} attributes should be stripped. 
#' Useful if you want to reduce the size even further, but you will lose the 
#' spatial attributes associated with the \code{sf} object 
#' @export
encode.sf <- function(obj, strip = FALSE, ...) {

  geomCol <- sfGeometryColumn(obj)
  lst <- rcpp_encodeSfGeometry(obj[[geomCol]], strip)
  
  if(!strip) sfAttrs <- sfGeometryAttributes(obj)
  
  obj[[geomCol]] <- lst
  
  ## strip attributes
  obj <- structure(obj, sf_column = NULL, agr = NULL, class = setdiff(class(obj), "sf"))

  attr(obj[[geomCol]], 'class') <- c('encoded_column', class(obj[[geomCol]]) )
  attr(obj, 'encoded_column') <- geomCol
  
  if(!strip) attr(obj, "sfAttributes") <- sfAttrs

  if (!inherits(obj, 'sfencoded'))
    attr(obj, 'class') <- c("sfencoded", attr(obj, 'class'))
  
  return(obj)
}

#' @export
encode.sfc <- function(obj, strip = FALSE, ...) rcpp_encodeSfGeometry(obj, strip)

#' @rdname encode
#' @param lon vector of longitudes
#' @param lat vector of latitudes
#' @export
encode.data.frame <- function(obj, lon = NULL, lat = NULL, ...) {

  if(is.null(lat)) lat <- find_lat_column(names(obj))
  if(is.null(lon)) lon <- find_lon_column(names(obj))

  rcpp_encode_polyline(obj[[lon]], obj[[lat]])
}



#' @export
encode.default <- function(obj, ...) {
  stop(paste0("I currently don't know how to encode ", paste0(class(obj), collapse = ", "), " objects"))
}


#' Encode coordinates
#' 
#' Encodes a vector of lon & lat coordinates
#' @param lon vector of longitudes
#' @param lat vector of latitudes
#' 
#' @examples 
#' \dontrun{
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
#'   summarise(polyline = encodeCoordinates(lon, lat))
#'   
#' ## using data.table
#' library(data.table)
#' setDT(df)
#' df[, encodeCoordinates(lon = lon, lat = lat), by = .(polygonId, lineId)]
#' 
#' 
#' }
#' 
#' @export
encodeCoordinates <- function(lon, lat) rcpp_encode_polyline(lon, lat)

