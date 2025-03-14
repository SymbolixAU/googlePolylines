// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

#include <b/range/begin.hpp>
#include <b/range/empty.hpp>
#include <b/range/end.hpp>
#include <b/range/value_type.hpp>

#include <b/geometry/core/closure.hpp>
#include <b/geometry/core/exterior_ring.hpp>
#include <b/geometry/core/interior_rings.hpp>
#include <b/geometry/core/ring_type.hpp>
#include <b/geometry/core/tags.hpp>

#include <b/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <b/geometry/algorithms/detail/is_valid/has_duplicates.hpp>

#include <b/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Ring, typename Strategy>
inline bool is_simple_ring(Ring const& ring, Strategy const& strategy)
{
    simplicity_failure_policy policy;
    return ! boost::empty(ring)
        && ! detail::is_valid::has_duplicates<Ring>::apply(ring, policy, strategy);
}

template <typename InteriorRings, typename Strategy>
inline bool are_simple_interior_rings(InteriorRings const& interior_rings,
                                      Strategy const& strategy)
{
    return std::all_of(boost::begin(interior_rings),
                       boost::end(interior_rings),
                       [&](auto const& r)
                       {
                           return is_simple_ring(r, strategy);
                       }); // non-simple ring not found
    // allow empty ring
}

template <typename Polygon, typename Strategy>
inline bool is_simple_polygon(Polygon const& polygon, Strategy const& strategy)
{
    return is_simple_ring(geometry::exterior_ring(polygon), strategy)
        && are_simple_interior_rings(geometry::interior_rings(polygon), strategy);
}


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A Ring is a Polygon.
// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Ring>
struct is_simple<Ring, ring_tag>
{
    template <typename Strategy>
    static inline bool apply(Ring const& ring, Strategy const& strategy)
    {
        return detail::is_simple::is_simple_ring(ring, strategy);
    }
};


// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for validity of Polygons): OGC 06-103r4 (6.1.11.1)
template <typename Polygon>
struct is_simple<Polygon, polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(Polygon const& polygon, Strategy const& strategy)
    {
        return detail::is_simple::is_simple_polygon(polygon, strategy);
    }
};


// Not clear what the definition is.
// Right now we consider a MultiPolygon as simple if it is valid.
//
// Reference (for validity of MultiPolygons): OGC 06-103r4 (6.1.14)
template <typename MultiPolygon>
struct is_simple<MultiPolygon, multi_polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(MultiPolygon const& multipolygon, Strategy const& strategy)
    {
        return std::none_of(boost::begin(multipolygon), boost::end(multipolygon),
                            [&](auto const& po) {
                                return ! detail::is_simple::is_simple_polygon(po, strategy);
                            }); // non-simple polygon not found
                                // allow empty multi-polygon
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP
