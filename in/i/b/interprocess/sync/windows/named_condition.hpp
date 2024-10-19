 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <b/interprocess/detail/config_begin.hpp>
#include <b/interprocess/detail/workaround.hpp>

#include <b/interprocess/sync/cv_status.hpp>
#include <b/interprocess/sync/windows/named_condition_any.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

typedef winapi_named_condition_any winapi_named_condition;

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <b/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
