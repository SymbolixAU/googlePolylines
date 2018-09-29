#ifndef GOOGLEPOLYLINES_DECODE_CONSTRUCTORS_H
#define GOOGLEPOLYLINES_DECODE_CONSTRUCTORS_H

#include <Rcpp.h>

namespace googlepolylines {
namespace decodeconstuctors {

  inline std::vector<std::string> get_col_headers(Rcpp::String sfg_dim) {
    std::vector<std::string> out;
    if (sfg_dim == "XYZ" || sfg_dim == "XYZM") {
      out.push_back("Z");
      out.push_back("M");
    } else if (sfg_dim == "XYM") {
      out.push_back("M");
      out.push_back("Z");
    } else {
      out.push_back("lat");
      out.push_back("lon");
    }
    return out;
  }
  
  inline Rcpp::List na_dataframe(std::vector<std::string>& col_headers) {
    // Create List output that has the necessary attributes to make it a 
    // data.frame object.
    Rcpp::List out = Rcpp::List::create(
      Rcpp::Named(col_headers[0]) = NA_REAL, 
      Rcpp::Named(col_headers[1]) = NA_REAL
    );
    out.attr("class") = "data.frame";
    out.attr("row.names") = 1;
    return out;
  }

}
} // namespace googlepolyilnes

#endif 
