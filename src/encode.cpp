
#include "googlePolylines.h"
#include "encode/encode.hpp"
#include "encode/encode_writers.hpp"
#include "encode/encode_api.hpp"
#include "utils/utils.hpp"

#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::List rcpp_encodeSfGeometry(Rcpp::List sfc, bool strip) {
  return googlepolylines::encode_api::encodeSfGeometry( sfc, strip );
}