#include <Rcpp.h>
using namespace Rcpp;

#ifndef GOOGLEVARIANTS_H
#define GOOGLEVARIANTS_H

#include <b/geometry.hpp>
#include <b/geometry/geometries/linestring.hpp>
#include <b/geometry/geometries/point_xy.hpp>
#include <b/geometry/geometries/multi_point.hpp>
#include <b/geometry/geometries/polygon.hpp>
#include <b/geometry/geometries/multi_linestring.hpp>
#include <b/geometry/geometries/multi_polygon.hpp>

namespace bg = boost::geometry;
namespace bgm = bg::model;

typedef bg::model::d2::point_xy<double> point_type;
typedef bgm::multi_point<point_type> multi_point_type;
typedef bgm::linestring<point_type> linestring_type;
typedef bgm::multi_linestring<linestring_type> multi_linestring_type;
typedef bgm::polygon<point_type> polygon_type;
typedef bgm::ring<polygon_type> ring_type;
typedef bgm::multi_polygon<polygon_type> multi_polygon_type;

#endif
