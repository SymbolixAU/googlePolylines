#include <Rcpp.h>
#include "googlePolylines.h"

using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::List rcpp_decode_polyline_list( Rcpp::List encodedList, std::string attribute ) {

  // If the DIM is just Z or just M, should the result return a vector, rather than
  // a 2-column data.frame? 
  // probably
  
  size_t n = encodedList.size();
  Rcpp::List output(n);
  Rcpp::CharacterVector sfg_dim;
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
      polyline_output[j] = decode_polyline(s, col_headers );
    }
    output[i] = polyline_output;
  }
  return output;
  
}

// [[Rcpp::export]]
Rcpp::List rcpp_decode_polyline(Rcpp::StringVector encodedStrings, Rcpp::String encoded_type) {

  int encodedSize = encodedStrings.size();
  Rcpp::List results(encodedSize);
  std::vector<std::string> col_headers = get_col_headers(encoded_type);
  
  for(int i = 0; i < encodedSize; i++){
    
    // If encodedStrings[i] is NA, assign a data frame of NA values
    if (Rcpp::StringVector::is_na(encodedStrings[i])) {
      results[i] = na_dataframe(col_headers);
      continue;
    }
    
    std::string encoded = Rcpp::as< std::string >(encodedStrings[i]);
    
    Rcpp::DataFrame decoded = decode_polyline(encoded, col_headers);
    
    results[i] = decoded;
  }
  
  return results;
}


// @param type the type of decoded object, coordinates or ZM Attribute
Rcpp::DataFrame decode_polyline(std::string encoded, std::vector<std::string>& col_headers) {
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
  Rcpp::NumericVector pointsLat;
  Rcpp::NumericVector pointsLon;
  
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
  
  return Rcpp::DataFrame::create(
    Named(col_headers[0]) = pointsLat, 
    Named(col_headers[1]) = pointsLon
  );
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

Rcpp::DataFrame na_dataframe(std::vector<std::string>& col_headers) {
  return Rcpp::DataFrame::create(
    Named(col_headers[0]) = NA_REAL, 
    Named(col_headers[1]) = NA_REAL
  );
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

Rcpp::String encode_polyline(Rcpp::NumericVector longitude,
                             Rcpp::NumericVector latitude){
  
  int plat = 0;
  int plon = 0;
  int num_coords = latitude.size();
  
  std::ostringstream os;
  Rcpp::String output_str;
  
  for(int i = 0; i < num_coords; i++){
    
    int late5 = latitude[i] * 1e5;
    int lone5 = longitude[i] * 1e5;
    
    EncodeSignedNumber(os, late5 - plat);
    EncodeSignedNumber(os, lone5 - plon);

    plat = late5;
    plon = lone5;
  }
  
  output_str = os.str();
  return output_str;
}

// [[Rcpp::export]]
Rcpp::String rcpp_encode_polyline(
    Rcpp::NumericVector longitude,
    Rcpp::NumericVector latitude
  ) {
  return encode_polyline(longitude, latitude);
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_encode_polyline_byrow(
    Rcpp::NumericVector longitude,
    Rcpp::NumericVector latitude
  ) { 
  
  size_t n = longitude.length();
  Rcpp::StringVector res( n );
  Rcpp::NumericVector lon(1);
  Rcpp::NumericVector lat(1);
  
  for ( size_t i = 0; i < n; i++ ) {
    
    lon[0] = longitude[i];
    lat[0] = latitude[i];

    res[i] = encode_polyline( lon, lat );
  }
  return res;
}

