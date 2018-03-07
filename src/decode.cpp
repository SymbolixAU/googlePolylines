#include <Rcpp.h>
using namespace Rcpp;
#include "googlePolylines.h"

// [[Rcpp::export]]
Rcpp::List rcpp_decode_sfencoded(Rcpp::List polylines, Rcpp::List sfAttributes){
  
  Rcpp::Rcout << "debug: step1" << std::endl;
  int n = polylines.size();
  Rcpp::List res(n);
  Rcpp::List thisGeom(0);
//  Rcpp::Rcout << "debug: polylines size: " << n << std::endl;
  
  Rcpp::List crs = Rcpp::List::create(Named("epsg") = sfAttributes["epsg"],
                                      Named("proj4string") = sfAttributes["proj"]);
  crs.attr("class") = "cls";
  
  
  for (int i = 0; i < n; i++) {
    Rcpp::StringVector sv = polylines[i];
//    Rcpp::Rcout << sv << std::endl;
    Rcpp::CharacterVector cls = sv.attr("sfc");
//    Rcpp::Rcout << cls << std::endl;
    
    thisGeom = decode_data(sv, cls[1]);
    thisGeom.attr("class") = Rcpp::CharacterVector::create("sfc_POINT", "sfc");
    
    res[i] = thisGeom;
  }
  
  res.attr("crs") = crs;
  res.attr("bbox") = sfAttributes["bbox"];
  res.attr("precision") = sfAttributes["prec"];
  res.attr("n_empty") = sfAttributes["n_em"];
  
  return res;
  
}


// functions for decoding each TYPE of geometry
// POINT
// MULTIPOINT
// LINESTRING
// MULTILINESTRING
// POLYGON
// MULTIPOLYGON
//
// each one will return something slightly different? 
// will be doing what the sf code does

// logic
// get the sfc attribute
// - based on result, 
// - return 
void decode_type(const char *cls, int *tp = NULL) {
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
  //return type;
}

Rcpp::NumericVector decode_point(Rcpp::StringVector pl) {
  Rcpp::NumericVector res(2);
  std::vector< std::string > spl(pl.size());
  spl[0] = pl[0];
  
  Rcpp::DataFrame df = decode_polyline(spl[0]);
  
  // df should ONLY BE ONE ROW!!
  // TODO: error handle this case
  
  
  res[0] = df["lon"];
  res[1] = df["lat"];
  res.attr("class") = Rcpp::StringVector::create("XY", "POINT", "sfg");
  return res;
}

Rcpp::NumericMatrix decode_points(Rcpp::StringVector pl) {
  Rcpp::NumericMatrix res(pl.size());
  Rcpp::StringVector thisPoint;
  
  for (int i = 0; i < pl.size(); i++) {
    thisPoint = pl[i];
    res(i, _) = decode_point(thisPoint);
  }
  res.attr("class") = Rcpp::StringVector::create("XY", "MULTIPOINT", "sfg");
  return res;
}

Rcpp::NumericMatrix decode_line(Rcpp::StringVector pl) {
  Rcpp::NumericMatrix res;
  
  return res;
}

Rcpp::List decode_lines(Rcpp::StringVector pl) {
  Rcpp::List res;
  
  return res;
}

Rcpp::List decode_polygon(Rcpp::StringVector pl) {
  Rcpp::List res;
  
  return res;
} 

Rcpp::List decode_multipolygon(Rcpp::StringVector pl) {
  Rcpp::List res;
  
  return res;
}


Rcpp::List decode_data(Rcpp::StringVector pl,
                 const char *cls) {
  
  Rcpp::Rcout << "debug: decode_data: " << std::endl;
  
  Rcpp::List output(1);
  int tp;
  decode_type(cls, &tp);
  
  switch(tp) {
  case SF_Point:
    output[0] = decode_point(pl);
    //output.attr("class") = Rcpp::CharacterVector::create("sfc_POINT", "sfc");
    break;
  case SF_MultiPoint:
    output[0] = decode_points(pl);
    //output.attr("class") = Rcpp::CharacterVector::create("sfc_MULTIPOINT", "sfc");
    break;
  case SF_LineString:
    output[0] = decode_line(pl);
    break;
  case SF_MultiLineString:
    output[0] = decode_lines(pl);
    break;
  case SF_Polygon:
    output[0] = decode_polygon(pl);
    break;
  case SF_MultiPolygon:
    output[0] = decode_multipolygon(pl);
    break;
//  case SF_Geometry:
//    decode_geometry(pl);
//    break;
    //  case SF_GeometryCollection:
    //  	write_geometrycollection(pl);
    //    break;
  default: {
      //      Rcpp::Rcout << "type is " << sf_type << "\n";
      Rcpp::stop("decoding this sf type is currently not supported");
    }
  }
  
  return output;
}
