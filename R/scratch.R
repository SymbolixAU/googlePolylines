
## TODO
## - test googleway normalise sf works
## - googleway - handle wkt objects
## - test new wkt methods (including preicsion)


# 
# ## creating wkt class
# 
# library(sf)
# nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
# 
# ## encode to polylines
# enc <- encode(nc)
# 
# ## convert encoded lines to well-known text
# wkt <- polyline_wkt(enc)
# 
# # just return a data.frame, with a wkt_column attribute? 