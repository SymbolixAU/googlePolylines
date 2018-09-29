#ifndef GOOGLEPOLYLINES_DECODE_H
#define GOOGLEPOLYLINES_DECODE_H

#include <Rcpp.h>

namespace googlepolylines { 
namespace decode {

  inline Rcpp::List decode_polyline(std::string encoded, 
                             std::vector<std::string>& col_headers, 
                             std::vector<double>& pointsLat, 
                             std::vector<double>& pointsLon) {
    
    int len = encoded.size();
    int index = 0;
    float lat = 0;
    float lng = 0;
    
    pointsLat.clear();
    pointsLon.clear();
    
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
      
      pointsLat.push_back(lat * (float)1e-5);
      pointsLon.push_back(lng * (float)1e-5);
    }
    
    //TODO(ZM attributes)
    
    // Create List output that has the necessary attributes to make it a 
    // data.frame object.
    Rcpp::List out = Rcpp::List::create(
      Rcpp::Named(col_headers[0]) = pointsLat, 
      Rcpp::Named(col_headers[1]) = pointsLon
    );
    
    out.attr("class") = "data.frame";
    out.attr("row.names") = Rcpp::seq(1, pointsLat.size());
    
    return out;
  }

} // namespace decode
} // namespace googlepolylines


#endif