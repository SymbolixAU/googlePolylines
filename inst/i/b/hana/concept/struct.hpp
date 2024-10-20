/*!
@file
Defines `boost::hana::Struct`.

Copyright Louis Dionne 2013-2022
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <b/hana/fwd/concept/struct.hpp>

#include <b/hana/accessors.hpp>
#include <b/hana/config.hpp>
#include <b/hana/core/default.hpp>
#include <b/hana/core/tag_of.hpp>
#include <b/hana/detail/integral_constant.hpp>


namespace boost { namespace hana {
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
}} // end namespace boost::hana

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP
