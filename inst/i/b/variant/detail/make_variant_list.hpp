//-----------------------------------------------------------------------------
// boost variant/detail/make_variant_list.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003 Eric Friedman, Itay Maman
// Copyright (c) 2013-2024 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VARIANT_DETAIL_MAKE_VARIANT_LIST_HPP
#define BOOST_VARIANT_DETAIL_MAKE_VARIANT_LIST_HPP

#include <b/variant/variant_fwd.hpp>

#include <b/mpl/list.hpp>
#include <b/preprocessor/cat.hpp>
#include <b/preprocessor/enum.hpp>

namespace boost { namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_variant_list
//
// Provides a MPL-compatible sequence with the specified non-void types
// as arguments.
//
// Rationale: see class template convert_void (variant_fwd.hpp) and using-
// declaration workaround (below).
//

template < typename... T >
struct make_variant_list
{
    typedef typename mpl::list< T... >::type type;
};

}}} // namespace boost::detail::variant

#endif // BOOST_VARIANT_DETAIL_MAKE_VARIANT_LIST_HPP
