//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP

#include <b/chrono/config.hpp>
#include <b/version.hpp>
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#include <b/chrono/thread_clock.hpp>
#include <b/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <b/system/system_error.hpp>
#endif
#include <b/throw_exception.hpp>
#include <b/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <b/chrono/detail/inlined/win/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <b/chrono/detail/inlined/mac/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <b/chrono/detail/inlined/posix/thread_clock.hpp>

#endif  // POSIX

#endif
#endif
