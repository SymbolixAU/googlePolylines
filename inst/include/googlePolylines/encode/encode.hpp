#ifndef GOOGLEPOLYLINES_ENCODE_H
#define GOOGLEPOLYLINES_ENCODE_H

#include <Rcpp.h>
#include "googlePolylines/googlePolylines.h"

namespace googlepolylines {
namespace encode {

  inline void EncodeNumber(std::ostringstream& os, int num) {
    
    std::string out_str;
    
    while(num >= 0x20){
      out_str += (char)(0x20 | (int)(num & 0x1f)) + 63;
      num >>= 5;
    }
    
    out_str += char(num + 63);
    os << out_str;
  }

  inline void EncodeSignedNumber(std::ostringstream& os, int num) {
    
    unsigned int ui = num;      //3
    ui <<= 1;                   //4
    ui = (num < 0) ? ~ui : ui;  //5
    EncodeNumber(os, ui);
  }

  inline std::string encode_polyline() {
    
    int plat = 0;
    int plon = 0;
    int late5;
    int lone5;
    
    std::ostringstream os;
    
    for(unsigned int i = 0; i < googlepolylines::global_vars::lats.size(); i++) {
      
      late5 = googlepolylines::global_vars::lats[i] * 1e5;
      lone5 = googlepolylines::global_vars::lons[i] * 1e5;
      
      EncodeSignedNumber(os, late5 - plat);
      EncodeSignedNumber(os, lone5 - plon);
      
      plat = late5;
      plon = lone5;
    }
    
    return os.str();
  }

} // namespace encode
} // namespace googlepolylines


#endif