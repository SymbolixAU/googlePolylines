#ifndef GOOGLEPOLYLINES_UTILS_H
#define GOOGLEPOLYLINES_UTILS_H

#include "googlePolylines.h"
#include <Rcpp.h>

namespace googlepolylines {
namespace utils {

  template <int RTYPE>
  inline Rcpp::CharacterVector sfClass(Vector<RTYPE> v) {
    return v.attr("class");
  }
  
  inline Rcpp::CharacterVector getSfClass(SEXP sf) {
    
    switch( TYPEOF(sf) ) {
    case REALSXP: 
      return sfClass<REALSXP>(sf);
    case VECSXP: 
      return sfClass<VECSXP>(sf);
    case INTSXP: 
      return sfClass<INTSXP>(sf);
    default: Rcpp::stop("unknown sf type");
    }
    return "";
  }
  
  template<typename Out>
  inline void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      *(result++) = item;
    }
  }
  
  inline void split(const std::string &s, char delim) {
    global_vars::elems.clear();
    split(s, delim, std::back_inserter(global_vars::elems));
  }
  
  inline void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
    os << std::to_string(lon) << " " << std::to_string(lat);
  }
  
  inline void coordSeparateWKT(std::ostringstream& os) {
    os << ", ";
  }

}
} // namespace googlepolylines

#endif
