
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <b/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <b/context/fiber_winfib.hpp>
#else
#include <b/context/fiber_fcontext.hpp>
#endif
