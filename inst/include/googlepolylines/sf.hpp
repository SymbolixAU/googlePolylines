
#ifndef R_GOOGLEPOLYLINES_SF_H
#define R_GOOGLEPOLYLINES_SF_H

#include "googlepolylines/googlepolylines.h"

namespace googlepolylines {
namespace sf {

  inline void make_dim_divisor(
      const char *cls, 
      int *d
  ) {
    int divisor = 2;
    if (strcmp(cls, "XY") == 0)
      divisor = XY;
    else if (strcmp(cls, "XYZ") == 0) 
      divisor = XYZ;
    else if (strcmp(cls, "XYM") == 0)
      divisor = XYM;
    else if (strcmp(cls, "XYZM") == 0)
      divisor = XYZM;
    else 
      Rcpp::stop("Unknown dimension attribute");
    *d = divisor;
  }
  
  inline void make_type(
      const char *cls, 
      int *tp = NULL,
      int srid = 0
  ) {
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

} // sf
} // googlepolylines

#endif