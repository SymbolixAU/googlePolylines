/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2017-2017
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP
#define BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <b/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <b/move/detail/config_begin.hpp>
#include <b/move/detail/workaround.hpp>
#include <b/move/detail/pointer_element.hpp>

namespace boost {
namespace movelib {

template <class T>
BOOST_MOVE_FORCEINLINE T* to_raw_pointer(T* p)
{  return p; }

template <class Pointer>
inline typename boost::movelib::pointer_element<Pointer>::type*
to_raw_pointer(const Pointer &p)
{  return ::boost::movelib::to_raw_pointer(p.operator->());  }

} //namespace movelib
} //namespace boost

#include <b/move/detail/config_end.hpp>

#endif //BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP
