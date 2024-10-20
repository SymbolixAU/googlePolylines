//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <b/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <b/interprocess/detail/config_begin.hpp>
#include <b/interprocess/detail/workaround.hpp>
#include <b/interprocess/sync/windows/mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

//Windows mutex is already recursive
class winapi_recursive_mutex
   : public winapi_mutex
{
   winapi_recursive_mutex(const winapi_recursive_mutex &);
   winapi_recursive_mutex &operator=(const winapi_recursive_mutex &);
   public:
   winapi_recursive_mutex() : winapi_mutex() {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {


#include <b/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
