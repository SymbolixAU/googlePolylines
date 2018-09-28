#include <Rcpp.h>
#include "googlePolylines.h"
#include "encode/encode.hpp"
#include "decode/decode.hpp"
#include "decode/decode_constructors.hpp"

using namespace Rcpp;

namespace googlepolylines {
namespace global_vars {
  std::vector<double> lons;
  std::vector<double> lats;
  std::string encodedString;
  std::vector<std::string> elems;
}
}

// [[Rcpp::export]]
Rcpp::List rcpp_decode_polyline_list( Rcpp::List encodedList, std::string attribute ) {

  // If the DIM is just Z or just M, should the result return a vector, rather than
  // a 2-column data.frame? 
  // probably
  
  size_t n = encodedList.size();
  Rcpp::List output(n);
  Rcpp::CharacterVector sfg_dim;
  std::vector<double> pointsLat;
  std::vector<double> pointsLon;
  std::vector<std::string> col_headers;
  
  for (size_t i = 0; i < n; i++) {
    
    Rcpp::StringVector polylines = encodedList[i];
    
    sfg_dim = polylines.attr( attribute );
    col_headers = googlepolylines::decodeconstuctors::get_col_headers(sfg_dim[0]);
    
    size_t pn = polylines.size();
    Rcpp::List polyline_output(pn);

    for (size_t j = 0; j < pn; j++ ) {
      
      // If polylines[j] is NA, assign a data frame of NA values
      if (Rcpp::StringVector::is_na(polylines[j])) {
        polyline_output[j] = googlepolylines::decodeconstuctors::na_dataframe(col_headers);
        continue;
      }
      
      Rcpp::StringVector sv(1);
      sv[0] = polylines[j];
      
      std::string s = Rcpp::as< std::string >(sv);
      polyline_output[j] = googlepolylines::decode::decode_polyline(s, col_headers, pointsLat, pointsLon);
    }
    output[i] = polyline_output;
  }
  return output;
  
}

// [[Rcpp::export]]
Rcpp::List rcpp_decode_polyline(Rcpp::StringVector encodedStrings, Rcpp::String encoded_type) {

  int encodedSize = encodedStrings.size();
  Rcpp::List results(encodedSize);
  std::vector<double> pointsLat;
  std::vector<double> pointsLon;
  std::vector<std::string> col_headers = googlepolylines::decodeconstuctors::get_col_headers(encoded_type);
  
  for(int i = 0; i < encodedSize; i++){
    
    // If encodedStrings[i] is NA, assign a data frame of NA values
    if (Rcpp::StringVector::is_na(encodedStrings[i])) {
      results[i] = googlepolylines::decodeconstuctors::na_dataframe(col_headers);
      continue;
    }
    
    std::string encoded = Rcpp::as< std::string >(encodedStrings[i]);
    
    Rcpp::List decoded = googlepolylines::decode::decode_polyline(encoded, col_headers, pointsLat, pointsLon);
    
    results[i] = decoded;
  }
  
  return results;
}







// [[Rcpp::export]]
std::string rcpp_encode_polyline(
    std::vector<double> longitude,
    std::vector<double> latitude
) {
  googlepolylines::global_vars::lons = longitude;
  googlepolylines::global_vars::lats = latitude;
  return googlepolylines::encode::encode_polyline();
}

// [[Rcpp::export]]
std::vector<std::string> rcpp_encode_polyline_byrow(
    Rcpp::NumericVector longitude,
    Rcpp::NumericVector latitude
  ) { 
  
  size_t n = longitude.length();
  std::vector<std::string> res;
  googlepolylines::global_vars::lons.clear();
  googlepolylines::global_vars::lons.resize(1);
  googlepolylines::global_vars::lats.clear();
  googlepolylines::global_vars::lats.resize(1);
  
  for ( size_t i = 0; i < n; i++ ) {

    googlepolylines::global_vars::lons[0] = longitude[i];
    googlepolylines::global_vars::lats[0] = latitude[i];

    res.push_back( googlepolylines::encode::encode_polyline() );
  }
  return res;
}

