#' Encode
#' 
#' Encodes coordinates into an encoded polyline. 
#' 
#' @details 
#' 
#' The function assumes Google Web Mercator projection (WSG 84 / EPSG:3857 / EPSG:900913)
#' for inputs and outputs.
#' 
#' Will work with
#' \itemize{
#'   \item{\code{sf} and \code{sfc} objects} directly
#'   \item{\code{data.frames}} - It will attempt to find lat & lon coordinates, 
#'   or you can explicitely define them using the \code{lat} and \code{lon} arguments
#' }
#' 
#' @param obj either an \code{sf} object or \code{data.frame}
#' @param ... other parameters passed to methods
#' 
#' @return \code{sfencoded} object
#' 
#' @note When an \code{sfencoded} object is colulmn-subset using \code{`[`} and 
#' the encoded column is retained, the attributes of the column will remain. This 
#' is different behaviour to standard subsetting of \code{data.frames}, where all 
#' attributes are dropped by default. See examples.
#' 
#' @examples 
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
#' ## use byrow = TRUE to convert each row individually
#' encode(df, byrow = TRUE)
#' 
#' 
#' \dontrun{
#' 
#' ## sf objects
#' library(sf)
#' nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#' 
#' encoded <- encode(nc)
#' 
#' ## view attributes
#' attributes(encoded) 
#' 
#' ## view attributes of subset object
#' attributes(encoded[, c("AREA", "PERIMETER", "geometry")])
#' 
#' ## view attributes without encoded column
#' attributes(encoded[, c("AREA", "PERIMETER")])
#' 
#' ## strip attributes
#' encodedLite <- encode(nc, strip = TRUE)
#' 
#' attributes(encodedLite)
#' 
#' ## view attributes of subset lite object
#' attributes(encodedLite[, c("AREA", "PERIMETER", "geometry")])
#' 
#' ## view attributes without encoded column
#' attributes(encodedLite[, c("AREA", "PERIMETER")])
#' }
#' 
#' @note When encoding an \code{sf} object, only the XY dimensions will be used,
#' the Z or M (3D and/or Measure) dimensions are dropped.
#' 
#' @seealso \link{encodeCoordinates}
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

  # obj[[geomCol]] <- lst[['XY']]
  obj[[geomCol]] <- lst
  
  ## strip attributes
  obj <- structure(obj, sf_column = NULL, agr = NULL, class = setdiff(class(obj), "sf"))

  attr(obj[[geomCol]], 'class') <- c('encoded_column', class(obj[[geomCol]]) )
  attr(obj, 'encoded_column') <- geomCol
  
  # ## TODO(remove this vapply step and return from rcpp a flag if the ZM attrs are attached)
  # if (any(vapply(lst[['ZM']], length, 0L)) > 0) {
  #   zmCol <- paste0(geomCol, "ZM")
  #   zmCol <- make.names(c(names(obj), zmCol), unique = T)
  #   zmCol <- zmCol[length(zmCol)]
  #   
  #   obj[[zmCol]] = lst[['ZM']]
  #   
  #   ## attach ZM attribute column
  #   attr(obj, 'zm_column') <- zmCol
  #   attr(obj[[zmCol]], 'class') <- c('zm_column', class(obj[[zmCol]]))
  # }
  
  if (!strip) {
    attr(obj, "sfAttributes") <- sfAttrs
    
    if(!inherits(obj, 'sfencoded'))
      attr(obj, 'class') <- c("sfencoded", attr(obj, 'class'))
  } else {
    if(!inherits(obj, 'sfencodedLite'))
      attr(obj, 'class') <- c("sfencodedLite", attr(obj, 'class'))
  }
  
  return(obj)
}

#' @export
encode.sfc <- function(obj, strip = FALSE, ...) {
  lst <- rcpp_encodeSfGeometry(obj, strip)
  
  # ## TODO(remove this vapply step and return from rcpp a flag if the ZM attrs are attached)
  # if (all(vapply(lst[['ZM']], length, 0L)) == 0) {
  #   
  #   lst[['ZM']] <- NULL
  #   lst <- lst[['XY']] ## to keep previous behaviour? 
  # }
  
  return( lst )
}

#' @rdname encode
#' @param lon vector of longitudes
#' @param lat vector of latitudes
#' @param byrow logical indicating if the encoding should be done for each row
#' @export
encode.data.frame <- function(obj, lon = NULL, lat = NULL, byrow = FALSE, ...) {

  if(is.null(lat)) lat <- find_lat_column(names(obj))
  if(is.null(lon)) lon <- find_lon_column(names(obj))

  if ( byrow ) {
    return( rcpp_encode_polyline_byrow( obj[[lon]], obj[[lat]] ) )
  }
  return( rcpp_encode_polyline(obj[[lon]], obj[[lat]]) )
}



#' @export
encode.default <- function(obj, ...) {
  stop(paste0("I currently don't know how to encode ", paste0(class(obj), collapse = ", "), " objects"))
}


#' Encode coordinates
#' 
#' Encodes a vector of lon & lat coordinates
#' 
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
#' @seealso \link{encode}
#' 
#' @export
encodeCoordinates <- function(lon, lat) rcpp_encode_polyline(lon, lat)

