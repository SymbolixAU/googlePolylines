// [[Rcpp::depends(BH)]]

/*
#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>

#include "wkt.h"
#include "variants.h"
#include "googlePolylines.h"

namespace bg = boost::geometry;
namespace bgm = bg::model;
*/
 
// TODO:
// - other algorithms: http://www.boost.org/doc/libs/1_66_0/libs/geometry/doc/html/geometry/reference/algorithms.html
//
// - correct for polygon ring direction? (outer == clockwise, holes == counter-clockwise)
// -- we could leave this up to the user for now, and assume the rings are oriented correctly
// -- or should the user conform from the outset? (and use http://www.boost.org/doc/libs/1_47_0/libs/geometry/doc/html/geometry/reference/algorithms/correct.html)
//
// - specify units / CRS ? 

/*
template <typename T, typename F>
double geometryFunction(T geom,  F geomFunc) {
  return geomFunc(geom);
}
*/

/*
void intersectionTest() { 
  
  std::string wkt1 = "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
  "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))";
  std::string wkt2 = "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5))";
  
  std::string wkt3 = "LINESTRING(4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5)";
  
  std::string wkt4 = "MULTIPOLYGON(((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5)))";
  
  
  GeoIntersection gv1;
  gv1 = read_intersection_wkt(wkt1);

  GeoIntersection gv2;
  gv2 = read_intersection_wkt(wkt2);
  
  GeoIntersection gv3;
  gv3 = read_intersection_wkt(wkt3);
  
  GeoIntersection gv4;
  gv4 = read_intersection_wkt(wkt4);
  
  //std::vector<multi_linestring_type> output;
  //std::deque<linestring_type> output;
  //GeoIntersectionOutput output;
  multi_linestring_type output;
  //multi_polygon_type output;
  //geometryFunction(gv1, gv2, bg::intersection<geometryVariant>);
  bg::intersection(gv1, gv4, output);
  
  std::cout << bg::wkt(output) << std::endl;
  
//  BOOST_FOREACH(AnyGeo const& p, output) {
//    std::cout << bg::wkt(p) << std::endl;
//  }
}
*/

/*
// [[Rcpp::export]]
Rcpp::StringVector rcpp_polyline_centroid(Rcpp::StringVector wkt ) {
  
  Rcpp::StringVector result(wkt.length());
  
  std::string s_wkt;
  Rcpp::String i_wkt;

  AnyGeo g;
  point_type p;
  
  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;
    std::stringstream ss;
    
    g = read_any_wkt(s_wkt);
    bg::centroid(g, p);
    ss << bg::wkt(p);
    result[i] = ss.str();

  }
  return result;
}
*/

/*
// [[Rcpp::export]]
Rcpp::NumericVector rcpp_polyline_algorithm(Rcpp::StringVector wkt, Rcpp::String algorithm) {

  Rcpp::NumericVector result(wkt.length());
  std::string s_wkt;
  Rcpp::String i_wkt;
  //geometryVariant gv;

  AnyGeo g;
  
  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;
    
    g = read_any_wkt(s_wkt);
    
    //gv = read_any_wkt(s_wkt);
    if(algorithm == "length") { 
      result[i] = geometryFunction(g, bg::length<AnyGeo>);
    }else if(algorithm == "area") {
      result[i] = geometryFunction(g, bg::area<AnyGeo>);
    }
  }
  return result;
}
*/







