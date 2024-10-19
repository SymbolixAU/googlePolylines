// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_RANDOM_LAYOUT_HPP
#define BOOST_GRAPH_RANDOM_LAYOUT_HPP

#include <b/graph/graph_traits.hpp>
#include <b/random/uniform_int.hpp>
#include <b/random/uniform_01.hpp>
#include <b/random/uniform_real.hpp>
#include <b/type_traits/is_integral.hpp>
#include <b/mpl/if.hpp>
#include <b/graph/iteration_macros.hpp>

namespace boost
{

template < typename Topology, typename Graph, typename PositionMap >
void random_graph_layout(
    const Graph& g, PositionMap position_map, const Topology& topology)
{
    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        put(position_map, v, topology.random_point());
    }
}

} // end namespace boost

#endif // BOOST_GRAPH_RANDOM_LAYOUT_HPP
