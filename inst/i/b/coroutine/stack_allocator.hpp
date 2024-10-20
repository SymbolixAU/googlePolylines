
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STACK_ALLOCATOR_H

#include <cstddef>

#include <b/config.hpp>

#include <b/context/detail/config.hpp>
#include <b/coroutine/segmented_stack_allocator.hpp>
#include <b/coroutine/standard_stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

#if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack_allocator   stack_allocator;
#else
typedef standard_stack_allocator    stack_allocator;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_ALLOCATOR_H
