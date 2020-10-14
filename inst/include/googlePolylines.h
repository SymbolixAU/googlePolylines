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

#define XYUNKNOWN 0
#define XY        2
#define XYZ       3
#define XYM       3
#define XYZM      4

void addToStream(std::ostringstream& os) ; 

template<typename Out>
void split(const std::string &s, char delim, Out result);

void split(const std::string &s, char delim);

Rcpp::CharacterVector getSfClass(SEXP sf);

Rcpp::List decode_polyline(std::string encoded, 
                           std::vector<std::string>& col_headers, 
                           std::vector<double>& pointsLat, 
                           std::vector<double>& pointsLon);

std::vector<std::string> get_col_headers(Rcpp::String sfg_dim);

Rcpp::List na_dataframe(std::vector<std::string>& col_headers);

void EncodeNumber(std::ostringstream& os, int num);

void EncodeSignedNumber(std::ostringstream& os, int num);

std::string encode_polyline();

Rcpp::List decode_data(Rcpp::StringVector pl,
                 const char *cls = NULL);


namespace global_vars {
  extern std::vector<double> lons;
  extern std::vector<double> lats;
  extern std::string encodedString;
  extern std::vector<std::string> elems;
}

#endif
