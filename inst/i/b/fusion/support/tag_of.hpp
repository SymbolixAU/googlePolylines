/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAG_OF_09232005_0845)
#define FUSION_TAG_OF_09232005_0845

#include <b/fusion/support/config.hpp>
#include <b/utility/enable_if.hpp>
#include <b/type_traits/remove_const.hpp>
#include <b/fusion/support/tag_of_fwd.hpp>
#include <b/fusion/support/detail/is_mpl_sequence.hpp>
#include <b/mpl/has_xxx.hpp>
#include <b/mpl/identity.hpp>
#include <b/mpl/assert.hpp>
#include <b/mpl/bool.hpp>
#include <b/mpl/if.hpp>
#include <b/config/no_tr1/utility.hpp>

namespace boost
{
    template <typename T, std::size_t N>
    class array; // forward

    namespace tuples
    {
        struct null_type;

        template <
            class T0, class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8, class T9
        >
        class tuple;

        template <class Head, class Tail>
        struct cons;
    }
}

namespace boost { namespace fusion
{
    struct non_fusion_tag;
    struct mpl_sequence_tag;

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(fusion_tag)

        template<typename Sequence, typename Active=void>
        struct tag_of_fallback
        {
            typedef non_fusion_tag type;
        };

        template <typename Sequence, typename Active>
        struct tag_of_impl
          : mpl::if_<fusion::detail::is_mpl_sequence<Sequence>,
              mpl::identity<mpl_sequence_tag>,
              mpl::identity<typename tag_of_fallback<Sequence>::type> >::type
        {};

        template <typename Sequence>
        struct tag_of_impl<
            Sequence
          , typename boost::enable_if<detail::has_fusion_tag<Sequence> >::type>
        {
            typedef typename Sequence::fusion_tag type;
        };
    }

    namespace traits
    {
        template <typename Sequence, typename Active>
        struct tag_of
            : boost::fusion::detail::tag_of_impl<Sequence, Active>
        {};
    }

    namespace detail
    {
        template<typename T>
        struct tag_of
            : traits::tag_of<typename remove_const<T>::type>
        {};
    }
}}
#endif
