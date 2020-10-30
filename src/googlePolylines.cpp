#include <Rcpp.h>
#include "googlePolylines.h"

using namespace Rcpp;

namespace global_vars {
  std::vector<double> lons;
  std::vector<double> lats;
  std::string encodedString;
  std::vector<std::string> elems;
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
    col_headers = get_col_headers(sfg_dim[0]);
    
    size_t pn = polylines.size();
    Rcpp::List polyline_output(pn);

    for (size_t j = 0; j < pn; j++ ) {
      
      // If polylines[j] is NA, assign a data frame of NA values
      if (Rcpp::StringVector::is_na(polylines[j])) {
        polyline_output[j] = na_dataframe(col_headers);
        continue;
      }
      
      Rcpp::StringVector sv(1);
      sv[0] = polylines[j];
      
      std::string s = Rcpp::as< std::string >(sv);
      polyline_output[j] = decode_polyline(s, col_headers, pointsLat, pointsLon);
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
  std::vector<std::string> col_headers = get_col_headers(encoded_type);
  
  for(int i = 0; i < encodedSize; i++){
    
    // If encodedStrings[i] is NA, assign a data frame of NA values
    if (Rcpp::StringVector::is_na(encodedStrings[i])) {
      results[i] = na_dataframe(col_headers);
      continue;
    }
    
    // Rcpp::Rcout << encodedStrings << std::endl;
    
    std::string encoded = Rcpp::as< std::string >(encodedStrings[i]);
    
    Rcpp::List decoded = decode_polyline(encoded, col_headers, pointsLat, pointsLon);
    
    results[i] = decoded;
  }
  
  return results;
}


// @param type the type of decoded object, coordinates or ZM Attribute
Rcpp::List decode_polyline(std::string encoded, 
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
    Named(col_headers[0]) = pointsLat, 
    Named(col_headers[1]) = pointsLon
  );
  
  out.attr("class") = "data.frame";
  out.attr("row.names") = seq(1, pointsLat.size());

  return out;
}

std::vector<std::string> get_col_headers(Rcpp::String sfg_dim) {
  std::vector<std::string> out;
  if (sfg_dim == "XYZ" || sfg_dim == "XYZM") {
    out.push_back("Z");
    out.push_back("M");
  } else if (sfg_dim == "XYM") {
    out.push_back("M");
    out.push_back("Z");
  } else {
    out.push_back("lat");
    out.push_back("lon");
  }
  
  return out;
}

Rcpp::List na_dataframe(std::vector<std::string>& col_headers) {
  // Create List output that has the necessary attributes to make it a 
  // data.frame object.
  Rcpp::List out = Rcpp::List::create(
    Named(col_headers[0]) = NA_REAL, 
    Named(col_headers[1]) = NA_REAL
  );
  
  out.attr("class") = "data.frame";
  out.attr("row.names") = 1;

  return out;
}

void EncodeNumber(std::ostringstream& os, int num){
  
  std::string out_str;
  
  while(num >= 0x20){
    out_str += (char)(0x20 | (int)(num & 0x1f)) + 63;
    num >>= 5;
  }
  
  out_str += char(num + 63);
  os << out_str;
}

void EncodeSignedNumber(std::ostringstream& os, int num){
  
  unsigned int ui = num;      //3
  ui <<= 1;                   //4
  ui = (num < 0) ? ~ui : ui;  //5
  EncodeNumber(os, ui);
}

std::string encode_polyline(){
  
  int plat = 0;
  int plon = 0;
  int late5;
  int lone5;
  
  std::ostringstream os;

  for(unsigned int i = 0; i < global_vars::lats.size(); i++){
    
    late5 = global_vars::lats[i] * 1e5;
    lone5 = global_vars::lons[i] * 1e5;
    
    EncodeSignedNumber(os, late5 - plat);
    EncodeSignedNumber(os, lone5 - plon);

    plat = late5;
    plon = lone5;
  }
  
  return os.str();
}

// [[Rcpp::export]]
std::string rcpp_encode_polyline(
    std::vector<double> longitude,
    std::vector<double> latitude
) {
  global_vars::lons = longitude;
  global_vars::lats = latitude;
  return encode_polyline();
}

// [[Rcpp::export]]
std::vector<std::string> rcpp_encode_polyline_byrow(
    Rcpp::NumericVector longitude,
    Rcpp::NumericVector latitude
  ) { 
  
  size_t n = longitude.length();
  std::vector<std::string> res;
  global_vars::lons.clear();
  global_vars::lons.resize(1);
  global_vars::lats.clear();
  global_vars::lats.resize(1);
  
  for ( size_t i = 0; i < n; i++ ) {

    global_vars::lons[0] = longitude[i];
    global_vars::lats[0] = latitude[i];

    res.push_back(encode_polyline());
  }
  return res;
}

