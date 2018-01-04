#include <Rcpp.h>
using namespace Rcpp;

#ifndef GOOGLEPOLYLINES_H
#define GOOGLEPOLYLINES_H

#define SF_Unknown             0
#define SF_Point               1
#define SF_LineString          2
#define SF_Polygon             3
#define SF_MultiPoint          4
#define SF_MultiLineString     5
#define SF_MultiPolygon        6
#define SF_GeometryCollection  7
#define SF_CircularString      8
#define SF_CompoundCurve       9
#define SF_CurvePolygon       10
#define SF_MultiCurve         11
#define SF_MultiSurface       12
#define SF_Curve              13
#define SF_Surface            14
#define SF_PolyhedralSurface  15
#define SF_TIN                16
#define SF_Triangle           17
#define SF_Geometry           18

#define SPLIT_CHAR "-"

void addToStream(std::ostringstream& os, Rcpp::String encodedString ) ; 

template<typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

Rcpp::CharacterVector getSfClass(SEXP sf);

Rcpp::NumericMatrix decode_polyline(std::string encoded);

Rcpp::String EncodeNumber(int num);

Rcpp::String EncodeSignedNumber(int num);

Rcpp::String encode_polyline(Rcpp::NumericVector latitude,
                             Rcpp::NumericVector longitude);

#endif