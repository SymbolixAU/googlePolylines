#ifndef R_GOOGLEPOLYLINES_ENCODE_H
#define R_GOOGLEPOLYLINES_ENCODE_H

#include <Rcpp.h>
#include "googlepolylines/googlepolylines.h"

//#include "sfheaders/df/sfg.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/utils/lists/list.hpp"

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

  template < int RTYPE >
  inline void encode(
    Rcpp::Vector< RTYPE >& lons,
    Rcpp::Vector< RTYPE >& lats,
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

  template< int RTYPE >
  inline std::string encode(
    Rcpp::Vector< RTYPE >& lons,
    Rcpp::Vector< RTYPE >& lats
  ) {
    std::ostringstream os;
    encode( lons, lats, os );
    return os.str();
  }

  template< int RTYPE >
  inline std::string encode(
    Rcpp::Matrix< RTYPE >& mat
  ) {
    if( mat.ncol() < 2 ) {
      Rcpp::stop("googlepolylines - expecting at least 2 columns in a matrix");
    }

    Rcpp::Vector< RTYPE > lons = mat( Rcpp::_, 0 );
    Rcpp::Vector< RTYPE > lats = mat( Rcpp::_, 1 );
    return encode( lons, lats );
  }

  // encode sfg objects
  template< int RTYPE >
  inline std::string encode(
    Rcpp::Vector< RTYPE >& sfg
  ) {
    
    if( sfg.length() < 2 ) {
      Rcpp::stop("googlepolylines - not enough values in a point");
    }
    Rcpp::Vector< RTYPE > lons(1);
    Rcpp::Vector< RTYPE > lats(1);
    lons[0] = sfg[0];
    lats[0] = sfg[1];
    Rcpp::StringVector res(1);
    return encode( lons, lats );
    // res[0] = encode( lons, lats );
    // return res;
  }

  // template< int RTYPE >
  // inline Rcpp::StringVector encode(
  //   Rcpp::Matrix< RTYPE >& sfg
  // ) {
  // 
  //   if( sfg.ncol() < 2 ) {
  //     Rcpp::stop("googlepolylines - not enough columns in the matrix");
  //   }
  //   R_xlen_t n = sfg.nrow();
  //   R_xlen_t i;
  //   Rcpp::StringVector res( n );
  //   
  //   if( n == 0 ) {
  //     // empty geometry - return empty string
  //     return res;
  //   }
  //   
  //   for( i = 0; i < n; ++i ) {
  //     double lon = sfg( i, 0 );
  //     double lat = sfg( i, 1 );
  //     Rcpp::Vector< RTYPE > lons(1);
  //     Rcpp::Vector< RTYPE > lats(1);
  //     lons[0] = lon;
  //     lats[0] = lat;
  //     res[i] = encode( lons, lats );
  //   }
  //   return res;
  // }

  // template< int RTYPE >
  // inline Rcpp::StringVector encode_linestring(
  //   Rcpp::Matrix< RTYPE >& sfg
  // ) {
  //   
  //   R_xlen_t n = sfg.nrow();
  //   if( n == 0 ) {
  //     Rcpp::StringVector res(0);
  //     return res;
  //   }
  //   return encode( sfg );
  // }
  
  inline Rcpp::StringVector encode(
    SEXP& sfg
  ) {
    switch( TYPEOF( sfg ) ) {
    case INTSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( sfg );
      return encode( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( sfg );
      return encode( iv );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      return encode( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      return encode( nv );
    }
    }
    case VECSXP: {
    if( Rf_isNewList( sfg ) ) {
      Rcpp::Rcout << "new_list" << std::endl;
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      R_xlen_t n = lst.size();
      R_xlen_t i;
      Rcpp::List res( n ); // to add in a SPLIT_CHAR
      for( i = 0; i < n; ++i ) {
        // loop and encode?
        Rcpp::Rcout << "i: " << i << std::endl;
        SEXP sfgi = lst[ i ];
        res[ i ] = encode( sfgi );
      }
      //Rcpp::Rcout << "SPLIT_CHAR" << std::endl;
      //res[ n ] = SPLIT_CHAR;
      Rcpp::StringVector enc = sfheaders::utils::unlist_list( res );
      //return res;
      Rcpp::Rcout << "encoded list " << std::endl;
      
      return enc;
    }
    }
    default: {
      Rcpp::stop("googlePolylines - numeric values required");
    }
    }
    return Rcpp::StringVector::create(); // #nocov - never reaches
  }

  // inline Rcpp::StringVector encode_multilinestring(
  //   Rcpp::List& sfg
  // ) {
  //   int n = sfg.length();
  //   int i;
  //   Rcpp::StringVector res( n );
  // 
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::NumericMatrix line = sfg[ i ];
  //     res[ i ] = encode( line );
  //   }
  //   return res;
  // }
  // 
  // inline Rcpp::StringVector encode_polygon(
  //   Rcpp::List& sfg
  // ) {
  //   return encode_multilinestring( sfg );
  // }
  // 
  // inline Rcpp::StringVector encode_multipolygon(
  //   Rcpp::List& sfg
  // ) {
  // 
  //   int n = sfg.length();
  //   int i, j;
  //   Rcpp::List polygons( n ); 
  //   int line_counter = 0;
  //   
  //   if( n == 0 ) {
  //     Rcpp::StringVector sv(0);
  //     return sv;
  //   }
  //   
  //   std::vector< std::string > lines;
  //   
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::List polygon = sfg[ i ];
  //     line_counter = line_counter + polygon.size() + 1; // to add the SPLIT_CHAR "-" to separate polygons
  //   }
  // 
  //   Rcpp::StringVector res( line_counter );
  // 
  //   int counter = 0;
  //   for( i = 0; i < polygons.size(); ++i ) {
  // 
  //     Rcpp::List polygon = sfg[ i ];
  // 
  //     for( j = 0; j < polygon.size(); ++j ) {  
  //       Rcpp::NumericMatrix line = polygon[ j ];
  //       res[ counter ] = encode( line );
  //       counter = counter + 1;
  //     }
  //   
  //     res[ counter ] = SPLIT_CHAR;
  //     counter = counter + 1;
  //   }
  //   // remove the final SPLIT_CHAR
  //   res.erase( line_counter - 1 );
  //   return res;
  // }

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
      cls = sfheaders::sfg::getSfgClass( sfg );
      geometry = cls[1];
      
      Rcpp::StringVector sv = encode( sfg );

      // TODO:
      // - stop if unknown sfg type (e.g. geometry collection??);
      // - or will this loop handle it?
      
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