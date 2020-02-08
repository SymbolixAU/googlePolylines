#ifndef R_GOOGLEPOLYLINES_DECODE_H
#define R_GOOGLEPOLYLINES_DECODE_H

namespace googlepolylines {
namespace decode {

  inline void decode(
      std::string& encoded,
      std::vector<double>& pointsLat, 
      std::vector<double>& pointsLon
  ) {
    
    R_xlen_t len = encoded.size();
    R_xlen_t index = 0;
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
  }

} // decode
} // googlepolylines

#endif