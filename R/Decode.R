
## TODO
# decode <- function(obj, ...) { }  ## - to decode objects

#' Decode Polyline
#' 
#' Decodes encoded polylines
#' 
#' @param polylines strings of encoded polylines
#' 
#' @examples
#' polylines <- c(
#'   "ohlbDnbmhN~suq@am{tAw`qsAeyhGvkz`@fge}A",
#'   "ggmnDt}wmLgc`DesuQvvrLofdDorqGtzzV"
#' )
#' 
#' decodePolyline(polylines)
#' 
#' @export
decode <- function(polylines) UseMethod("decodePolyline")

#' @export
decodePolyline.character <- function(polylines) {
  rcpp_decode_polyline(polylines)
}

#' @export
decodePolyline.sfencoded <- function(polylines) {
  
  ## get the encoded_column and decode into an 'sf' object
  if(is.null(attr(polylines, "encoded_column"))) stop("Can not find the encoded_column")
  
  geomCol <- attr(polylines, "encoded_column")
  
  decode(polylines[[geomCol]])
  
}

decodePolyline.encoded_column <- function(polylines) {
  
  ## for each list entry, decode, and turn into the correct sf object. 
  ## should do this at the C++ level for speed. 
  
  ## this will return a 'st_geometry' column, that will be attached to the 
  ## rest of the sfencoded data.frame
  str(polylines)
  rcpp_decode_sfencoded(polylines)
  
  
  ## then need to ensure the correct sf attributes are attached to make it 
  ## a valid sf object
  
}






