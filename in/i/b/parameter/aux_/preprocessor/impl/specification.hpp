// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP

#include <b/parameter/optional.hpp>

// Helper macros for BOOST_PARAMETER_SPECIFICATION_ELEM_R.
#define BOOST_PARAMETER_QUALIFIED_TAG_optional(tag)                          \
    optional<tag
/**/

#include <b/parameter/required.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_required(tag)                          \
    required<tag
/**/

#include <b/parameter/deduced.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_optional(tag)                  \
    optional< ::boost::parameter::deduced<tag>
/**/

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_required(tag)                  \
    required< ::boost::parameter::deduced<tag>
/**/

#include <b/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <b/parameter/config.hpp>
#include <b/preprocessor/punctuation/comma_if.hpp>
#include <b/preprocessor/cat.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

#include <b/parameter/aux_/use_default.hpp>

#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , ::boost::parameter::aux::use_default                                 \
    >
/**/

#else   // !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

#include <b/parameter/aux_/pp_impl/unwrap_predicate.hpp>

// Expands to each boost::parameter::parameters<> element type.
#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , typename ::boost::parameter::aux::unwrap_predicate<                  \
            void BOOST_PARAMETER_FN_ARG_PRED(elem)                           \
        >::type                                                              \
    >
/**/

#endif  // Borland workarounds needed.

#include <b/parameter/parameters.hpp>
#include <b/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <b/preprocessor/control/if.hpp>
#include <b/preprocessor/seq/for_each_i.hpp>

// Expands to a boost::parameter::parameters<> specialization for the
// function named base.  Used by BOOST_PARAMETER_CONSTRUCTOR_AUX and
// BOOST_PARAMETER_FUNCTION_HEAD for their respective ParameterSpec models.
#define BOOST_PARAMETER_SPECIFICATION(tag_ns, base, split_args, is_const)    \
    template <typename BoostParameterDummy>                                  \
    struct BOOST_PP_CAT(                                                     \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    ) : ::boost::parameter::parameters<                                      \
            BOOST_PP_SEQ_FOR_EACH_I(                                         \
                BOOST_PARAMETER_SPECIFICATION_ELEM_R, tag_ns, split_args     \
            )                                                                \
        >                                                                    \
    {                                                                        \
    };                                                                       \
    typedef BOOST_PP_CAT(                                                    \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )<int>
/**/

#endif  // include guard

