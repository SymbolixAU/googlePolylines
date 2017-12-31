// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/variant/variant.hpp>
//#include <boost/geometry/io/wkt/read.hpp>
#include "wkt.h"

#include <boost/function.hpp>

namespace geom = boost::geometry;

typedef geom::model::d2::point_xy<double> point_type;
//typedef geom::model::point <double , 2, geom::cs::geographic<geom::degree> > point_type;
//typedef geom::model::point <double , 2, geom::cs::spherical_equatorial<geom::degree> > point_type;
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
  geometryVariant;
 */

// TODO:
// - distance
// - area

// methods:
// - each row of sfobj, 
// -- getGeomType
// -- calc 


//https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c

template <typename T, typename F>
T myFunction(T geom, F geomFunc) {
  return geomFunc(geom);
}


// [[Rcpp::export]]
Rcpp::NumericVector polyline_length(Rcpp::StringVector wkt) {

  Rcpp::NumericVector resultLength(wkt.length());
  std::string geometry;
  std::string s_wkt;
  Rcpp::String i_wkt;

  for (size_t i = 0; i < wkt.size(); i++ ) {
    i_wkt = wkt[i];
    s_wkt = i_wkt;

    geometry = geomFromWKT(s_wkt);

    if (geometry == "LINESTRING") {
      
      geom::model::linestring<point_type> g;
      geom::read_wkt(s_wkt, g);
      resultLength[i] = geom::length(g);
      
    }else if( geometry == "MULTILINESTRING") {
      
      geom::model::multi_linestring<linestring_type> g;
      geom::read_wkt(s_wkt, g);
      resultLength[i] = geom::length(g);

    }else{
      resultLength[i] = NA_REAL;
    }
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
      
      geom::model::polygon<point_type> g;
      geom::read_wkt(s_wkt, g);
      resultArea[i] = geom::length(g);
      
    }else if( geometry == "MULTIPOLYGON") {
      
      geom::model::multi_polygon<polygon_type> g;
      geom::read_wkt(s_wkt, g);
      resultArea[i] = geom::length(g);
      
    }else{
      resultArea[i] = NA_REAL;
    }
  }
  return resultArea;
}


