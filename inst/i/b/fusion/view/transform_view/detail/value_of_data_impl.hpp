/*=============================================================================
    Copyright (c) 2022 Denis Mikhailov
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_TRANSFORM_VIEW_VALUE_OF_IMPL_JAN_9_2022_0354PM)
#define BOOST_FUSION_TRANSFORM_VIEW_VALUE_OF_IMPL_JAN_9_2022_0354PM

#include <b/fusion/support/config.hpp>
#include <b/fusion/iterator/deref.hpp>
#include <b/type_traits/remove_reference.hpp>
#include <b/type_traits/remove_const.hpp>
#include <b/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_of_data_impl;

        // Unary Version
        template<>
        struct value_of_data_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type transformed_type;
                typedef typename boost::remove_reference<transformed_type>::type transformed_type_unref;
                typedef typename boost::remove_const<transformed_type_unref>::type transformed_type_unconst;

                typedef typename transformed_type_unconst::second_type type;
            };
        };

        // Binary Version is not supported with Associative Sequence
    }
}}
#endif
