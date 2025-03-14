/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED

#include <b/fusion/support/config.hpp>
#include <b/mpl/bool.hpp>
#include <b/type_traits/remove_reference.hpp>
#include <b/fusion/support/tag_of.hpp>
#include <b/fusion/sequence/intrinsic_fwd.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion { namespace detail
{
    struct segment_sequence_tag {};

    // Here, Sequence is a sequence of ranges (which may or may not be
    // segmented).
    template<typename Sequence>
    struct segment_sequence
        : sequence_base<segment_sequence<Sequence> >
    {
        typedef fusion_sequence_tag tag;
        typedef segment_sequence_tag fusion_tag;
        typedef typename Sequence::is_view is_view;
        typedef typename Sequence::category category;
        typedef Sequence sequence_type;
        sequence_type sequence;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED explicit segment_sequence(Sequence const & seq)
            : sequence(seq)
        {}
    };
}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

namespace extension
{
    template<typename Tag>
    struct is_segmented_impl;

    template<>
    struct is_segmented_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
            : mpl::true_
        {};
    };

    template<typename Tag>
    struct segments_impl;

    template<>
    struct segments_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::sequence_type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence & seq)
            {
                return seq.sequence;
            }
        };
    };
}}}

#endif
