// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP


#include <b/geometry/core/closure.hpp>
#include <b/geometry/core/coordinate_dimension.hpp>
#include <b/geometry/core/coordinate_type.hpp>
#include <b/geometry/core/cs.hpp>
#include <b/geometry/core/point_order.hpp>
#include <b/geometry/core/point_type.hpp>
#include <b/geometry/core/tag.hpp>
#include <b/geometry/core/tags.hpp>

#include <b/geometry/geometries/box.hpp>
#include <b/geometry/geometries/linestring.hpp>
#include <b/geometry/geometries/point.hpp>
#include <b/geometry/geometries/ring.hpp>

#include <b/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace helper_geometries
{

template
<
    typename Point,
    typename NewCoordinateType,
    typename NewUnits,
    typename CS_Tag = cs_tag_t<Point>
>
struct helper_point
{
    typedef model::point
        <
            NewCoordinateType,
            dimension<Point>::value,
            typename cs_tag_to_coordinate_system<NewUnits, CS_Tag>::type
        > type;
};


}} // detail::helper_geometries


namespace detail_dispatch
{


template
<
    typename Geometry,
    typename NewCoordinateType,
    typename NewUnits,
    typename Tag = typename tag<Geometry>::type>
struct helper_geometry : not_implemented<Geometry>
{};


template <typename Point, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Point, NewCoordinateType, NewUnits, point_tag>
{
    using type = typename detail::helper_geometries::helper_point
        <
            Point, NewCoordinateType, NewUnits
        >::type;
};


template <typename Box, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Box, NewCoordinateType, NewUnits, box_tag>
{
    using type = model::box
        <
            typename helper_geometry
                <
                    point_type_t<Box>, NewCoordinateType, NewUnits
                >::type
        >;
};


template <typename Linestring, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Linestring, NewCoordinateType, NewUnits, linestring_tag>
{
    using type = model::linestring
        <
            typename helper_geometry
                <
                    point_type_t<Linestring>, NewCoordinateType, NewUnits
                >::type
        >;
};

template <typename Ring, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Ring, NewCoordinateType, NewUnits, ring_tag>
{
    using type = model::ring
        <
            typename helper_geometry
                <
                    point_type_t<Ring>, NewCoordinateType, NewUnits
                >::type,
            point_order<Ring>::value != counterclockwise,
            closure<Ring>::value != open
        >;
};


} // detail_dispatch


// Meta-function that provides a new helper geometry of the same kind as
// the input geometry and the same coordinate system type,
// but with a possibly different coordinate type and coordinate system units
template
<
    typename Geometry,
    typename NewCoordinateType = typename coordinate_type<Geometry>::type,
    typename NewUnits = typename detail::cs_angular_units<Geometry>::type
>
struct helper_geometry
{
    using type = typename detail_dispatch::helper_geometry
        <
            Geometry, NewCoordinateType, NewUnits
        >::type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP
