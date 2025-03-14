// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2024.
// Modifications copyright (c) 2024 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP

#include <cstddef>

#include <b/range/size.hpp>

#include <b/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <b/geometry/algorithms/detail/overlay/traversal_ring_creator.hpp>
#include <b/geometry/algorithms/detail/overlay/traversal_switch_detector.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


/*!
    \brief Traverses through intersection points / geometries
    \ingroup overlay
 */
template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1,
    typename Geometry2,
    overlay_type OverlayType,
    typename Backtrack = backtrack_check_self_intersections<Geometry1, Geometry2>
>
class traverse
{

    template <typename Turns>
    static void reset_visits(Turns& turns)
    {
        for (auto& turn : turns)
        {
            for (auto& op : turn.operations)
            {
                op.visited.reset();
            }
        }
    }


public :
    template
    <
        typename IntersectionStrategy,
        typename Turns,
        typename Rings,
        typename TurnInfoMap,
        typename Clusters,
        typename Visitor
    >
    static inline void apply(Geometry1 const& geometry1,
                Geometry2 const& geometry2,
                IntersectionStrategy const& intersection_strategy,
                Turns& turns, Rings& rings,
                TurnInfoMap& turn_info_map,
                Clusters& clusters,
                Visitor& visitor)
    {
        traversal_switch_detector
            <
                Reverse1, Reverse2, OverlayType,
                Geometry1, Geometry2,
                Turns, Clusters,
                Visitor
            > switch_detector(geometry1, geometry2, turns, clusters,
                   visitor);

        switch_detector.iterate();
        reset_visits(turns);

        traversal_ring_creator
            <
                Reverse1, Reverse2, OverlayType,
                Geometry1, Geometry2,
                Turns, TurnInfoMap, Clusters,
                IntersectionStrategy,
                Visitor,
                Backtrack
            > trav(geometry1, geometry2, turns, turn_info_map, clusters,
                   intersection_strategy, visitor);

        std::size_t finalized_ring_size = boost::size(rings);

        typename Backtrack::state_type state;

        trav.iterate(rings, finalized_ring_size, state);
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP
