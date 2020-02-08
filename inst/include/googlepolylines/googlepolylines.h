
#ifndef GOOGLEPOLYLINES_H
#define GOOGLEPOLYLINES_H

#include <Rcpp.h>

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

#endif