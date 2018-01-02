#include <Rcpp.h>
using namespace Rcpp;

#ifndef GOOGLEWKT_H
#define GOOGLEWKT_H

#define UNKNOWN           0
#define POINT             1
#define MULTIPOINT        2
#define LINESTRING        3
#define MULTILINESTRING   4
#define POLYGON           5
#define MULTIPOLYGON      6


void polylineToWKT(std::ostringstream& os, std::string encoded);

std::string geomFromWKT(std::string& pl);


#endif
