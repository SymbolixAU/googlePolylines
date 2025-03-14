// Boost.Geometry

// Copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_EXPAND_HPP
#define BOOST_GEOMETRY_STRATEGY_EXPAND_HPP

#include <b/geometry/core/static_assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace expand { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this type.",
        Tag, CSTag);
};

}}} // namespace strategy::expand::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_EXPAND_HPP

