#ifndef BOOST_SYSTEM_ERRC_HPP_INCLUDED
#define BOOST_SYSTEM_ERRC_HPP_INCLUDED

// Copyright Beman Dawes 2006, 2007
// Copyright Christoper Kohlhoff 2007
// Copyright Peter Dimov 2017, 2018, 2020
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See library home page at http://www.boost.org/libs/system

#include <b/system/detail/errc.hpp>
#include <b/system/detail/error_code.hpp>
#include <b/system/detail/error_condition.hpp>
#include <b/system/detail/generic_category.hpp>
#include <b/system/detail/error_category_impl.hpp>
#include <b/system/detail/config.hpp>
#include <b/assert/source_location.hpp>
#include <b/config.hpp>

namespace boost
{

namespace system
{

// make_* functions for errc::errc_t

namespace errc
{

// explicit conversion:
BOOST_SYSTEM_CONSTEXPR inline error_code make_error_code( errc_t e ) BOOST_NOEXCEPT
{
    return error_code( e, generic_category() );
}

// explicit conversion:
inline error_code make_error_code( errc_t e, boost::source_location const * loc ) BOOST_NOEXCEPT
{
    return error_code( e, generic_category(), loc );
}

// implicit conversion:
BOOST_SYSTEM_CONSTEXPR inline error_condition make_error_condition( errc_t e ) BOOST_NOEXCEPT
{
    return error_condition( e, generic_category() );
}

} // namespace errc

} // namespace system

} // namespace boost

#endif // #ifndef BOOST_SYSTEM_ERRC_HPP_INCLUDED
