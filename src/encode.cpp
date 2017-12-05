#include <Rcpp.h>
using namespace Rcpp;
#include "googlePolylines.h"


// [[Rcpp::depends(BH)]]

#include <boost/algorithm/string.hpp>


template <int RTYPE>
Rcpp::CharacterVector sfClass(Vector<RTYPE> v) {
  return v.attr("class");
}

Rcpp::CharacterVector getSfClass(SEXP sf) {
  
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

void write_data(std::ostringstream& os, SEXP sfc,
                const char *cls, int srid);

void add_int(std::ostringstream& os, unsigned int i) {
  const char *cp = (char *)&i;
  os.write((char*) cp, sizeof(int));
}

void add_byte(std::ostringstream& os, char c) {
  os.write((char*) &c, sizeof(char));
}

void write_matrix_list(std::ostringstream& os, Rcpp::List lst);

unsigned int make_type(const char *cls, int *tp = NULL,
                       int srid = 0) {
  int type = 0;
  if (strstr(cls, "sfc_") == cls)
    cls += 4;
  if (strcmp(cls, "POINT") == 0)
    type = SF_Point;
  else if (strcmp(cls, "MULTIPOINT") == 0)
    type = SF_MultiPoint;
  else if (strcmp(cls, "LINESTRING") == 0)
    type = SF_LineString;
  else if (strcmp(cls, "POLYGON") == 0)
    type = SF_Polygon;
  else if (strcmp(cls, "MULTILINESTRING") == 0)
    type = SF_MultiLineString;
  else if (strcmp(cls, "MULTIPOLYGON") == 0)
    type = SF_MultiPolygon;
  else if (strcmp(cls, "GEOMETRY") == 0)
    type = SF_Geometry;
  else if (strcmp(cls, "GEOMETRYCOLLECTION") == 0)
  	type = SF_GeometryCollection;
  else
    type = SF_Unknown;
  if (tp != NULL)
    *tp = type;
  //	Rcpp::Rcout << "type: " << type << std::endl;
  return type;
}

void write_multipolygon(std::ostringstream& os, Rcpp::List lst) {
  
  for (int i = 0; i < lst.length(); i++){
    write_matrix_list(os, lst[i]);
  }
}

void addToStream(std::ostringstream& os, Rcpp::String encodedString ) {
  std::string strng = encodedString;
  os << strng << ' ';
}

void encode_point( std::ostringstream& os, Rcpp::NumericVector point) {
  
//  Rcpp::Rcout << point << std::endl;
//  Rcpp::Rcout << "size: " << point.size() << " length: " << point.length() << std::endl;
  Rcpp::NumericVector lon(1);
  Rcpp::NumericVector lat(1);
  
  lon[0] = point[0];
  lat[0] = point[1];
  
  Rcpp::String encodedString = encode_polyline(lon, lat);
  addToStream(os, encodedString);
}

void encode_points( std::ostringstream& os, Rcpp::NumericMatrix point) {
  
  int n = point.size() / 2;
  Rcpp::String encodedString;
  Rcpp::NumericVector pointLon;
  Rcpp::NumericVector pointLat;
  
  for (int i = 0; i < n; i++){
    pointLon = point(i, 0);
    pointLat = point(i, 1);
    encodedString = encode_polyline( pointLon, pointLat);
    addToStream(os, encodedString);
  }
  
}

void encode_vector( std::ostringstream& os, Rcpp::List vec ) {
  
  int n = vec.size() / 2;
  
  Rcpp::String encodedString;

  Rcpp::NumericVector lats(n);
  Rcpp::NumericVector lons(n);
  
  for (int i = 0; i < n; i++){
    lons[i] = vec[i];
    lats[i] = vec[(i + n)];
  }
  
  encodedString = encode_polyline(lons, lats);
  addToStream(os, encodedString);
}

void encode_vectors( std::ostringstream& os, Rcpp::List sfc ){
  
  size_t n = sfc.size();
  for (size_t i = 0; i < n; i++) {
    encode_vector(os, sfc[i]);
  }
}

void encode_matrix(std::ostringstream& os, Rcpp::NumericMatrix mat ) {

  Rcpp::String encodedString;
  
  Rcpp::NumericVector lats = mat(_, 1);
  Rcpp::NumericVector lons = mat(_, 0);
  
  encodedString = encode_polyline(lons, lats);
  
  addToStream(os, encodedString);
}

void write_matrix_list(std::ostringstream& os, Rcpp::List lst) {
  
  size_t len = lst.length();

  for (size_t j = 0; j < len; j++){
    encode_matrix(os, lst[j]);
  }
  
  addToStream(os, SPLIT_CHAR);
}

void write_geometry(std::ostringstream& os, SEXP s) {
  
  Rcpp::CharacterVector cls_attr = getSfClass(s);
  
  write_data(os, s, cls_attr[1], 0);
}

//void write_geometrycollection(std::ostringstream& os, Rcpp::List lst) {
//  
//  SEXP geom;
//  
//  for (int i = 0; i < lst.length(); i++) {
//    
//    Rcpp::Rcout << i << std::endl;
//    geom = lst[i];
//    Rcpp::CharacterVector cls_attr = getSfClass(geom);
//    
//    Rcpp::Rcout << cls_attr[1] << std::endl;
//    
//    write_data(os, geom, cls_attr[1], 0);
//  }
//}


void write_data(std::ostringstream& os, SEXP sfc,
                const char *cls = NULL, int srid = 0) {
  
  int tp;
  unsigned int sf_type = make_type(cls, &tp, srid);

  switch(tp) {
  case SF_Point:
    encode_point(os, sfc);
    break;
  case SF_MultiPoint:
    encode_points(os, sfc);
    break;
  case SF_LineString:
    encode_vector(os, sfc);
    break;
  case SF_MultiLineString:
    encode_vectors(os, sfc);
    break;
  case SF_Polygon:
    write_matrix_list(os, sfc);
    break;
  case SF_MultiPolygon:
    write_multipolygon(os, sfc);
    break;
  case SF_Geometry:
    write_geometry(os, sfc);
    break;
//  case SF_GeometryCollection:
//  	write_geometrycollection(os, sfc);
//    break;
  default: {
//      Rcpp::Rcout << "type is " << sf_type << "\n";
      Rcpp::stop("writing this sf type is currently not supported");
    }
  }
}


// [[Rcpp::export]]
Rcpp::List encodeSfGeometry(Rcpp::List sfc, bool strip){
  
  Rcpp::CharacterVector cls_attr = sfc.attr("class");
  Rcpp::List output(sfc.size());
  int lastItem;
  
  for (int i = 0; i < sfc.size(); i++){

    std::ostringstream os;
    Rcpp::checkUserInterrupt();

    write_data(os, sfc[i], cls_attr[0], 0);
    
    std::string str = os.str();
    std::vector<std::string> strs;
//    boost::split(strs, str, boost::is_any_of("\t "));
    
    strs.erase(strs.end() - 1);
    lastItem = strs.size() - 1;
    
    if (strs[lastItem] == "-") {
      strs.erase(strs.end() - 1);
    }
  
    Rcpp::CharacterVector sv = wrap(strs);
//    Rcpp::Rcout << "sv: " << sv << std::endl;
//    for (int j = 0; j < sv.size(); j++ ) {
//      Rcpp::Rcout << "sv size - j : " << j << std::endl;
//      if (sv[j].size() == 1 && sv[j] == "-") {
//        Rcpp::Rcout << "splitter" << std::endl;
//      }
//    }
    
    
    if(strip == FALSE){
      sv.attr("sfc") = getSfClass(sfc[i]);
    }
    output[i] = sv;
  }
  return output;
}