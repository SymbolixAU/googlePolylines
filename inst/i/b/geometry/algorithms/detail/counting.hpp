// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

#include <cstddef>

#include <b/range/begin.hpp>
#include <b/range/end.hpp>

#include <b/geometry/core/exterior_ring.hpp>
#include <b/geometry/core/interior_rings.hpp>

#include <b/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace counting
{


template <std::size_t D>
struct other_count
{
    template <typename Geometry>
    static inline std::size_t apply(Geometry const&)
    {
        return D;
    }

    template <typename Geometry>
    static inline std::size_t apply(Geometry const&, bool)
    {
        return D;
    }
};


template <typename RangeCount>
struct polygon_count
{
    template <typename Polygon>
    static inline std::size_t apply(Polygon const& poly)
    {
        std::size_t n = RangeCount::apply(exterior_ring(poly));

        auto const& rings = interior_rings(poly);
        for (auto it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            n += RangeCount::apply(*it);
        }

        return n;
    }
};


template <typename SingleCount>
struct multi_count
{
    template <typename MultiGeometry>
    static inline std::size_t apply(MultiGeometry const& multi)
    {
        std::size_t n = 0;
        for (auto it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            n += SingleCount::apply(*it);
        }
        return n;
    }
};


}} // namespace detail::counting
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP
