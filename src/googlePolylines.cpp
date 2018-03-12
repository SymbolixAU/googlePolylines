#include <Rcpp.h>
#include "googlePolylines.h"

using namespace Rcpp;


// [[Rcpp::export]]
Rcpp::List rcpp_decode_polyline(Rcpp::StringVector encodedStrings) {

  int encodedSize = encodedStrings.size();
  //Rcpp::List resultLats(encodedSize);
  //Rcpp::List resultLons(encodedSize);
  Rcpp::List results(encodedSize);
  
  for(int i = 0; i < encodedSize; i++){
    
    std::string encoded = Rcpp::as< std::string >(encodedStrings[i]);
    
    Rcpp::DataFrame decoded = decode_polyline(encoded);
    
    //resultLons[i] = decoded["lon"];
    //resultLats[i] = decoded["lat"];
    
    results[i] = decoded;
  }
  
  return results;
  //return Rcpp::List::create(resultLons, resultLats);
}



Rcpp::DataFrame decode_polyline(std::string encoded){
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
  Rcpp::NumericVector pointsLat;
  Rcpp::NumericVector pointsLon;
  
  while (index < len){
    char b;
    int shift = 0;
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
  
  // putting latitude first
  return Rcpp::DataFrame::create(
    Named("lat") = pointsLat,
    Named("lon") = pointsLon);
  
//  Rcpp::NumericMatrix mat(pointsLat.size(), 2);
//  mat(_, 0) = pointsLon;
//  mat(_, 1) = pointsLat;
  
//  return mat;
  
//  return Rcpp::List::create(
//    _["lon"] = pointsLon,
//    _["lat"] = pointsLat);
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
  
  int sgn_num = num << 1;
  
  if (sgn_num < 0) {
    sgn_num = ~sgn_num;
  }
  
  EncodeNumber(os, sgn_num);
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
Rcpp::String rcpp_encode_polyline(Rcpp::NumericVector longitude,
                                  Rcpp::NumericVector latitude){

  return encode_polyline(longitude,latitude);
}

