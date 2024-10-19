// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_HPP
#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_HPP

#include <b/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct are_tagged_arguments;
}} // namespace boost::parameter

#include <b/parameter/aux_/is_tagged_argument.hpp>

namespace boost { namespace parameter {

    template <typename TaggedArg0>
    struct are_tagged_arguments<TaggedArg0>
      : ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
    {
    };
}} // namespace boost::parameter

#include <b/mpl/bool.hpp>
#include <b/mpl/if.hpp>

namespace boost { namespace parameter {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct are_tagged_arguments
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
          , ::boost::parameter::are_tagged_arguments<TaggedArgs...>
          , ::boost::mpl::false_
        >::type
    {
    };
}} // namespace boost::parameter

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z(z, n, false_t) , false_t>
/**/

#include <b/parameter/aux_/is_tagged_argument.hpp>
#include <b/mpl/eval_if.hpp>
#include <b/preprocessor/cat.hpp>

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z(z, n, prefix)           \
    ::boost::mpl::eval_if<                                                   \
        ::boost::parameter::aux::is_tagged_argument<BOOST_PP_CAT(prefix, n)>,
/**/

#include <b/parameter/aux_/void.hpp>
#include <b/mpl/bool.hpp>
#include <b/preprocessor/arithmetic/sub.hpp>
#include <b/preprocessor/facilities/intercept.hpp>
#include <b/preprocessor/repetition/repeat.hpp>
#include <b/preprocessor/repetition/enum_params.hpp>
#include <b/preprocessor/repetition/enum_trailing_params.hpp>

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z(z, n, prefix)       \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    struct are_tagged_arguments<                                             \
        BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)                                 \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(                                     \
            z                                                                \
          , BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, n)               \
          , ::boost::parameter::void_ BOOST_PP_INTERCEPT                     \
        )                                                                    \
    > : BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z                     \
          , prefix                                                           \
        )                                                                    \
        ::boost::mpl::true_                                                  \
        BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z                       \
          , ::boost::mpl::false_                                             \
        )::type                                                              \
    {                                                                        \
    };
/**/

#include <b/preprocessor/arithmetic/inc.hpp>
#include <b/preprocessor/repetition/enum_binary_params.hpp>

namespace boost { namespace parameter {

    template <
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
          , typename TaggedArg
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct are_tagged_arguments;
}} // namespace boost::parameter

#include <b/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace parameter {

    BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
      , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z
      , TaggedArg
    )
}} // namespace boost::parameter

#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z
#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z
#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard

