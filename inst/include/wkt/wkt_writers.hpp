#ifndef GOOGLEPOLYLINES_WKT_WRITERS_H
#define GOOGLEPOLYLINES_WKT_WRITERS_H

#include <Rcpp.h>
#include "wkt.h"

namespace googlepolylines {
namespace wktwriters {

  inline void beginWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
    
    int tp;
    googlepolylines::wkt::geom_type(cls[1], &tp);
    //geom_type(cls[0], &tp);  // iff removing XY and sfg attributs
    
    switch( tp ) {
    case POINT:
      os << "POINT ";
      break;
    case MULTIPOINT:
      os << "MULTIPOINT (";
      break;
    case LINESTRING:
      os << "LINESTRING ";
      break;
    case MULTILINESTRING:
      os << "MULTILINESTRING (";
      break;
    case POLYGON:
      os << "POLYGON (";
      break;
    case MULTIPOLYGON:
      os << "MULTIPOLYGON ((";
      break;
    default: {
        Rcpp::stop("Unknown geometry type");
      }
    }
  }
  
  inline void endWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
    
    int tp;
    googlepolylines::wkt::geom_type(cls[1], &tp);
    //geom_type(cls[0], &tp);
    
    switch( tp ) {
    case POINT:
      os << "";
      break;
    case MULTIPOINT:
      os << ")";
      break;
    case LINESTRING:
      os << "";
      break;
    case MULTILINESTRING:
      os << ")";
      break;
    case POLYGON:
      os << ")";
      break;
    case MULTIPOLYGON:
      os << "))";
      break;
    default: {
        Rcpp::stop("Unknown geometry type");
      }
    }
  }

} // namespace wktwriters
} // namespace googlepolylines

#endif