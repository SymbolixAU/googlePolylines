#ifndef BOOST_BIND_DETAIL_IS_SAME_HPP_INCLUDED
#define BOOST_BIND_DETAIL_IS_SAME_HPP_INCLUDED

// is_same<T1,T2>::value is true when T1 == T2
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <b/config.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{
namespace _bi
{

template< class T1, class T2 > struct is_same
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template< class T > struct is_same< T, T >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

} // namespace _bi
} // namespace boost

#endif // #ifndef BOOST_BIND_DETAIL_IS_SAME_HPP_INCLUDED
