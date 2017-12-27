#include <Rcpp.h>
#include "googleWKT.h"
#include "googlePolylines.h"

using namespace Rcpp;

// POINT (x y)
// MULTIPOINT ((x y), (a b))
// LINESTRING (a b, x y, j k)
// MULTILINESTRING ((a b, x y, j k), (a b, x y, j k))

// DECODE -> WKT
// - get TYPE
// - add to stream
// - decode coordinates (to numeric matrix?) (or, create a 'decode' methdo that goes to WKT point?)
void addLonLatToWKTStream(std::ostringstream& os, Rcpp::String lon, Rcpp::String lat ) {
  
  // add coordinates, separated by a space
  std::string slon = lon;
  std::string slat = lat;
  os << slon << " " << slat;
  
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
  
  switch( tp ) {
  case POINT:
    os << "POINT(";
    break;
  case MULTIPOINT:
    os << "MULTIPOINT((";
    break;
  case LINESTRING:
    os << "LINESTRING(";
    break;
  case MULTILINESTRING:
    os << "MULTILINESTRING((";
    break;
  case POLYGON:
    os << "POLYGON((";
    break;
  case MULTIPOLYGON:
    os << "MULTIPOLYGON(((";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void endWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
  
  int tp;
  geom_type(cls[1], &tp);
  
  switch( tp ) {
  case POINT:
    os << ")";
    break;
  case MULTIPOINT:
    os << "))";
    break;
  case LINESTRING:
    os << ")";
    break;
  case MULTILINESTRING:
    os << "))";
    break;
  case POLYGON:
    os << "))";
    break;
  case MULTIPOLYGON:
    os << ")))";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void coordSeparateWKT(std::ostringstream& os) {
  os << ", ";
}

// TODO:
// - user can specify geometry type
// - if not supplied, assume LINESTRING / MULTILINESTRING 
// - if from sfencoded - read the attributes

// - different beginnings based on the geometry -> POLYGON((, LINESTRING(, POINT(, MULTIPOINT((, MULTILINESTRING((, 
// - SPLIT_CHAR -> the beginning of a new polygon (in a MULTIPOLYGON)

// [[Rcpp::export]]
Rcpp::String polyline_to_wkt(Rcpp::List sfencoded) {
  
  Rcpp::Rcout << sfencoded.size() << std::endl;
  std::ostringstream os;
  Rcpp::String wkt;
  
  Rcpp::StringVector pl = sfencoded[0];
  Rcpp::CharacterVector cls = pl.attr("sfc");
  
  beginWKT(os, cls);
  int n =  pl.size();

  for(size_t i = 0; i < n; i ++ ) {
    
    // for each set of coordiantes, they need to be split by "),(",
    // unless it's a new polygon, where it needs ")), ((" 
    // which is denoted by the SPLIT_CHAR
    Rcpp::String spl = pl[i];
    
    if(spl == SPLIT_CHAR){
      os << ")),((";
    }else{
      std::string stdspl = spl;
      polylineToWKT(os, stdspl);
      if (i < (n-1)){
        os << "),(";
      }
    }
    
  }
  endWKT(os, cls);
  
  wkt = os.str();
  return wkt;
  
}


void polylineToWKT(std::ostringstream& os, std::string encoded){
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
  while (index < len){
    char b;
    int shift = 0;
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
    
    addLonLatToWKTStream(os, lng, lat);
    if(index < len) {
      coordSeparateWKT(os);
//    }else{
//      endWKT(os, cls);
    }
  }
}










