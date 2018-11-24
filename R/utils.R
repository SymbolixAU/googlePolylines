# Find Lat Column
#
# Tries to identify the latitude column
# @param names string of column names
find_lat_column <- function(names) {
  
  lat = names[grep("^(lat|lats|latitude|latitudes|stop_lat|shape_pt_lat)$", names, ignore.case = TRUE)]
  
  if (length(lat) == 1) {
    return(lat)
  }
  stop("Couldn't infer latitude column")
}

# Find Lon Column
#
# Tries to identify the longitude column
# @param names string of column names
find_lon_column <- function(names, calling_function) {
  
  lon = names[grep("^(lon|lons|lng|lngs|long|longs|longitude|longitudes|stop_lon|shape_pt_lon)$", names, ignore.case = TRUE)]
  
  if (length(lon) == 1) {
    return(lon)
  }
  stop("Couldn't infer longitude column")
}




