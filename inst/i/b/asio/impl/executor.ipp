//
// impl/executor.ipp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXECUTOR_IPP
#define BOOST_ASIO_IMPL_EXECUTOR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <b/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#include <b/asio/executor.hpp>

#include <b/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

bad_executor::bad_executor() noexcept
{
}

const char* bad_executor::what() const noexcept
{
  return "bad executor";
}

} // namespace asio
} // namespace boost

#include <b/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#endif // BOOST_ASIO_IMPL_EXECUTOR_IPP
