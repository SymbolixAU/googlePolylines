// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2023, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP

#include <algorithm>

#include <b/range/begin.hpp>
#include <b/range/end.hpp>
#include <b/range/value_type.hpp>

#include <b/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template <typename Geometry, typename Strategy, typename BinaryPredicate>
class unary_disjoint_geometry_to_query_geometry
{
public:
    unary_disjoint_geometry_to_query_geometry(Geometry const& geometry,
                                                  Strategy const& strategy)
        : m_geometry(geometry)
        , m_strategy(strategy)
    {}

    template <typename QueryGeometry>
    inline bool operator()(QueryGeometry const& query_geometry) const
    {
        return BinaryPredicate::apply(query_geometry, m_geometry, m_strategy);
    }

private:
    Geometry const& m_geometry;
    Strategy const& m_strategy;
};


template<typename MultiRange, typename ConstantSizeGeometry>
struct multirange_constant_size_geometry
{
    template <typename Strategy>
    static inline bool apply(MultiRange const& multirange,
                             ConstantSizeGeometry const& constant_size_geometry,
                             Strategy const& strategy)
    {
        using disjoint = unary_disjoint_geometry_to_query_geometry
            <
                ConstantSizeGeometry,
                Strategy,
                dispatch::disjoint
                    <
                        typename boost::range_value<MultiRange>::type,
                        ConstantSizeGeometry
                    >
            >;

        return std::all_of(boost::begin(multirange),
                           boost::end(multirange),
                           disjoint(constant_size_geometry, strategy));
    }

    template <typename Strategy>
    static inline bool apply(ConstantSizeGeometry const& constant_size_geometry,
                             MultiRange const& multirange,
                             Strategy const& strategy)
    {
        return apply(multirange, constant_size_geometry, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP
