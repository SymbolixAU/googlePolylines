/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt
    Copyright (c) 2021-2022 Denis Mikhailov

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <b/fusion/support/config.hpp>
#include <b/fusion/iterator/value_of_data.hpp>
#include <b/fusion/iterator/prior.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_of_data<
                    typename result_of::prior<
                        typename It::first_type
                    >::type
                >::type
            type;
        };
    };
}}}

#endif
