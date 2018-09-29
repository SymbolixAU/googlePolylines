#ifndef GOOGLEPOLYLINES_WKT_H
#define GOOGLEPOLYLINES_WKT_H

// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/algorithm/string.hpp>
#include <boost/geometry.hpp>
#include "googlePolylines/utils/utils.hpp"

#define UNKNOWN           0
#define POINT             1
#define MULTIPOINT        2
#define LINESTRING        3
#define MULTILINESTRING   4
#define POLYGON           5
#define MULTIPOLYGON      6

namespace googlepolylines {
namespace wkt {

  inline void geom_type(const char *cls, int *tp = NULL) {
    
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


  // TODO( use the decoding code from decode.hpp )
  inline void polylineToWKT(std::ostringstream& os, std::string encoded){
    
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
      
      googlepolylines::utils::addLonLatToWKTStream(os, lng* (float)1e-5, lat* (float)1e-5);
      
      if(index < len) {
        googlepolylines::utils::coordSeparateWKT(os);
      }
    }
  }

  /**
   * Finds the 'GEOMETRY' text
   */
  inline std::string geomFromWKT(std::string& pl) {
    size_t s = pl.find_first_of("(");
    std::string geom = pl.substr(0, s);
    boost::trim(geom);
    
    return geom;
  }

} // namespace wkt
} // namespace googlepolylines

#endif
