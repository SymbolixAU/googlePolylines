// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
//#include <boost/geometry/io/wkt/read.hpp>
#include "wkt.h"

#include <boost/function.hpp>

namespace bg = boost::geometry;
namespace bgm = bg::model;

// TODO:
// - other algorithms: http://www.boost.org/doc/libs/1_66_0/libs/geometry/doc/html/geometry/reference/algorithms.html
//
// - correct for polygon ring direction? (outer == clockwise, holes == counter-clockwise)
// -- we could leave this up to the user for now, and assume the rings are oriented correctly
// -- or should the user conform from the outset? (and use http://www.boost.org/doc/libs/1_47_0/libs/geometry/doc/html/geometry/reference/algorithms/correct.html)
//
// - specify units / CRS ? 



typedef bg::model::d2::point_xy<double> point_type;
//typedef bg::model::point <double , 2, bg::cs::geographic<bg::degree> > point_type;
//typedef bg::model::point <double , 2, bg::cs::spherical_equatorial<bg::degree> > point_type;
typedef bgm::multi_point<point_type> multi_point_type;
typedef bgm::linestring<point_type> linestring_type;
typedef bgm::multi_linestring<linestring_type> multi_linestring_type;
typedef bgm::polygon<point_type> polygon_type;
typedef bgm::multi_polygon<polygon_type> multi_polygon_type;


typedef boost::variant
  <
    point_type,
    multi_point_type,
    linestring_type,
    multi_linestring_type,
    polygon_type,
    multi_polygon_type
  > 
  geometryVariant;

typedef boost::variant
  <
    linestring_type,
    multi_linestring_type,
    polygon_type,
    multi_polygon_type
  >
  geometryIntersection;

// https://stackoverflow.com/a/48045800/4002530
struct {
  using result_type = bool;
  
  template <typename... T>
  bool operator()(std::string const& wkt, boost::variant<T...>& geo) const {
    return boost::apply_visitor(boost::bind(*this, boost::ref(wkt), _1), geo);
  }
  
  template <typename Geo>
  bool operator()(std::string const& wkt, Geo& geo) const {
    try {
      bg::read_wkt(wkt, geo);
      return true;
    } catch(bg::read_wkt_exception const& cant) {
      return false;
    }
  }
  
} read_wkt;

geometryVariant read_any_wkt(std::string const& wkt) {
  { point_type            tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { multi_point_type      tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { linestring_type       tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { multi_linestring_type tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { polygon_type          tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { multi_polygon_type    tmp; if (read_wkt(wkt, tmp)) return tmp; }
  throw bg::read_wkt_exception("read_any_wkt failed", wkt);
}

geometryIntersection read_intersection_wkt(std::string const& wkt) {
//  { point_type            tmp; if (read_wkt(wkt, tmp)) return tmp; }
//  { multi_point_type      tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { linestring_type       tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { multi_linestring_type tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { polygon_type          tmp; if (read_wkt(wkt, tmp)) return tmp; }
  { multi_polygon_type    tmp; if (read_wkt(wkt, tmp)) return tmp; }
  throw bg::read_wkt_exception("read_any_wkt failed", wkt);
}

template <typename T, typename F>
double geometryFunction(T geom,  F geomFunc) {
  return geomFunc(geom);
}


template <typename T, typename F>
geometryVariant geometryFunction(T geom1, T geom2,  F geomFunc) {
  return geomFunc(geom1, geom2);
}


// [[Rcpp::export]]
void intersectionTest() { 
  
  std::string wkt1 = "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
  "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))";
  std::string wkt2 = "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5))";
  
  std::string wkt3 = "LINESTRING(4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5)";
  
  std::string wkt4 = "MULTIPOLYGON(((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5)))";
  
  geometryIntersection gv1;
  gv1 = read_intersection_wkt(wkt1);

  geometryIntersection gv2;
  gv2 = read_intersection_wkt(wkt2);
  
  geometryIntersection gv3;
  gv3 = read_intersection_wkt(wkt3);
  
  geometryIntersection gv4;
  gv4 = read_intersection_wkt(wkt4);
  
  multi_linestring_type output;
  //multi_polygon_type output;
  //geometryFunction(gv1, gv2, bg::intersection<geometryVariant>);
  bg::intersection(gv1, gv4, output);
  
  BOOST_FOREACH(geometryIntersection const& p, output) {
    std::cout << bg::wkt(p) << std::endl;
  }

  
}

// [[Rcpp::export]]
Rcpp::NumericVector polyline_algorithm(Rcpp::StringVector wkt, Rcpp::String algorithm) {

  Rcpp::NumericVector result(wkt.length());
  std::string s_wkt;
  Rcpp::String i_wkt;
  geometryVariant gv;

  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;
    
    gv = read_any_wkt(s_wkt);
    if(algorithm == "length") { 
      result[i] = geometryFunction(gv, bg::length<geometryVariant>);
    }else if(algorithm == "area") {
      result[i] = geometryFunction(gv, bg::area<geometryVariant>);
    }
  }
  return result;
}
