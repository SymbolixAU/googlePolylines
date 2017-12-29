// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/variant/variant.hpp>
#include "wkt.h"

namespace geom = boost::geometry;

typedef geom::model::d2::point_xy<double> point_type;
typedef geom::model::multi_point<point_type> multi_point_type;
typedef geom::model::linestring<point_type> linestring_type;
typedef geom::model::multi_linestring<linestring_type> multi_linestring_type;
typedef geom::model::polygon<point_type> polygon_type;
typedef geom::model::multi_polygon<polygon_type> multi_polygon_type;

/*
typedef boost::variant
  <
    point_type,
    multi_point_type,
    linestring_type,
    multi_linestring_type,
    polygon_type,
    multi_polygon_type
  > 
  geometry;
*/
// TODO:
// - distance
// - area

// methods:
// - each row of sfobj, 
// -- getGeomType
// -- calc 

// [[Rcpp::export]]
void polyline_distance(Rcpp::StringVector wkt) {
  
//  geom::model::polygon<point_type> ply;
//  geom::model::multi_polygon<polygon_type> mp;
  
//  Rcpp::NumericVector wktDistance(wkt.length());
  
  std::string geometry;
  
  Rcpp::Rcout << "size: " << wkt.size() << std::endl;
  
  //geometry g;
  for (size_t i = 0; i < wkt.size(); i++ ) {
    Rcpp::String rs = wkt[i];
    std::string s = rs;
//    Rcpp::Rcout << wkt[i] << std::endl;
    
    geometry = geomFromWKT(s);
    Rcpp::Rcout << "geom: " << geometry << std::endl;
  }
  
  
}




