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

void beginWKT(std::ostringstream& os, Rcpp::String geom) {
  std::string sgeom = geom;
  os << sgeom << "(";
}

// TODO:
// - user can specify geometry type
// - if not supplied, assume LINESTRING / MULTILINESTRING 
// - if from sfencoded - read the attributes

// 

// [[Rcpp::export]]
Rcpp::String polyline_to_wkt(Rcpp::List sfencoded) {
  
  Rcpp::Rcout << sfencoded.size() << std::endl;
  std::ostringstream os;
  
  Rcpp::StringVector pl = sfencoded[0];
  Rcpp::CharacterVector cls = pl.attr("sfc");
  beginWKT(os, cls[1]);

  Rcpp::String wkt;
  
  for(size_t i = 0; i < pl.size(); i ++ ) {
    Rcpp::String spl = pl[i];
    std::string stdspl = spl;
    polylineToWKT(os, stdspl);
  }
  
  wkt = os.str();
  return wkt;
  
}


void polylineToWKT(std::ostringstream& os, std::string encoded){
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
//  std::ostringstream os;
  Rcpp::String wkt;
  
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
  }
}










