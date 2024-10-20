//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_STRING_HPP
#define BOOST_INTERPROCESS_CONTAINERS_STRING_HPP

#ifndef BOOST_CONFIG_HPP
#  include <b/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <b/interprocess/detail/config_begin.hpp>
#include <b/container/string.hpp>
#include <b/interprocess/containers/containers_fwd.hpp>

namespace boost {
namespace interprocess {

using boost::container::basic_string;
using boost::container::string;

}  //namespace interprocess {
}  //namespace boost {

#include <b/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_STRING_HPP
