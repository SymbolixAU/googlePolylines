# 
# library(googlePolylines)
# library(sf)
# sf <- st_sf(a = c("x", "y"), geom = st_sfc(st_point(3:4), st_point(3:4)))
# sf[["geom2"]] = st_sfc(st_point(3:4), st_point(3:4))
# sf
# 
# encode( sf )
# 
# multisfGeometryColumn <- function(sf) {
#   names( which( sapply( sf, function(x) inherits(x, "sfc") ) ) )
# }
# 
# multisfGeometryColumn( sf )
# 
# 
# library(Rcpp)
# 
# 
# cppFunction('void listTest(Rcpp::List lst) {
#   int n = lst.size();
#   Rcpp::Rcout << n << std::endl;
# 
# }')
# 
# lst <- list(a = 1:5, b = 2)
# 
# sf <- st_sf(a = c("x", "y","z"), geom = st_sfc(st_point(3:4), st_point(3:4), st_point(5:6)))
# sf[["geom2"]] = st_sfc(st_point(3:4), st_point(3:4), st_point(5:6))
# sf
# 
# listTest( sf[, c("geom")] )
# listTest( sf[, c("geom", "geom2")] )
# 
# sfc <- googlePolylines:::sfGeometryColumn(sf)
# listTest( sf[['geom']])
# listTest( sf[, c("geom", "geom2")])
# 
# listTest( lst )
# 
