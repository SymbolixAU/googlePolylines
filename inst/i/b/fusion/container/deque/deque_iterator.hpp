/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_ITERATOR_26112006_2154)
#define BOOST_FUSION_DEQUE_ITERATOR_26112006_2154

#include <b/fusion/support/config.hpp>
#include <b/fusion/iterator/iterator_facade.hpp>
#include <b/fusion/container/deque/detail/keyed_element.hpp>
#include <b/mpl/int.hpp>
#include <b/mpl/minus.hpp>
#include <b/mpl/equal_to.hpp>
#include <b/mpl/identity.hpp>
#include <b/mpl/if.hpp>
#include <b/type_traits/is_const.hpp>
#include <b/type_traits/add_const.hpp>
#include <b/type_traits/add_reference.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion {

    struct bidirectional_traversal_tag;

    template <typename Seq, int Pos>
    struct deque_iterator
        : iterator_facade<deque_iterator<Seq, Pos>, bidirectional_traversal_tag>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
            : detail::keyed_element_value_at<
            typename Iterator::sequence, typename Iterator::index>
        {};

        template<typename Iterator>
        struct deref
        {
            typedef typename detail::keyed_element_value_at<
                typename Iterator::sequence, typename Iterator::index>::type element_type;

            typedef typename add_reference<
                typename mpl::eval_if<
                is_const<typename Iterator::sequence>,
                add_const<element_type>,
                mpl::identity<element_type> >::type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef deque_iterator<sequence, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }
        };

        template<typename Iterator>
        struct next
            : advance<Iterator, mpl::int_<1> >
        {};

        template<typename Iterator>
        struct prior
            : advance<Iterator, mpl::int_<-1> >
        {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template<typename I1, typename I2>
        struct equal_to
            : mpl::equal_to<typename I1::index, typename I2::index>
        {};

        Seq& seq_;
    };

}}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::deque_iterator<Seq, Pos> >
    { };
}
#endif

#endif
