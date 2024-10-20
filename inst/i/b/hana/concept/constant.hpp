/*!
@file
Defines `boost::hana::Constant`.

Copyright Louis Dionne 2013-2022
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_CONSTANT_HPP

#include <b/hana/fwd/concept/constant.hpp>

#include <b/hana/config.hpp>
#include <b/hana/core/default.hpp>
#include <b/hana/core/tag_of.hpp>
#include <b/hana/detail/integral_constant.hpp>
#include <b/hana/value.hpp>


namespace boost { namespace hana {
    template <typename C>
    struct Constant
        : hana::integral_constant<bool,
            !is_default<value_impl<typename tag_of<C>::type>>::value
        >
    { };
}} // end namespace boost::hana

#endif // !BOOST_HANA_CONCEPT_CONSTANT_HPP
