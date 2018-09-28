
#include <Rcpp.h>

#include "googlePolylines.h"
#include "wkt/wkt.h"
#include "wkt/wkt_writers.hpp"
#include "boostgeometries.hpp"


// [[Rcpp::export]]
Rcpp::StringVector rcpp_polyline_to_wkt(Rcpp::List sfencoded) {
  
  unsigned int nrow = sfencoded.size();
  Rcpp::StringVector res(nrow);
  std::string stdspl;
  Rcpp::CharacterVector cls;
  Rcpp::StringVector pl;
  Rcpp::String spl;

  for (size_t i = 0; i < nrow; i++ ){
    
    std::ostringstream os;
    stdspl.clear();

    pl = sfencoded[i];

    if(!Rf_isNull(pl.attr("sfc"))){
      cls = pl.attr("sfc"); 
    }else{
      Rcpp::stop("No geometry attribute found");
    }

    googlepolylines::wktwriters::beginWKT(os, cls);
    unsigned int n =  pl.size();
  
    for(size_t j = 0; j < n; j ++ ) {
  
      spl = pl[j];
      
      if(spl == SPLIT_CHAR){
        os << "),(";
      }else{
        stdspl = spl;
        os << "(";
        googlepolylines::wkt::polylineToWKT(os, stdspl);
        os << ")";
        if(n > 1 && j < (n - 1)){
          if(pl[j+1] != SPLIT_CHAR){
            os << ",";
          }
        }
      }
      
    }
    
    googlepolylines::wktwriters::endWKT(os, cls);
    res[i] = os.str();
  }
  
  return res;
  
}

// [[Rcpp::export]]
Rcpp::List rcpp_wkt_to_polyline(Rcpp::StringVector wkt) {
  
  size_t n = wkt.length();
  Rcpp::String r_wkt;
  std::string str_wkt;
  std::string geomType;
  std::vector<std::string> cls;
  Rcpp::CharacterVector sv;
  
  Rcpp::List resultPolylines(n);
  int lastItem;
  unsigned int i;
  
  for (i = 0; i < n; i++ ) {
    
    std::ostringstream os;
    
    r_wkt = wkt[i];
    str_wkt = r_wkt;
    geomType = googlepolylines::wkt::geomFromWKT(str_wkt);
    
    
    cls.clear();
    cls.push_back("XY");
    cls.push_back(geomType);
    cls.push_back("sfg");
    
    //Rcpp::CharacterVector cls(1);
    //cls[0] = geomType;
    
    if (geomType == "POINT" ) {
      
      point_type pt;
      boost::geometry::read_wkt(str_wkt, pt);
      googlepolylines::boostgeometries::encode_wkt_point(pt, os);
      
    }else if (geomType == "MULTIPOINT" ) {
      
      multi_point_type mp;
      boost::geometry::read_wkt(str_wkt, mp);
      googlepolylines::boostgeometries::encode_wkt_multipoint(mp, os);
      
    }else if (geomType == "LINESTRING" ) {
      
      linestring_type ls;
      boost::geometry::read_wkt(str_wkt, ls);
      googlepolylines::boostgeometries::encode_wkt_linestring(ls, os);
      
    }else if (geomType == "MULTILINESTRING" ) {
      
      multi_linestring_type mls;
      boost::geometry::read_wkt(str_wkt, mls);
      googlepolylines::boostgeometries::encode_wkt_multi_linestring(mls, os);
      
    }else if (geomType == "POLYGON" ) { 
      
      polygon_type pl;
      boost::geometry::read_wkt(str_wkt, pl);
      googlepolylines::boostgeometries::encode_wkt_polygon(pl, os);
      
    }else if (geomType == "MULTIPOLYGON" ) {
      
      multi_polygon_type mpl;
      boost::geometry::read_wkt(str_wkt, mpl);
      googlepolylines::boostgeometries::encode_wkt_multi_polygon(mpl, os);
    }
    
    std::string str = os.str();
    googlepolylines::utils::split(str, ' ');
    
    if( googlepolylines::global_vars::elems.size() > 1 ) {
      lastItem = googlepolylines::global_vars::elems.size() - 1;
      
      if ( googlepolylines::global_vars::elems[lastItem] == "-") {
        googlepolylines::global_vars::elems.erase(googlepolylines::global_vars::elems.end() - 1 );
      }
    }
    
    sv = Rcpp::wrap( googlepolylines::global_vars::elems );
    sv.attr("sfc") = cls;
    resultPolylines[i] = sv;
  }
  
  return resultPolylines;
}







