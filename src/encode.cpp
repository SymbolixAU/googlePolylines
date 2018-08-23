#include <Rcpp.h>
using namespace Rcpp;
#include "googlePolylines.h"

template <int RTYPE>
Rcpp::CharacterVector sfClass(Vector<RTYPE> v) {
  return v.attr("class");
}

Rcpp::CharacterVector getSfClass(SEXP sf) {
  
  switch( TYPEOF(sf) ) {
    case REALSXP: 
      return sfClass<REALSXP>(sf);
    case VECSXP: 
      return sfClass<VECSXP>(sf);
    case INTSXP: 
      return sfClass<INTSXP>(sf);
  default: Rcpp::stop("unknown sf type");
  }
  return "";
}


template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}


void write_data(std::ostringstream& os, std::ostringstream& oszm, Rcpp::CharacterVector& sfg_dim, int dim_divisor, 
                SEXP sfc, const char *cls, int srid);

void write_matrix_list(std::ostringstream& os, std::ostringstream& oszm, Rcpp::List lst, Rcpp::CharacterVector& sfg_dim, int dim_divisor);

void make_dim_divisor(const char *cls, int *d) {
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

void make_type(const char *cls, int *tp = NULL,
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

void write_multipolygon(std::ostringstream& os, std::ostringstream& oszm, Rcpp::List lst, Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  
  for (int i = 0; i < lst.length(); i++) {
    write_matrix_list(os, oszm, lst[i], sfg_dim, dim_divisor);
  }
}

void addToStream(std::ostringstream& os, Rcpp::String encodedString ) {
  std::string strng = encodedString;
  os << strng << ' ';
}

void geometry_dim(Rcpp::List& sf, Rcpp::CharacterVector& sfg_dim) {
  
  Rcpp::CharacterVector geom_attr;
  
  for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {
    
    switch( TYPEOF(*it) ) {
    
    case VECSXP: {
      Rcpp::List tmp = as<Rcpp::List>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        geometry_dim(tmp, sfg_dim);
      } else {
        sfg_dim = tmp.attr("class");
      }
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        Rcpp::stop("Geometry could not be determined");
      } else {
        sfg_dim = tmp.attr("class");
      }
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector tmp = as<Rcpp::IntegerVector>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        Rcpp::stop("Geometry could not be determined");
      } else {
        sfg_dim = tmp.attr("class");
      }
      break;
    }
    case STRSXP: {
      Rcpp::StringVector tmp = as<Rcpp::StringVector>(*it);
      if(Rf_isNull(tmp.attr("class"))){
        Rcpp::stop("Geometry could not be determined");
      } else {
        sfg_dim = tmp.attr("class");
      }
      break;
    }
    default: {
      Rcpp::stop("Geometry could not be determined");
    }
    }
  }
}

void encode_point( std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericVector point, Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  //Rcpp::Rcout << "point size: " << point.size() << std::endl;
  
  Rcpp::NumericVector lon(1);
  Rcpp::NumericVector lat(1);
  
  lon[0] = point[0];
  lat[0] = point[1];
  
  Rcpp::String encodedString;
  
  encodedString = encode_polyline(lon, lat);
  addToStream(os, encodedString);
  
  if ( dim_divisor > 2 ) {
    Rcpp::NumericVector elev(1);
    Rcpp::NumericVector meas(1);
    
    elev[0] = point[2];
    if (dim_divisor == 4 ) {
      meas[0] = point[3];
    }
    
    encodedString = encode_polyline(elev, meas);
    addToStream(oszm, encodedString);
  }
  
}

