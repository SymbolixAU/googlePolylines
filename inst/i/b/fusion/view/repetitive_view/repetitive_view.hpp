/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED

#include <b/fusion/support/config.hpp>
#include <b/type_traits/remove_reference.hpp>
#include <b/mpl/if.hpp>

#include <b/fusion/support/is_view.hpp>
#include <b/fusion/support/category_of.hpp>

#include <b/fusion/view/repetitive_view/detail/begin_impl.hpp>
#include <b/fusion/view/repetitive_view/detail/end_impl.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct repetitive_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequence> struct repetitive_view 
        : sequence_base< repetitive_view<Sequence> >
    {
        typedef repetitive_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef single_pass_traversal_tag category;

        typedef typename boost::remove_reference<Sequence>::type sequence_type;
        typedef typename 
            mpl::if_<traits::is_view<Sequence>, Sequence, sequence_type&>::type
        stored_seq_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view(Sequence& in_seq)
            : seq(in_seq) {}

        stored_seq_type seq;
    };

}}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#endif
