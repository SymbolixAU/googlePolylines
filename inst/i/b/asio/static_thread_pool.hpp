//
// static_thread_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STATIC_THREAD_POOL_HPP
#define BOOST_ASIO_STATIC_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <b/asio/detail/config.hpp>
#include <b/asio/thread_pool.hpp>

#include <b/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

typedef thread_pool static_thread_pool;

} // namespace asio
} // namespace boost

#include <b/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_STATIC_THREAD_POOL_HPP