void encode_points( std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericMatrix point, 
                    Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  //Rcpp::Rcout << "points size: " << point.size() << std::endl;
  
  int n = point.size() / dim_divisor;
  Rcpp::String encodedString;
  Rcpp::NumericVector pointLon;
  Rcpp::NumericVector pointLat;
  
  Rcpp::NumericVector elev(1);
  Rcpp::NumericVector meas(1);
  
  for (int i = 0; i < n; i++){
    pointLon = point(i, 0);
    pointLat = point(i, 1);
    encodedString = encode_polyline( pointLon, pointLat );
    addToStream(os, encodedString);
    
    if ( dim_divisor > 2 ) {
      elev[0] = point(i, 2);
      meas[0] = dim_divisor == 4 ? point(i, 3) : 0;
      
      encodedString = encode_polyline( elev, meas );
      addToStream(oszm, encodedString);
    }
    
  }
  
}

void encode_vector( std::ostringstream& os, std::ostringstream& oszm, Rcpp::List vec, Rcpp::CharacterVector& sfg_dim,
                    int dim_divisor) {
  
  // TODO(Z/M elements)
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  
  // TODO:
  // - XY == [0][1]
  // - XYZ == [0][1][2]{3}
  // - XYM == [0][1][2]{3}
  // - XYZM == [0][1][2][3]
  
  int n = vec.size() / dim_divisor;  // 2 : just using lon & lat, not Z/M?
  
  //Rcpp::Rcout << "vec size: " << vec.size() << std::endl;
  //Rcpp::Rcout << "vec length: " << vec.length() << std::endl;
  //::Rcout << "n elements: " << n << std::endl;

  Rcpp::String encodedString;

  Rcpp::NumericVector lats(n);
  Rcpp::NumericVector lons(n);
  
  for (int i = 0; i < n; i++) {
    
    //int testInt = dim_divisor == 2 ? 1 : ( dim_divisor == 3 ? 2 : 3 );
    //Rcpp::Rcout << "test string: " << testInt << std::endl;

    
    lons[i] = vec[i];
    lats[i] = vec[(i + n)];  // lats are the 2nd element
    
    //elev[i] = vec[( i + n + n)];
    
    
    // n == the number of elements in the geometry
    // dim_divisor == the number of fields (XYZM) in each element
    // lons is always the [0] elemnet
    // lats is always the [1] element
    // Z||M are the [2,3] elements, if they exist
    
    // when just XY, the vec (vecotr) is c(lon, lon, lon, lon, lat, lat, lat, lat)
    // XYZ : c(lon, lon, lon, lon, lat, lat, lat, lat, Z, Z, Z, Z)
  }
  
  //Rcpp::Rcout << "lons: " << lons << std::endl;
  //Rcpp::Rcout << "lats: " << lats << std::endl;
  //Rcpp::Rcout << "elev: " << elev << std::endl;
  
  encodedString = encode_polyline(lons, lats);
  addToStream(os, encodedString);
  
  if (dim_divisor > 2) {
    // there are Z and M attributes to encode
    // constructor sets them to 0
    Rcpp::NumericVector elev(n);
    Rcpp::NumericVector meas(n);
    
    for (int i = 0; i < n; i++) {
      elev[i] = vec[(i + n + n)];
      meas[i] = dim_divisor == 4 ? vec[(i + n + n + n)] : 0;
    }
    encodedString = encode_polyline(elev, meas);
    addToStream(oszm, encodedString);
  }
  
}

void encode_vectors( std::ostringstream& os, std::ostringstream& oszm, Rcpp::List sfc, Rcpp::CharacterVector& sfg_dim,
                     int dim_divisor){
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  size_t n = sfc.size();
  
  for (size_t i = 0; i < n; i++) {
    encode_vector(os, oszm, sfc[i], sfg_dim, dim_divisor);
  }
}

void encode_matrix(std::ostringstream& os, std::ostringstream& oszm, Rcpp::NumericMatrix mat, 
                   Rcpp::CharacterVector& sfg_dim, int dim_divisor ) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  //Rcpp::Rcout << "mat size: " << mat.size() << std::endl;
  //Rcpp::Rcout << "matrix: " << mat << std::endl;
  
  Rcpp::String encodedString;
  
  Rcpp::NumericVector lats = mat(_, 1);
  Rcpp::NumericVector lons = mat(_, 0);

  encodedString = encode_polyline(lons, lats);
  addToStream(os, encodedString);
  
  if (dim_divisor > 2 ) {
    int n = mat.size() / dim_divisor;
    Rcpp::NumericVector elev(n);
    Rcpp::NumericVector meas(n);
    if( dim_divisor == 3 ) {
      elev = mat(_, 2);
    } else if ( dim_divisor == 4 ) { 
      elev = mat(_, 2);
      meas = mat(_, 3);
    }
    encodedString = encode_polyline(elev, meas);
    addToStream(oszm, encodedString);
  }
  
}

void write_matrix_list(std::ostringstream& os, std::ostringstream& oszm, Rcpp::List lst, 
                       Rcpp::CharacterVector& sfg_dim, int dim_divisor ) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
   
  size_t len = lst.length();
   
  for (size_t j = 0; j < len; j++){
     encode_matrix(os, oszm, lst[j], sfg_dim, dim_divisor);
  }
  addToStream(os, SPLIT_CHAR);
  
  if (dim_divisor > 2) {
    addToStream(oszm, SPLIT_CHAR);
  }
}

void write_geometry(std::ostringstream& os, std::ostringstream& oszm, SEXP s, 
                    Rcpp::CharacterVector& sfg_dim, int dim_divisor) {
  
  //Rcpp::Rcout << "sfg_dim: " << sfg_dim << std::endl;
  Rcpp::CharacterVector cls_attr = getSfClass(s);
  
  write_data(os, oszm, sfg_dim, dim_divisor, s, cls_attr[1], 0);
}

void write_data(std::ostringstream& os, std::ostringstream& oszm, Rcpp::CharacterVector& sfg_dim, int dim_divisor, 
                SEXP sfc, const char *cls = NULL, int srid = 0) {
  
  int tp;
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
    write_geometry(os, oszm, sfc, sfg_dim, dim_divisor);
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

// [[Rcpp::export]]
Rcpp::List rcpp_encodeSfGeometry(Rcpp::List sfc, bool strip){
  
  Rcpp::CharacterVector cls_attr = sfc.attr("class");
  //Rcpp::Rcout << "cls_attr: " << cls_attr << std::endl;
  
  Rcpp::CharacterVector sfg_dim;
  int dim_divisor;
  
  Rcpp::List output(sfc.size());
  Rcpp::List output_zm(sfc.size());
  int lastItem;
  
  for (int i = 0; i < sfc.size(); i++){

    std::ostringstream os;
    std::ostringstream oszm;   // TODO(fill oszm stream)
    Rcpp::checkUserInterrupt();
    
    // TODO(sfc[i] class will tell us if XY[ZM] dimensions)
    Rcpp::List sfg(1);
    sfg[0] = sfc[i];
    geometry_dim(sfg, sfg_dim);
    
    make_dim_divisor(sfg_dim[0], &dim_divisor);
    //Rcpp::Rcout << "dim divisor: " << dim_divisor << std::endl;
    
    write_data(os, oszm, sfg_dim, dim_divisor, sfc[i], cls_attr[0], 0);

    std::string str = os.str();
    std::string zmstr = oszm.str();
    
    //Rcpp::Rcout << "zm stream: " << zmstr << std::endl;
    
    std::vector< std::string > strs = split(str, ' ');
    std::vector< std::string > zmstrs = split(zmstr, ' ');
    
    lastItem = strs.size() - 1;
    
    if (strs[lastItem] == "-") {
      strs.erase(strs.end() - 1);
      if (dim_divisor > 2 ) {
        zmstrs.erase(zmstrs.end() - 1);
      }
    }

    Rcpp::CharacterVector sv = wrap( strs );
    Rcpp::CharacterVector zmsv = wrap( zmstrs );

    if(strip == FALSE) {
      sv.attr("sfc") = getSfClass(sfc[i]);
    }
    output[i] = sv;
    output_zm[i] = zmsv;
    //output[i] = Rcpp::List::create(sv, zmsv);
  }
  return Rcpp::List::create(
    _["XY"] = output,
    _["ZM"] = output_zm
  );
  //return output;
}