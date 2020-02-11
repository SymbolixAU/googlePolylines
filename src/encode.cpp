#include <Rcpp.h>

//#include "googlepolylines/sf.hpp"
#include "googlePolylines.h"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "googlepolylines/encode.hpp"


template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

void split(const std::string &s, char delim) {
  global_vars::elems.clear();
  split(s, delim, std::back_inserter(global_vars::elems));
}

void addToStream(std::ostringstream& os) {
  os << global_vars::encodedString << ' ';
}



// [[Rcpp::export]]
Rcpp::List rcpp_encode_sfc(
    Rcpp::List& sfc,
    bool strip
) {
  return googlepolylines::encode::encode_sfc( sfc, strip );
}

