// Boost.Geometry

// Copyright (c) 2015-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

#include <type_traits>

#include <b/geometry/core/coordinate_type.hpp>
#include <b/geometry/util/has_nan_coordinate.hpp>
#include <b/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct is_not_finite
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return ! boost::math::isfinite(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_non_finite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::is_not_finite,
            std::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP
