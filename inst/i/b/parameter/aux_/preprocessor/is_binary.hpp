// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP

#include <b/config.hpp>
#include <b/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <b/preprocessor/punctuation/comma.hpp>
#include <b/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_BINARY_C x BOOST_PP_COMMA() 0)
/**/
#include <b/preprocessor/punctuation/paren.hpp>
#include <b/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_BINARY_C(x,y) \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <b/preprocessor/detail/is_binary.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) BOOST_PP_IS_BINARY(x)
#endif

#endif  // include guard

