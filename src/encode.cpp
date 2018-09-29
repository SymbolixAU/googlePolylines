
#include "googlePolylines/googlePolylines.h"
#include "googlePolylines/encode/encode.hpp"
#include "googlePolylines/encode/encode_writers.hpp"
#include "googlePolylines/encode/encode_api.hpp"
#include "googlePolylines/utils/utils.hpp"

#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::List rcpp_encodeSfGeometry(Rcpp::List sfc, bool strip) {
  return googlepolylines::encode_api::encodeSfGeometry( sfc, strip );
}