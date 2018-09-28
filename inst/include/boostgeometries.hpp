#ifndef GOOGLEPOLYLINES_BOOST_GEOMETRIES_H
#define GOOGLEPOLYLINES_BOOST_GEOMETRIES_H

#include <Rcpp.h>
#include <boost/geometry.hpp>
#include "googlePolylines.h"
#include "encode/encode.hpp"
#include "utils/utils.hpp"
#include "variants.h"

namespace bg = boost::geometry;

namespace googlepolylines {
namespace boostgeometries {

  template <typename Point>
  inline void encode_wkt_point(Point const& p, std::ostringstream& os) {
    
    googlepolylines::global_vars::lons.clear();
    googlepolylines::global_vars::lats.clear();
    
    googlepolylines::global_vars::lons.push_back( bg::get<0>(p));
    googlepolylines::global_vars::lats.push_back( bg::get<1>(p));
    
    googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
    
    googlepolylines::utils::addToStream(os);
  }
  
  
  template <typename MultiPoint>
  inline void encode_wkt_multipoint(MultiPoint const& mp, std::ostringstream& os) {
    
    typedef typename boost::range_iterator
    < multi_point_type const >::type iterator_type;
    
    for ( iterator_type it = boost::begin(mp); it != boost::end(mp); ++it ) {
      encode_wkt_point(*it, os);
      }
    
  }
  
  template <typename LineString>
  inline void encode_wkt_linestring(LineString const& ls, std::ostringstream& os) {
    
    // works for RINGS (because it's templated)
    
    typedef typename boost::range_iterator
    < linestring_type const >::type iterator_type;
    
    int i = 0;
    for ( iterator_type it = boost::begin(ls); it != boost::end(ls); ++it ) {
      googlepolylines::global_vars::lons.push_back(bg::get<0>(*it));
      googlepolylines::global_vars::lats.push_back(bg::get<1>(*it));
      i++;
    }
    googlepolylines::global_vars::encodedString = googlepolylines::encode::encode_polyline();
    googlepolylines::utils::addToStream(os);
  }
  
  template <typename MultiLinestring>
  inline void encode_wkt_multi_linestring(MultiLinestring const& mls, std::ostringstream& os) {
    
    typedef typename boost::range_iterator
    < multi_linestring_type const >::type iterator_type;
    
    for ( iterator_type it = boost::begin(mls); it != boost::end(mls); ++it ) {
      encode_wkt_linestring(*it, os);
    }
  }
  
  template <typename Polygon>
  inline void encode_wkt_polygon(Polygon const& pl, std::ostringstream& os) {
    
    encode_wkt_linestring(pl.outer(), os);
    
    // perhaps use
    // https://stackoverflow.com/questions/7722087/getting-the-coordinates-of-points-from-a-boost-geometry-polygon/7748091#7748091
    // https://stackoverflow.com/questions/37071031/how-to-get-a-polygon-from-boostgeometrymodelpolygon
    for (auto& i: pl.inners() ) {
      encode_wkt_linestring(i, os);
    }
  }
  
  template <typename MultiPolygon>
  inline void encode_wkt_multi_polygon(MultiPolygon const& mpl, std::ostringstream& os) {
    
    typedef typename boost::range_iterator
    < multi_polygon_type const >::type iterator_type;
    
    googlepolylines::global_vars::encodedString = SPLIT_CHAR;
    for (iterator_type it = boost::begin(mpl); it != boost::end(mpl); ++it) {
      encode_wkt_polygon(*it, os);
      googlepolylines::utils::addToStream(os);
    }
  }

} // namespace boostgeometries
} // namespace googlepolylines


#endif
