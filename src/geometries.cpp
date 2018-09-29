#include <Rcpp.h>

bool is_multipolygon( const char* x) {
  return strcmp( x, "MULTIPOLYGON" );
}

bool is_polygon( const char* x ) {
  return strcmp( x, "POLYGON");
}

bool is_geom_type( const char* x, const char* type ) {
  return strcmp( x, type );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_encoded_column_types( Rcpp::List sfencoded ) {
  // Extracts the geometry types of the encoded column
  int n = sfencoded.size();
  Rcpp::StringVector res( n );
  Rcpp::CharacterVector cls;
  for ( int i = 0; i < n; i++ ) {
    Rcpp::StringVector thisElem = sfencoded[i];
    cls = thisElem.attr("sfc");
    //Rcpp::Rcout << "is: " << is_multipolygon(cls[1]) << std::endl;
    res[i] = cls[1];
  }
  return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_get_geometry_types( Rcpp::List sfencoded, const char* type ) {
  int n = sfencoded.size();
  Rcpp::IntegerVector res( n );
  Rcpp::CharacterVector cls(3);
  int success_counter = 0;
  for( int i = 0; i < n; i++ ){
    Rcpp::StringVector thisElem = sfencoded[i];
    cls = thisElem.attr("sfc");
    if ( is_geom_type( cls[1], type) == 0 ) {
      res[success_counter] = i;
      success_counter++;
    }
  }
  return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_get_geometry_types_multi( Rcpp::List sfencoded, const char* type1, const char* type2 ) {
  int n = sfencoded.size();
  Rcpp::IntegerVector res( n );
  Rcpp::CharacterVector cls(3);
  int success_counter = 0;
  for( int i = 0; i < n; i++ ){
    Rcpp::StringVector thisElem = sfencoded[i];
    cls = thisElem.attr("sfc");
    if ( is_geom_type( cls[1], type1) == 0 || is_geom_type( cls[1], type2) == 0) {
      res[success_counter] = i;
      success_counter++;
    }
  }
  return res;
}

//http://kevinushey.github.io/blog/2015/01/24/understanding-data-frame-subsetting/
// [[Rcpp::export]]
SEXP subset_df(SEXP x,
               Rcpp::IntegerVector row_indices,
               Rcpp::IntegerVector column_indices) {
  
  // Get some useful variables
  // (lengths of index vectors)
  int column_indices_n = column_indices.size();
  int row_indices_n = row_indices.size();
  
  // Translate from R to C indices.
  // This could be optimized...
  row_indices = row_indices - 1;
  column_indices = column_indices - 1;
  
  // Allocate the output 'data.frame'.
  Rcpp::List output = Rcpp::no_init(column_indices_n);
  
  // Set the names, based on the names of 'x'.
  // We'll assume it has names.
  Rcpp::CharacterVector x_names =
    Rcpp::as<Rcpp::CharacterVector>(Rf_getAttrib(x, R_NamesSymbol));
  
  // Use Rcpp's sugar subsetting to subset names.
  output.attr("names") = x_names[column_indices];
  
  // Loop and fill!
  for (int j = 0; j < column_indices_n; ++j)
  {
    // Get the j'th element of 'x'. We don't need to
    // PROTECT it since it's implicitly protected as a
    // child of 'x'.
    SEXP element = VECTOR_ELT(x, column_indices[j]);
    
    // Get the 'rows' for that vector, and fill.
    SEXP vec = PROTECT(
      Rf_allocVector(TYPEOF(element), row_indices_n)
    );
    
    for (int i = 0; i < row_indices_n; ++i)
    {
      // Copying vectors is a pain in the butt, because
      // we need to know the actual type underneath the
      // SEXP. I'll just handle a couple of the main
      // types. One could imagine simplifying this with
      // some macro magic...
      switch (TYPEOF(vec))
      {
      case REALSXP:
        REAL(vec)[i] =
          REAL(element)[row_indices[i]];
        break;
      case INTSXP:
      case LGLSXP:
        INTEGER(vec)[i] =
          INTEGER(element)[row_indices[i]];
        break;
      case STRSXP:
        SET_STRING_ELT(vec, i,
                       STRING_ELT(element, row_indices[i]));
        break;
      }
    }
    
    // Don't need to protect 'vec' anymore
    UNPROTECT(1);
    
    // And make sure the output list now
    // refers to that vector!
    SET_VECTOR_ELT(output, j, vec);
  }
  
  // Finally, copy the attributes of `x` to `output`...
  Rf_copyMostAttrib(x, output);
  
  // ... but set the row names manually. Note that this
  // is the secret method for creating 'compact' row
  // names, whereby internally R stores the 'empty' row
  // names object as 'c(NA_integer_, -<nrow>)'.
  Rf_setAttrib(output, R_RowNamesSymbol,
               Rcpp::IntegerVector::create(NA_INTEGER, -row_indices_n));
  
  return output;
  
}