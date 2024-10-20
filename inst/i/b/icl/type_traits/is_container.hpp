/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <b/mpl/has_xxx.hpp>
#include <b/mpl/bool.hpp>
#include <b/mpl/and.hpp> 
#include <b/mpl/not.hpp> 
#include <b/type_traits/is_same.hpp>
#include <b/icl/type_traits/element_type_of.hpp> 
#include <b/icl/type_traits/segment_type_of.hpp> 
#include <b/icl/type_traits/size_type_of.hpp> 
#include <b/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif


