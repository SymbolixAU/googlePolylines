//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

#include <b/static_assert.hpp>

#include <b/compute/system.hpp>
#include <b/compute/command_queue.hpp>
#include <b/compute/algorithm/stable_partition.hpp>
#include <b/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// Partitions the elements in the range [\p first, \p last) according to
/// \p predicate. Order of the elements need not be preserved.
///
/// Space complexity: \Omega(3n)
///
/// \see is_partitioned() and stable_partition()
///
template<class Iterator, class UnaryPredicate>
inline Iterator partition(Iterator first,
                          Iterator last,
                          UnaryPredicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    return stable_partition(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP
