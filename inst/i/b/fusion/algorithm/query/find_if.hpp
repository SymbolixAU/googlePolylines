/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1108)
#define FUSION_FIND_IF_05052005_1108

#include <b/fusion/support/config.hpp>
#include <b/fusion/algorithm/query/find_if_fwd.hpp>
#include <b/fusion/algorithm/query/detail/find_if.hpp>
#include <b/fusion/algorithm/query/detail/segmented_find_if.hpp>
#include <b/fusion/iterator/value_of.hpp>
#include <b/fusion/support/is_segmented.hpp>
#include <b/utility/enable_if.hpp>
#include <b/type_traits/is_const.hpp>
#include <b/mpl/bind.hpp>
#include <b/mpl/lambda.hpp>
#include <b/mpl/placeholders.hpp>
#include <b/mpl/quote.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find_if<Sequence, Pred>
              , detail::result_of_find_if<
                    Sequence,
                    mpl::bind1<
                        typename mpl::lambda<Pred>::type
                      , mpl::bind1<mpl::quote1<value_of>, mpl::_1>
                    >
                >
            >::type
        {};
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq)
    {
        typedef typename result_of::find_if<Sequence, Pred>::filter filter;
        return filter::call(seq);
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq)
    {
        typedef typename result_of::find_if<Sequence const, Pred>::filter filter;
        return filter::call(seq);
    }
}}

#endif
