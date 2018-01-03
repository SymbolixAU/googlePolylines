// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>
//#include <boost/geometry/geometries/point_xy.hpp>
//#include <boost/geometry/geometries/linestring.hpp>
//#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/variant/variant.hpp>
//#include <boost/variant.hpp>
//#include <boost/bind.hpp>

//#include <boost/geometry/io/wkt/read.hpp>
#include "wkt.h"
#include "variants.h"
#include "googlePolylines.h"

//#include <boost/foreach.hpp>

//#include <boost/function.hpp>

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

/*

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

*/
  
template <typename T, typename F>
double geometryFunction(T geom,  F geomFunc) {
  return geomFunc(geom);
}

/*
template <typename T, typename F>
geometryVariant geometryFunction(T geom1, T geom2,  F geomFunc) {
  return geomFunc(geom1, geom2);
}
*/

// [[Rcpp::export]]
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

// [[Rcpp::export]]
Rcpp::StringVector centroidTest(Rcpp::StringVector wkt ) {
  
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

// [[Rcpp::export]]
Rcpp::NumericVector polyline_algorithm(Rcpp::StringVector wkt, Rcpp::String algorithm) {

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

template <typename Point>
void encode_wkt_point(Point const& p, std::ostringstream& os) {

  Rcpp::NumericVector lon(1);
  Rcpp::NumericVector lat(1);
    
  lon[0] = bg::get<0>(p);
  lat[0] = bg::get<1>(p);

  addToStream(os, encode_polyline(lon, lat));
}


template <typename MultiPoint>
void encode_wkt_multipoint(MultiPoint const& mp, std::ostringstream& os) {
  
  typedef typename boost::range_iterator
    <
      multi_point_type const
    >::type iterator_type;
  
  for (iterator_type it = boost::begin(mp); 
       it != boost::end(mp);
       ++it) 
  {
    encode_wkt_point(*it, os);
  }
  
}

template <typename LineString>
void encode_wkt_linestring(LineString const& ls, std::ostringstream& os) {
  //std::cout << "num points: " << bg::num_points(ls) << std::endl;
  
  size_t n = bg::num_points(ls);
  Rcpp::NumericVector lon(n);
  Rcpp::NumericVector lat(n);
  
  typedef typename boost::range_iterator
    <
      linestring_type const
    >::type iterator_type;
  
  int i = 0;
  for (iterator_type it = boost::begin(ls);
       it != boost::end(ls);
       ++it)
  {
    lon[i] = bg::get<0>(*it);
    lat[i] = bg::get<1>(*it);
    i++;
    //std::cout << boost::geometry::get<0>(*it) << " " << boost::geometry::get<1>(*it) << std::endl;
  }
  
  addToStream(os, encode_polyline(lon, lat));
  
}

template <typename MultiLinestring>
void encode_wkt_multi_linestring(MultiLinestring const& mls, std::ostringstream& os) {
  
  size_t n = bg::num_geometries(mls);
  std::cout << n << std::endl;
  
  typedef typename boost::range_iterator
    <
      multi_linestring_type const
    >::type iterator_type;
  
  for (iterator_type it = boost::begin(mls);
       it != boost::end(mls);
       ++it)
  {
    //std::cout << bg::wkt(*it) << std::endl;
    encode_wkt_linestring(*it, os);
  }
  
}


// [[Rcpp::export]]
Rcpp::List parseWkt(Rcpp::StringVector wkt) {
  
  size_t n = wkt.length();
  Rcpp::String r_wkt;
  std::string str_wkt;
  std::string geomType;
  
  Rcpp::CharacterVector cls(3);
  
  Rcpp::List resultPolylines(n);
  int lastItem;
  
  for (int i = 0; i < n; i++ ) {
    
    std::ostringstream os;
    
    r_wkt = wkt[i];
    str_wkt = r_wkt;
    geomType = geomFromWKT(str_wkt);
    
    cls[0] = "XY";
    cls[1] = geomType;
    cls[2] = "sfg";
    
    if (geomType == "POINT" ) {
      
      point_type pt;
      bg::read_wkt(str_wkt, pt);
      encode_wkt_point(pt, os);
      
    }else if (geomType == "MULTIPOINT" ) {
      
      multi_point_type mp;
      bg::read_wkt(str_wkt, mp);
      encode_wkt_multipoint(mp, os);
      
    }else if (geomType == "LINESTRING" ) {
      
      linestring_type ls;
      bg::read_wkt(str_wkt, ls);
      encode_wkt_linestring(ls, os);
      
    }else if (geomType == "MULTILINESTRING" ) {
      
      multi_linestring_type mls;
      bg::read_wkt(str_wkt, mls);
      encode_wkt_multi_linestring(mls, os);
      
    }
//    std::cout << geomType << std::endl;
  // create Rcpp::StringVector polylines; inside each encode_wkt_*** function
    
    
    std::string str = os.str();
    //std::cout << str << std::endl;
    std::vector<std::string> strs = split(str, ' ');;
    
    if(strs.size() > 1) {
      lastItem = strs.size() - 1;
      
      if (strs[lastItem] == "-") {
        strs.erase(strs.end() - 1);
      }
    }
    
    Rcpp::CharacterVector sv = wrap(strs);
    resultPolylines[i] = sv;
  }
  
  /*
  // IF POINT: encode lon & lat
  point_type g;
  bg::read_wkt("POINT(1 1)", g);
  
  using boost::geometry::get;
  std::cout << "x: " << get<0>(g) << std::endl;
  
  // IF MULTIPOINT: encode multiple lon & lats
  multi_point_type mp;
  bg::read_wkt("MULTIPOINT((0 0),(1 1),(2 2))", mp);
  bg::for_each_point(
    g,
    encode_wkt_point<point_type>
    //list_coordinates<point_type>
  );
  */
  
  return resultPolylines;
  
}







