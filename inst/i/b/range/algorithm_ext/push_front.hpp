// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_PUSH_FRONT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_PUSH_FRONT_HPP_INCLUDED

#include <b/range/config.hpp>
#include <b/range/concepts.hpp>
#include <b/range/difference_type.hpp>
#include <b/range/begin.hpp>
#include <b/range/end.hpp>
#include <b/range/detail/implementation_help.hpp>
#include <b/assert.hpp>

namespace boost
{
    namespace range
    {

template< class Container, class Range >
inline Container& push_front( Container& on, const Range& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Container> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const Range> ));
    BOOST_ASSERT_MSG(!range_detail::is_same_object(on, from),
        "cannot copy from a container to itself");
    on.insert( on.begin(), boost::begin(from), boost::end(from) );
    return on;
}

    } // namespace range
    using range::push_front;
} // namespace boost

#endif // include guard
