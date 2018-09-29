#ifndef GOOGLEPOLYLINES_ENCODE_API_H
#define GOOGLEPOLYLINES_ENCODE_API_H

#include <Rcpp.h>
#include "googlePolylines/googlePolylines.h"
#include "googlePolylines/encode/encode.hpp"
#include "googlePolylines/encode/encode_writers.hpp"


namespace googlepolylines {
namespace encode_api {

  inline Rcpp::List encodeSfGeometry( Rcpp::List& sfc, bool strip ) {
    Rcpp::CharacterVector cls_attr = sfc.attr("class");
    
    Rcpp::CharacterVector sfg_dim;
    int dim_divisor;
    
    Rcpp::List output(sfc.size());
    //Rcpp::List output_zm(sfc.size());
    int lastItem;
    Rcpp::List thisSfc;
    std::string str;
    Rcpp::CharacterVector sv;
    
    // TODO(empty geometries should not enter this list and return something?)
    
    for (int i = 0; i < sfc.size(); i++){
      
      std::ostringstream os;
      std::ostringstream oszm;
      Rcpp::checkUserInterrupt();
      
      sfg_dim = googlepolylines::utils::getSfClass(sfc[i]);
      thisSfc = sfc[i];
      
      if (thisSfc.size() > 0 ) {
        
        googlepolylines::encode_writers::make_dim_divisor(sfg_dim[0], &dim_divisor);
        googlepolylines::encode_writers::write_data(os, oszm, sfg_dim, dim_divisor, sfc[i], cls_attr[0], 0);
      }
      
      str = os.str();
      // std::string zmstr = oszm.str();
      
      googlepolylines::utils::split(str, ' ');
      // std::vector< std::string > zmstrs = split(zmstr, ' ');
      
      // MULTI* objects
      lastItem = googlepolylines::global_vars::elems.size() - 1;
      
      if (lastItem >= 0) {
        
        if (googlepolylines::global_vars::elems[lastItem] == "-") {
          googlepolylines::global_vars::elems.erase( googlepolylines::global_vars::elems.end() - 1 );
          // if (dim_divisor > 2 ) {
          //   zmstrs.erase(zmstrs.end() - 1);
          // }
        }
      }
      
      sv = Rcpp::wrap( googlepolylines::global_vars::elems );
      // Rcpp::CharacterVector zmsv = wrap( zmstrs );
      
      if(strip == FALSE) {
        sv.attr("sfc") = sfg_dim;
        // zmsv.attr("zm") = as< Rcpp::CharacterVector >( sfg_dim[0] );
      }
      output[i] = sv;
      // output_zm[i] = zmsv;
    }
    
    // TODO(only return zm stream IFF there are dim attributes?)
    // return Rcpp::List::create(
    //   _["XY"] = output
    //   _["ZM"] = output_zm
    // );
    return output;
  }

} // namespace encode_api
} // namespace googlepolylines


#endif