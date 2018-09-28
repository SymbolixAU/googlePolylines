#ifndef GOOGLEPOLYLINES_VARIANTS_H
#define GOOGLEPOLYLINES_VARIANTS_H

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_linestring.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <iostream>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::multi_point<point_type> multi_point_type;
typedef boost::geometry::model::linestring<point_type> linestring_type;
typedef boost::geometry::model::multi_linestring<linestring_type> multi_linestring_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::ring<polygon_type> ring_type;
typedef boost::geometry::model::multi_polygon<polygon_type> multi_polygon_type;

#endif