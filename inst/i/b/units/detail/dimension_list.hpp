// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_DIMENSION_LIST_HPP
#define BOOST_UNITS_DIMENSION_LIST_HPP

#include <b/mpl/next.hpp>
#include <b/mpl/deref.hpp>
#include <b/mpl/push_front_fwd.hpp>
#include <b/mpl/pop_front_fwd.hpp>
#include <b/mpl/size_fwd.hpp>
#include <b/mpl/begin_end_fwd.hpp>
#include <b/mpl/front_fwd.hpp>

#include <b/units/config.hpp>

namespace boost {

namespace units {

struct dimensionless_type;

namespace detail {

struct dimension_list_tag { };

} // namespace detail

template<class Item, class Next>
struct list
{
    typedef detail::dimension_list_tag  tag;
    typedef list              type;
    typedef Item                        item;
    typedef Next                        next;
    typedef typename mpl::next<typename Next::size>::type size;
};

} // namespace units

namespace mpl {

// INTERNAL ONLY
template<>
struct size_impl<units::detail::dimension_list_tag>
{
    template<class L> struct apply : public L::size { };
};

// INTERNAL ONLY
template<>
struct begin_impl<units::detail::dimension_list_tag>
{
    template<class L>
    struct apply 
    {
        typedef L type;
    };
};

// INTERNAL ONLY
template<>
struct end_impl<units::detail::dimension_list_tag>
{
    template<class L>
    struct apply 
    {
        typedef units::dimensionless_type type;
    };
};

// INTERNAL ONLY
template<>
struct push_front_impl<units::detail::dimension_list_tag>
{
    template<class L, class T>
    struct apply 
    {
        typedef units::list<T, L> type;
    };
};

// INTERNAL ONLY
template<>
struct pop_front_impl<units::detail::dimension_list_tag>
{
    template<class L>
    struct apply 
    {
        typedef typename L::next type;
    };
};

// INTERNAL ONLY
template<>
struct front_impl<units::detail::dimension_list_tag>
{
    template<class L>
    struct apply 
    {
        typedef typename L::item type;
    };
};

// INTERNAL ONLY
template<class Item, class Next>
struct deref<units::list<Item, Next> >
{
    typedef Item type;
};

} // namespace mpl

} // namespace boost

#if BOOST_UNITS_HAS_BOOST_TYPEOF

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::units::list, 2)

#endif

#include <b/units/dimensionless_type.hpp>

#endif // BOOST_UNITS_DIMENSION_LIST_HPP
