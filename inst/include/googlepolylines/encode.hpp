#ifndef R_GOOGLEPOLYLINES_ENCODE_H
#define R_GOOGLEPOLYLINES_ENCODE_H

#include <Rcpp.h>
#include "googlepolylines/googlepolylines.h"

#include "sfheaders/df/sfg.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"

namespace googlepolylines {
namespace encode {

  inline void encode_number(
      std::ostringstream& os, 
      int num
  ) {
    
    std::string out_str;
    
    while(num >= 0x20){
      out_str += (char)(0x20 | (int)(num & 0x1f)) + 63;
      num >>= 5;
    }
    
    out_str += char(num + 63);
    os << out_str;
  }

  inline void encode_signed_number(
      std::ostringstream& os, 
      int num
  ) {
    
    unsigned int ui = num;      //3
    ui <<= 1;                   //4
    ui = (num < 0) ? ~ui : ui;  //5
    encode_number(os, ui);
  }

  inline void encode(
    Rcpp::NumericVector& lons,
    Rcpp::NumericVector& lats,
    std::ostringstream& os
  ) {
    int plat = 0;
    int plon = 0;
    int late5;
    int lone5;
    
    R_xlen_t i;
    R_xlen_t n = lats.size();
    
    for( i = 0; i < n; i++){
      
      late5 = lats[ i ] * 1e5;
      lone5 = lons[ i ] * 1e5;
      
      encode_signed_number(os, late5 - plat);
      encode_signed_number(os, lone5 - plon);
      
      plat = late5;
      plon = lone5;
    }
  }

  inline std::string encode(
    Rcpp::NumericVector& lons,
    Rcpp::NumericVector& lats
  ) {
    std::ostringstream os;
    encode( lons, lats, os );
    // Rcpp::Rcout << "os" << os.str() <<  std::endl;
    return os.str();
  }

  inline std::string encode(
    Rcpp::NumericMatrix& mat
  ) {
    if( mat.ncol() < 2 ) {
      Rcpp::stop("googlepolylines - expecting at least 2 columns in a matrix");
    }

    Rcpp::NumericVector lons = mat( Rcpp::_, 0 );
    Rcpp::NumericVector lats = mat( Rcpp::_, 1 );
    return encode( lons, lats );
  }

  // encode sfg objects
  inline Rcpp::StringVector encode_point(
    Rcpp::NumericVector& sfg
  ) {
    
    //Rcpp::DataFrame df = sfheaders::df::sfg_to_df(sfg);
    // but I don't know what type of sfg it is yet...

    if( sfg.length() < 2 ) {
      Rcpp::stop("googlepolylines - not enough values in a point");
    }
    Rcpp::NumericVector lons(1);
    Rcpp::NumericVector lats(1);
    lons[0] = sfg[0];
    lats[0] = sfg[1];
    Rcpp::StringVector res(1);
    res[0] = encode( lons, lats );
    return res;
  }

  inline Rcpp::StringVector encode_multipoint(
    Rcpp::NumericMatrix& sfg
  ) {

    if( sfg.ncol() < 2 ) {
      Rcpp::stop("googlepolylines - not enough columns in the matrix");
    }
    R_xlen_t n = sfg.nrow();
    R_xlen_t i;
    Rcpp::StringVector res( n );
    
    if( n == 0 ) {
      // empty geometry - return empty string
      return res;
    }
    
    for( i = 0; i < n; ++i ) {
      double lon = sfg( i, 0 );
      double lat = sfg( i, 1 );
      Rcpp::NumericVector lons(1);
      Rcpp::NumericVector lats(1);
      lons[0] = lon;
      lats[0] = lat;
      res[i] = encode( lons, lats );
    }
    return res;
  }

  inline Rcpp::StringVector encode_linestring(
    Rcpp::NumericMatrix& sfg
  ) {
    
    R_xlen_t n = sfg.nrow();
    if( n == 0 ) {
      Rcpp::StringVector res(0);
      return res;
    }
    return encode( sfg );
  }

  inline Rcpp::StringVector encode_multilinestring(
    Rcpp::List& sfg
  ) {
    int n = sfg.length();
    int i;
    Rcpp::StringVector res( n );
    
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix line = sfg[ i ];
      res[ i ] = encode( line );
    }
    return res;
  }

  inline Rcpp::StringVector encode_polygon(
    Rcpp::List& sfg
  ) {
    return encode_multilinestring( sfg );
  }

  inline Rcpp::StringVector encode_multipolygon(
    Rcpp::List& sfg
  ) {

    int n = sfg.length();
    int i, j;
    Rcpp::List polygons( n ); 
    int line_counter = 0;
    
    if( n == 0 ) {
      Rcpp::StringVector sv(0);
      return sv;
    }
    
    std::vector< std::string > lines;
    
    for( i = 0; i < n; ++i ) {
      Rcpp::List polygon = sfg[ i ];
      line_counter = line_counter + polygon.size() + 1; // to add the SPLIT_CHAR "-" to separate polygons
    }

    Rcpp::StringVector res( line_counter );

    int counter = 0;
    for( i = 0; i < polygons.size(); ++i ) {

    Rcpp::List polygon = sfg[ i ];
  
      for( j = 0; j < polygon.size(); ++j ) {  
        Rcpp::NumericMatrix line = polygon[ j ];
        res[ counter ] = encode( line );
        counter = counter + 1;
      }
    
      res[ counter ] = SPLIT_CHAR;
      counter = counter + 1;
    }
    // remove the final SPLIT_CHAR
    res.erase( line_counter - 1 );
    return res;
  }

  inline Rcpp::List encode_sfc(
    Rcpp::List& sfc,
    bool& strip
  ) {

    R_xlen_t n = sfc.size();
    R_xlen_t i;
    Rcpp::List res( n );
    Rcpp::CharacterVector cls;
    std::string geometry;
    
    for( i = 0; i < n; ++i ) {
      
      SEXP sfg = sfc[ i ];
      cls = sfheaders::df::getSfgClass( sfg );
      geometry = cls[1];
      
      Rcpp::StringVector sv;
      
      if( geometry == "POINT" ) {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
        sv = encode_point( nv );
      } else if ( geometry == "MULTIPOINT" ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
        sv = encode_multipoint( nm );
      } else if ( geometry == "LINESTRING" ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
        sv = encode_linestring( nm );
      } else if ( geometry == "MULTILINESTRING" ) {
        Rcpp::List mls = Rcpp::as< Rcpp::List >( sfg );
        sv = encode_multilinestring( mls );
      } else if ( geometry == "POLYGON" ) {
        Rcpp::List pl = Rcpp::as< Rcpp::List >( sfg );
        sv = encode_polygon( pl );
      } else if ( geometry == "MULTIPOLYGON" ) {
        Rcpp::List mpl = Rcpp::as< Rcpp::List >( sfg );
        sv = encode_multipolygon( mpl );
      } else {
        Rcpp::stop("googlepolylines - unknown sfg type");
      }
      
      if( !strip ) {
        std::string dim = "XY";
        sv.attr("sfg") = sfheaders::sfg::sfg_attributes(dim, geometry);
      }
      
      res[i] = sv;
      
    }
    return res;
  }


} // encode
} // googlepolylines

#endif