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
//#include <boost/geometry/io/wkt/read.hpp>
#include "wkt.h"

#include <boost/function.hpp>

namespace bg = boost::geometry;
namespace bgm = bg::model;

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

template <typename T, typename F>
double geometryFunction(T geom,  F geomFunc) {
  return geomFunc(geom);
}


template <typename T, typename F>
double geometryFunction(T geom1, T geom2,  F geomFunc) {
  return geomFunc(geom1, geom2);
}

/*
void geometryType(const char *geom, int *geomType = NULL) {
  
  int type = 0;
  
  if(strcmp(geom, "POINT") == 0) {
    type = POINT;
  }else if(strcmp(geom, "MULTIPOINT") == 0) {
    type = MULTIPOINT;
  }else if(strcmp(geom, "LINESTRING") == 0) {
    type = LINESTRING;
  }else if(strcmp(geom, "MULTILINESTRING") == 0) {
    type = MULTILINESTRING;
  }else if(strcmp(geom, "POLYGON") == 0) {
    type = POLYGON;
  }else if(strcmp(geom, "MULTIPOLYGON") == 0) {
    type = MULTIPOLYGON;
  }else{
    type = UNKNOWN;
  }
  *geomType = type;
}
*/

template <typename T, typename F>
geometryVariant getGeometry(T wkt, F geomFunc) {
  
  //int geomType;
  
  //geometryVariant gv;
  
  //std::string geometry = geomFromWKT(wkt);
  
  //geometryType(geometry.c_str(), &geomType);
  
  //Rcpp::Rcout << "geom: " << geometry << std::endl;
  //Rcpp::Rcout << "geomType: " << geomType << std::endl;
  
  //auto any = read_any_wkt(wkt);
  //return any;
  //std::cout << "read_any_wkt: " << bg::wkt(any) << "\n";
  
  //std::cout << "any length: " << geomFunc(any) << "\n";
  
  /*
  switch(geomType) {
  case POINT:
    
  }

  if (geometry == "POINT") {
    
    //geometryVariant g;
    bgm::d2::point_xy<double> pt;
    bg::read_wkt(wkt, pt);
    
  }else if (geometry == "MULTIPOINT" ) {
    //geometryVariant g;
    bgm::multi_point<point_type> mpt;
    bg::read_wkt(wkt, mpt);
    
  }else if (geometry == "LINESTRING" ) {
    //geometryVariant g;
    Rcpp::Rcout << wkt << std::endl;

    bgm::linestring<point_type> ls;
    bg::read_wkt(wkt, ls);
    
    std::cout << "linestring: " << geomFunc(ls) << std::endl;
    
  }else if (geometry == "MULTILINESTRING" ) {
    //geometryVariant g;
    bgm::multi_linestring<linestring_type> mls;
    bg::read_wkt(wkt, mls);
    
  }else if (geometry == "POLYGON" ) {
    //geometryVariant g;
    bgm::polygon<point_type> p;
    bg::read_wkt(wkt, p)
      ;
  }else if (geometry == "MULTIPOLYGON" ) {
    //geometryVariant g;
    bgm::multi_polygon<polygon_type> mp;
    bg::read_wkt(wkt, mp);
    
  }else{
    Rcpp::stop("unknown geometry type");
  }
  return gv;
  */
}

/*
void lineTest() {
  std::string wkt = "LINESTRING(0 0, 1 1, 2 2, 3 3)";
  geometryVariant g = getGeometry(wkt);
  
}
*/
// [[Rcpp::export]]
Rcpp::NumericVector polyline_length(Rcpp::StringVector wkt) {

  Rcpp::NumericVector resultLength(wkt.length());
  std::string geometry;
  std::string s_wkt;
  Rcpp::String i_wkt;
  geometryVariant gv;

  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;
    
    gv = read_any_wkt(s_wkt);
//    gv = getGeometry(s_wkt, bg::length<geometryVariant>);
    resultLength[i] = geometryFunction(gv, bg::length<geometryVariant>);
    /*

    geometry = geomFromWKT(s_wkt);

    if (geometry == "LINESTRING") {
      
      bg::model::linestring<point_type> g;
      bg::read_wkt(s_wkt, g);

      resultLength[i] = geometryFunction(g, boost::geometry::length<geometryVariant>);
      
    }else if( geometry == "MULTILINESTRING") {
      
      bg::model::multi_linestring<linestring_type> g;
      bg::read_wkt(s_wkt, g);
      
      resultLength[i] = geometryFunction(g, boost::geometry::length<geometryVariant>);

    }else{
      resultLength[i] = NA_REAL;
    }
     
     */
  }
  return resultLength;
}

// [[Rcpp::export]]
Rcpp::NumericVector polyline_area(Rcpp::StringVector wkt) {
  
  Rcpp::NumericVector resultArea(wkt.length());
  std::string geometry;
  std::string s_wkt;
  Rcpp::String i_wkt;
  
  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;
    
    geometry = geomFromWKT(s_wkt);
    
    if (geometry == "POLYGON") {
      
      bgm::polygon<point_type> g;
      bg::read_wkt(s_wkt, g);
      resultArea[i] = bg::area(g);
      
    }else if( geometry == "MULTIPOLYGON") {
      
      bgm::multi_polygon<polygon_type> g;
      bg::read_wkt(s_wkt, g);
      resultArea[i] = bg::area(g);
      
    }else{
      resultArea[i] = NA_REAL;
    }
  }
  return resultArea;
}


