//-----------------------------------------------------------------------------
// boost variant/recursive_variant.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003 Eric Friedman
// Copyright (c) 2013-2023 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VARIANT_RECURSIVE_VARIANT_HPP
#define BOOST_VARIANT_RECURSIVE_VARIANT_HPP

#include <b/variant/variant_fwd.hpp>
#include <b/variant/detail/enable_recursive.hpp>
#include <b/variant/detail/substitute_fwd.hpp>
#include <b/variant/detail/make_variant_list.hpp>
#include <b/variant/detail/over_sequence.hpp>

#include <b/mpl/aux_/lambda_arity_param.hpp>

#include <b/mpl/equal.hpp>
#include <b/mpl/eval_if.hpp>
#include <b/mpl/identity.hpp>
#include <b/mpl/if.hpp>
#include <b/mpl/protect.hpp>
#include <b/mpl/transform.hpp>
#include <b/type_traits/is_same.hpp>
#include <b/preprocessor/cat.hpp>
#include <b/preprocessor/repeat.hpp>

#include <b/mpl/bool.hpp>
#include <b/mpl/is_sequence.hpp>
#include <b/variant/variant.hpp>

namespace boost {

namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction specialization substitute
//
// Handles embedded variant types when substituting for recursive_variant_.
//

template <
      BOOST_VARIANT_ENUM_PARAMS(typename T)
    , typename RecursiveVariant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(typename Arity)
    >
struct substitute<
      ::boost::variant<
          recursive_flag< T0 >
        , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
        >
    , RecursiveVariant
    , ::boost::recursive_variant_
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(Arity)
    >
{
    typedef ::boost::variant<
          recursive_flag< T0 >
        , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
        > type;
};

template <
      BOOST_VARIANT_ENUM_PARAMS(typename T)
    , typename RecursiveVariant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(typename Arity)
    >
struct substitute<
      ::boost::variant<
          ::boost::detail::variant::over_sequence< T0 >
        , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
        >
    , RecursiveVariant
    , ::boost::recursive_variant_
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(Arity)
    >
{
private:

    typedef T0 initial_types;

    typedef typename mpl::transform<
          initial_types
        , mpl::protect< quoted_enable_recursive<RecursiveVariant,mpl::true_> >
        >::type types;

public:

    typedef typename mpl::if_<
          mpl::equal<initial_types, types, ::boost::is_same<mpl::_1, mpl::_2> >
        , ::boost::variant<
              ::boost::detail::variant::over_sequence< T0 >
            , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
            >
        , ::boost::variant< over_sequence<types> >
        >::type type;
};

template <
      BOOST_VARIANT_ENUM_PARAMS(typename T)
    , typename RecursiveVariant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(typename Arity)
    >
struct substitute<
      ::boost::variant< BOOST_VARIANT_ENUM_PARAMS(T) >
    , RecursiveVariant
    , ::boost::recursive_variant_
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(Arity)
    >
{   
    typedef ::boost::variant<
        typename enable_recursive<   
              T0              
            , RecursiveVariant               
            , mpl::true_                     
        >::type,
        typename enable_recursive<   
              TN              
            , RecursiveVariant               
            , mpl::true_                     
        >::type...  
    > type;
};

}} // namespace detail::variant

///////////////////////////////////////////////////////////////////////////////
// metafunction make_recursive_variant
//
// See docs and b/variant/variant_fwd.hpp for more information.
//
template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
struct make_recursive_variant
{
public: // metafunction result

    typedef boost::variant<
          detail::variant::recursive_flag< T0 >
        , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)
        > type;

};

///////////////////////////////////////////////////////////////////////////////
// metafunction make_recursive_variant_over
//
// See docs and b/variant/variant_fwd.hpp for more information.
//
template <typename Types>
struct make_recursive_variant_over
{
private: // precondition assertions

    BOOST_STATIC_ASSERT(( ::boost::mpl::is_sequence<Types>::value ));

public: // metafunction result

    typedef typename make_recursive_variant<
          detail::variant::over_sequence< Types >
        >::type type;

};

} // namespace boost

#endif // BOOST_VARIANT_RECURSIVE_VARIANT_HPP
