// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MATCH_DWA2005714_HPP
#define BOOST_PARAMETER_MATCH_DWA2005714_HPP

#include <b/parameter/config.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#include <b/parameter/aux_/void.hpp>
#include <b/preprocessor/arithmetic/sub.hpp>
#include <b/preprocessor/facilities/intercept.hpp>
#include <b/preprocessor/repetition/enum_trailing_params.hpp>
#include <b/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    BOOST_PP_ENUM_TRAILING_PARAMS(                                           \
        BOOST_PP_SUB(                                                        \
            BOOST_PARAMETER_MAX_ARITY                                        \
          , BOOST_PP_SEQ_SIZE(ArgTypes)                                      \
        )                                                                    \
      , ::boost::parameter::void_ BOOST_PP_INTERCEPT                         \
    )
/**/
#else
#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)
#endif

#include <b/parameter/aux_/preprocessor/seq_enum.hpp>

//
// Generates, e.g.
//
//    typename dfs_params::match<A1,A2>::type name = dfs_params()
//
// with workarounds for Borland compatibility.
//
#define BOOST_PARAMETER_MATCH(ParameterSpec, ArgTypes, name)                 \
    typename ParameterSpec::match<                                           \
        BOOST_PARAMETER_SEQ_ENUM(ArgTypes)                                   \
        BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    >::type name = ParameterSpec()
/**/

#endif  // include guard

