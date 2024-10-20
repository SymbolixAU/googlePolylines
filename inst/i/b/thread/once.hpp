#ifndef BOOST_THREAD_ONCE_HPP
#define BOOST_THREAD_ONCE_HPP

//  once.hpp
//
//  (C) Copyright 2006-7 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <b/thread/detail/config.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code
#endif

#include <b/thread/detail/platform.hpp>
#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include <b/thread/win32/once.hpp>
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD)
#if defined BOOST_THREAD_ONCE_FAST_EPOCH
#include <b/thread/pthread/once.hpp>
#elif defined BOOST_THREAD_ONCE_ATOMIC
#include <b/thread/pthread/once_atomic.hpp>
#else
#error "Once Not Implemented"
#endif
#else
#error "Boost threads unavailable on this platform"
#endif

#include <b/config/abi_prefix.hpp>

namespace boost
{
  // template<class Callable, class ...Args> void
  // call_once(once_flag& flag, Callable&& func, Args&&... args);
template<typename Function>
inline void call_once(Function func,once_flag& flag)
//inline void call_once(void (*func)(),once_flag& flag)
    {
        call_once(flag,func);
    }
}

#include <b/config/abi_suffix.hpp>

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif
