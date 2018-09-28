
// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/algorithm/string.hpp>
#include <boost/geometry.hpp>

#include "wkt.h"
#include "googlePolylines.h"
#include "variants.h"

using namespace Rcpp;
namespace bg = boost::geometry;
namespace bgm = bg::model;

void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
  os << std::to_string(lon) << " " << std::to_string(lat);
}

void geom_type(const char *cls, int *tp = NULL) {
  
  int type = 0;
  if (strcmp(cls, "POINT") == 0)
    type = POINT;
  else if (strcmp(cls, "MULTIPOINT") == 0)
    type = MULTIPOINT;
  else if (strcmp(cls, "LINESTRING") == 0)
    type = LINESTRING;
  else if (strcmp(cls, "POLYGON") == 0)
    type = POLYGON;
  else if (strcmp(cls, "MULTILINESTRING") == 0)
    type = MULTILINESTRING;
  else if (strcmp(cls, "MULTIPOLYGON") == 0)
    type = MULTIPOLYGON;
  else
    type = UNKNOWN;
  if (tp != NULL)
    *tp = type;
}

void beginWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
  
  int tp;
  geom_type(cls[1], &tp);
  //geom_type(cls[0], &tp);  // iff removing XY and sfg attributs
  
  switch( tp ) {
  case POINT:
    os << "POINT ";
    break;
  case MULTIPOINT:
    os << "MULTIPOINT (";
    break;
  case LINESTRING:
    os << "LINESTRING ";
    break;
  case MULTILINESTRING:
    os << "MULTILINESTRING (";
    break;
  case POLYGON:
    os << "POLYGON (";
    break;
  case MULTIPOLYGON:
    os << "MULTIPOLYGON ((";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void endWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
  
  int tp;
  geom_type(cls[1], &tp);
  //geom_type(cls[0], &tp);
  
  switch( tp ) {
  case POINT:
    os << "";
    break;
  case MULTIPOINT:
    os << ")";
    break;
  case LINESTRING:
    os << "";
    break;
  case MULTILINESTRING:
    os << ")";
    break;
  case POLYGON:
    os << ")";
    break;
  case MULTIPOLYGON:
    os << "))";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void coordSeparateWKT(std::ostringstream& os) {
  os << ", ";
}

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

    beginWKT(os, cls);
    unsigned int n =  pl.size();
  
    for(size_t j = 0; j < n; j ++ ) {
  
      spl = pl[j];
      
      if(spl == SPLIT_CHAR){
        os << "),(";
      }else{
        stdspl = spl;
        os << "(";
        polylineToWKT(os, stdspl);
        os << ")";
        if(n > 1 && j < (n - 1)){
          if(pl[j+1] != SPLIT_CHAR){
            os << ",";
          }
        }
      }
      
    }
    endWKT(os, cls);
    res[i] = os.str();
  }
  
  return res;
  
}


void polylineToWKT(std::ostringstream& os, std::string encoded){
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
  while (index < len){
    char b;
    unsigned int shift = 0;
    int result = 0;
    do {
      b = encoded.at(index++) - 63;
      result |= (b & 0x1f) << shift;
      shift += 5;
    } while (b >= 0x20);
    float dlat = ((result & 1) ? ~(result >> 1) : (result >> 1));
    lat += dlat;
    
    shift = 0;
    result = 0;
    do {
      b = encoded.at(index++) - 63;
      result |= (b & 0x1f) << shift;
      shift += 5;
    } while (b >= 0x20);
    float dlng = ((result & 1) ? ~(result >> 1) : (result >> 1));
    lng += dlng;

    addLonLatToWKTStream(os, lng* (float)1e-5, lat* (float)1e-5);
    
    if(index < len) {
      coordSeparateWKT(os);
    }
  }
}


/*
void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}
*/

/**
 * Finds the 'GEOMETRY' text
 */
std::string geomFromWKT(std::string& pl) {
  size_t s = pl.find_first_of("(");
  std::string geom = pl.substr(0, s);
  boost::trim(geom);
//  pl.replace(0, s, "");
  
  return geom;
}

template <typename Point>
void encode_wkt_point(Point const& p, std::ostringstream& os) {
  
  global_vars::lons.clear();
  global_vars::lats.clear();

  global_vars::lons.push_back(bg::get<0>(p));
  global_vars::lats.push_back(bg::get<1>(p));
  
  global_vars::encodedString = encode_polyline();
  
  addToStream(os);
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
  
  // works for RINGS (because it's templated)
  
  typedef typename boost::range_iterator
    <
      linestring_type const
    >::type iterator_type;
  
  int i = 0;
  for (iterator_type it = boost::begin(ls);
       it != boost::end(ls);
       ++it)
  {
    global_vars::lons.push_back(bg::get<0>(*it));
    global_vars::lats.push_back(bg::get<1>(*it));
    i++;
  }
  global_vars::encodedString = encode_polyline();
  addToStream(os);
}

template <typename MultiLinestring>
void encode_wkt_multi_linestring(MultiLinestring const& mls, std::ostringstream& os) {
  
  typedef typename boost::range_iterator
  <
    multi_linestring_type const
  >::type iterator_type;
  
  for (iterator_type it = boost::begin(mls);
       it != boost::end(mls);
       ++it)
  {
    encode_wkt_linestring(*it, os);
  }
}

template <typename Polygon>
void encode_wkt_polygon(Polygon const& pl, std::ostringstream& os) {
  
  encode_wkt_linestring(pl.outer(), os);
  
  // perhaps use
  // https://stackoverflow.com/questions/7722087/getting-the-coordinates-of-points-from-a-boost-geometry-polygon/7748091#7748091
  // https://stackoverflow.com/questions/37071031/how-to-get-a-polygon-from-boostgeometrymodelpolygon
  for (auto& i: pl.inners() ) {
    encode_wkt_linestring(i, os);
  }
}

template <typename MultiPolygon>
void encode_wkt_multi_polygon(MultiPolygon const& mpl, std::ostringstream& os) {
  
  typedef typename boost::range_iterator
  <
    multi_polygon_type const
  >::type iterator_type;
  
  global_vars::encodedString = SPLIT_CHAR;
  for (iterator_type it = boost::begin(mpl);
       it != boost::end(mpl);
       ++it)
  {
    encode_wkt_polygon(*it, os);
    addToStream(os);
  }
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
    geomType = geomFromWKT(str_wkt);
    
    
    cls.clear();
    cls.push_back("XY");
    cls.push_back(geomType);
    cls.push_back("sfg");
    
    //Rcpp::CharacterVector cls(1);
    //cls[0] = geomType;
    
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
      
    }else if (geomType == "POLYGON" ) { 
      
      polygon_type pl;
      bg::read_wkt(str_wkt, pl);
      encode_wkt_polygon(pl, os);
      
    }else if (geomType == "MULTIPOLYGON" ) {
      
      multi_polygon_type mpl;
      bg::read_wkt(str_wkt, mpl);
      encode_wkt_multi_polygon(mpl, os);
    }
    
    std::string str = os.str();
    split(str, ' ');
    
    if(global_vars::elems.size() > 1) {
      lastItem = global_vars::elems.size() - 1;
      
      if (global_vars::elems[lastItem] == "-") {
        global_vars::elems.erase(global_vars::elems.end() - 1);
      }
    }
    
    sv = wrap(global_vars::elems);
    sv.attr("sfc") = cls;
    resultPolylines[i] = sv;
  }
  
  return resultPolylines;
}







