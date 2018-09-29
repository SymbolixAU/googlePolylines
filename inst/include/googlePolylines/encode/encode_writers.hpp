#ifndef GOOGLEPOLYLINES_ENCODE_WRITERS_H
#define GOOGLEPOLYLINES_ENCODE_WRITERS_H

#include <Rcpp.h>
#include "googlePolylines/googlePolylines.h"
#include "googlePolylines/encode/encode.hpp"
#include "googlePolylines/utils/utils.hpp"

namespace googlepolylines {
namespace encode_writers {

  inline void encode_matrix(std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericMatrix mat, 
                            Rcpp::CharacterVector& sfg_dim, int dim_divisor ) {
    
    googlepolylines::global_vars::lons.clear();
    googlepolylines::global_vars::lats.clear();
    int nrow = mat.nrow();
    for (int i = 0; i < nrow; ++i) {
      googlepolylines::global_vars::lats.push_back(mat(i, 1));
      googlepolylines::global_vars::lons.push_back(mat(i, 0));
    }
    
    googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
    googlepolylines::utils::addToStream(os);
    
    // if (dim_divisor > 2 ) {
    //   int n = mat.size() / dim_divisor;
    //   Rcpp::NumericVector elev(n);
    //   Rcpp::NumericVector meas(n);
    //   if( dim_divisor == 3 ) {
    //     elev = mat(_, 2);
    //   } else if ( dim_divisor == 4 ) { 
    //     elev = mat(_, 2);
    //     meas = mat(_, 3);
    //   }
    //   encodedString = encode_polyline(elev, meas);
    //   addToStream(oszm, encodedString);
    // }
    
  }

  inline void write_matrix_list(std::ostringstream& os, std::ostringstream& oszm, Rcpp::List lst, 
                                Rcpp::CharacterVector& sfg_dim, int dim_divisor ) {
    
    size_t len = lst.length();
    
    for (size_t j = 0; j < len; j++){
      encode_matrix(os, oszm, lst[j], sfg_dim, dim_divisor);
    }
    googlepolylines::global_vars::encodedString = SPLIT_CHAR;
    googlepolylines::utils::addToStream(os);
    
    // if (dim_divisor > 2) {
    //   addToStream(oszm, SPLIT_CHAR);
    // }
  }

  inline void make_dim_divisor(const char *cls, int *d) {
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
  
  inline void make_type(const char *cls, int *tp = NULL,
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
    //return type;
  }
  
  inline void write_multipolygon(std::ostringstream& os, std::ostringstream& oszm, Rcpp::List lst, Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
    
    for (int i = 0; i < lst.length(); i++) {
      write_matrix_list(os, oszm, lst[i], sfg_dim, dim_divisor);
    }
  }
  
  inline void encode_point( std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericVector point, Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
    
    googlepolylines::global_vars::lons.clear();
    googlepolylines::global_vars::lats.clear();
    googlepolylines::global_vars::lons.push_back(point[0]);
    googlepolylines::global_vars::lats.push_back(point[1]);
    
    googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
    googlepolylines::utils::addToStream(os);
    
    // if ( dim_divisor > 2 ) {
    //   Rcpp::NumericVector elev(1);
    //   Rcpp::NumericVector meas(1);
    //   
    //   elev[0] = point[2];
    //   if (dim_divisor == 4 ) {
    //     meas[0] = point[3];
    //   }
    //   
    //   encodedString = encode_polyline(elev, meas);
    //   addToStream(oszm, encodedString);
    // }
    
  }
  
  inline void encode_points( std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericMatrix point, 
                      Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
    
    int n = point.size() / dim_divisor;
    googlepolylines::global_vars::lons.clear();
    googlepolylines::global_vars::lons.resize(1);
    googlepolylines::global_vars::lats.clear();
    googlepolylines::global_vars::lats.resize(1);
    
    //Rcpp::NumericVector elev(1);
    //Rcpp::NumericVector meas(1);
    
    for (int i = 0; i < n; i++){
      googlepolylines::global_vars::lons[0] = point(i, 0);
      googlepolylines::global_vars::lats[0] = point(i, 1);
      googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
      googlepolylines::utils::addToStream(os);
      
      // if ( dim_divisor > 2 ) {
      //   elev[0] = point(i, 2);
      //   meas[0] = dim_divisor == 4 ? point(i, 3) : 0;
      //   
      //   encodedString = encode_polyline( elev, meas );
      //   addToStream(oszm, encodedString);
      // }
      
    }
    
  }
  
  inline void encode_vector( std::ostringstream& os, std::ostringstream& oszm, Rcpp::List vec, Rcpp::CharacterVector& sfg_dim,
                      int dim_divisor) {
    
    // - XY == [0][1]
    // - XYZ == [0][1][2]{3}
    // - XYM == [0][1][2]{3}
    // - XYZM == [0][1][2][3]
    
    int n = vec.size() / dim_divisor;
    
    googlepolylines::global_vars::lats.clear();
    googlepolylines::global_vars::lons.clear();
    
    for (int i = 0; i < n; i++) {
      googlepolylines::global_vars::lons.push_back(vec[i]);
      googlepolylines::global_vars::lats.push_back(vec[(i + n)]);
    }
    
    googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
    googlepolylines::utils::addToStream(os);
    
    // if (dim_divisor > 2) {
    //   // there are Z and M attributes to encode
    //   // constructor sets them to 0
    //   Rcpp::NumericVector elev(n);
    //   Rcpp::NumericVector meas(n);
    //   
    //   for (int i = 0; i < n; i++) {
    //     elev[i] = vec[(i + n + n)];
    //     meas[i] = dim_divisor == 4 ? vec[(i + n + n + n)] : 0;
    //   }
    //   encodedString = encode_polyline(elev, meas);
    //   addToStream(oszm, encodedString);
    // }
    
  }
  
  inline void encode_vectors( std::ostringstream& os, std::ostringstream& oszm, Rcpp::List sfc, Rcpp::CharacterVector& sfg_dim,
                       int dim_divisor){
    
    size_t n = sfc.size();
    
    for (size_t i = 0; i < n; i++) {
      encode_vector(os, oszm, sfc[i], sfg_dim, dim_divisor);
    }
  }
  
  inline void write_data(
      std::ostringstream& os, std::ostringstream& oszm, 
      Rcpp::CharacterVector& sfg_dim, int dim_divisor, 
      SEXP sfc, const char *cls = NULL, int srid = 0) {
    
    int tp;
    Rcpp::CharacterVector cls_attr;
    make_type(cls, &tp, srid);
    
    switch(tp) {
    case SF_Point:
      encode_point(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_MultiPoint:
      encode_points(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_LineString:
      encode_vector(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_MultiLineString:
      encode_vectors(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_Polygon:
      write_matrix_list(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_MultiPolygon:
      write_multipolygon(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
    case SF_Geometry:
      cls_attr = googlepolylines::utils::getSfClass(sfc);
      write_data(os, oszm, sfg_dim, dim_divisor, sfc, cls_attr[1], 0);
      //write_geometry(os, oszm, sfc, sfg_dim, dim_divisor);
      break;
      //  case SF_GeometryCollection:
      //  	write_geometrycollection(os, sfc);
      //    break;
    default: {
        //      Rcpp::Rcout << "type is " << sf_type << "\n";
        Rcpp::stop("encoding this sf type is currently not supported");
      }
    }
  }

} // namespace encode_writers
} // namespace googlepolylines

#endif