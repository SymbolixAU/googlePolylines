/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_ITERATOR_05042005_0635)
#define FUSION_VECTOR_ITERATOR_05042005_0635

#include <b/fusion/support/config.hpp>
#include <b/fusion/support/iterator_base.hpp>
#include <b/fusion/container/vector/detail/deref_impl.hpp>
#include <b/fusion/container/vector/detail/value_of_impl.hpp>
#include <b/fusion/container/vector/detail/next_impl.hpp>
#include <b/fusion/container/vector/detail/prior_impl.hpp>
#include <b/fusion/container/vector/detail/equal_to_impl.hpp>
#include <b/fusion/container/vector/detail/distance_impl.hpp>
#include <b/fusion/container/vector/detail/advance_impl.hpp>
#include <b/type_traits/add_const.hpp>
#include <b/mpl/int.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    struct random_access_traversal_tag;

    template <typename Vector, int N>
    struct vector_iterator_identity;

    template <typename Vector, int N>
    struct vector_iterator : iterator_base<vector_iterator<Vector, N> >
    {
        typedef mpl::int_<N> index;
        typedef Vector vector;
        typedef vector_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef vector_iterator_identity<
            typename add_const<Vector>::type, N> identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_iterator(Vector& in_vec)
            : vec(in_vec) {}

        Vector& vec;
    };
}}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Vector, int N>
    struct iterator_traits< ::boost::fusion::vector_iterator<Vector, N> >
    { };
}
#endif

#endif

