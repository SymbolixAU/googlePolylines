#include <Rcpp.h>
using namespace Rcpp;

#ifndef GOOGLEVARIANTS_H
#define GOOGLEVARIANTS_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_linestring.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <iostream>

namespace bg = boost::geometry;
namespace bgm = bg::model;


/*
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <boost/spirit/home/x3.hpp>
*/


/*
// https://stackoverflow.com/a/48045800/4002530
namespace detail {
  template <typename Variant> struct read_any_helper {
    
    static Variant call(std::string const& wkt) {
      Variant output;
      call_impl(wkt, output);
      return output;
    }
    
    using result_type = void;
    template <typename Geo> result_type operator()(std::string const& wkt, Geo& output) const {
      bg::read_wkt(wkt, output);
    }

  private:
    template <typename... T>
    static void call_impl(std::string const& wkt, boost::variant<T...>& output) {
      static auto const switch_ = gen_switch(output);
      if (parse(wkt.begin(), wkt.end(), switch_, output)) {
        boost::apply_visitor(boost::bind(read_any_helper{}, boost::ref(wkt), _1), output);
      } else {
        throw bg::read_wkt_exception("Unregistered type", wkt);
      }
    }
    
    template <typename... T>
    static auto gen_switch(boost::variant<T...> const&) {
      namespace x3 = boost::spirit::x3;
      x3::symbols<Variant> result;
      
      boost::fusion::for_each(boost::fusion::vector<T...>{}, [&result](auto&& seed) {
        auto const serialized = boost::lexical_cast<std::string>(bg::wkt(seed));
        
        std::string keyword;
        if (x3::parse(serialized.begin(), serialized.end(), +x3::alpha, keyword))
          result.add(keyword, std::forward<decltype(seed)>(seed));
        else
          throw std::logic_error(std::string("registering WKT for ") + typeid(seed).name());
      });
      
//      result.for_each([](auto& key, auto&&...) {
//        std::cout << "DEBUG: statically registered support for " << key << " type\n";
//      });
      
      return result;
    }
  };
}

*/

//using point_type = bgm::d2::point_xy<double>;

typedef bg::model::d2::point_xy<double> point_type;
//typedef bg::model::point <double , 2, bg::cs::geographic<bg::degree> > point_type;
//typedef bg::model::point <double , 2, bg::cs::spherical_equatorial<bg::degree> > point_type;
typedef bgm::multi_point<point_type> multi_point_type;
typedef bgm::linestring<point_type> linestring_type;
typedef bgm::multi_linestring<linestring_type> multi_linestring_type;
typedef bgm::polygon<point_type> polygon_type;
typedef bgm::ring<polygon_type> ring_type;
typedef bgm::multi_polygon<polygon_type> multi_polygon_type;

/*
typedef boost::variant<
  point_type,
  multi_point_type,
  linestring_type,
  multi_linestring_type,
  polygon_type,
  multi_polygon_type
> AnyGeo;

typedef boost::variant<
  linestring_type,
  multi_linestring_type,
  polygon_type,
  multi_polygon_type
> GeoIntersection;
*/

/*
template <typename Variant = AnyGeo>
Variant read_any_wkt(std::string const& wkt) {
  return detail::read_any_helper<Variant>::call(wkt);
}

template <typename Variant = GeoIntersection>
Variant read_intersection_wkt(std::string const& wkt) {
  return detail::read_any_helper<Variant>::call(wkt);
}
*/

#endif
