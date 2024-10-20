//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_SRC_HPP
#define BOOST_JSON_SRC_HPP

/*

This file is meant to be included once,
in a translation unit of the program.

*/

#ifndef BOOST_JSON_SOURCE
#define BOOST_JSON_SOURCE
#endif

// We include this in case someone is using
// src.hpp as their main JSON header file
// https://github.com/boostorg/json/issues/223#issuecomment-689264149
#include <b/json.hpp>

#include <b/json/detail/config.hpp>

#include <b/json/impl/array.ipp>
#include <b/json/impl/error.ipp>
#include <b/json/impl/kind.ipp>
#include <b/json/impl/monotonic_resource.ipp>
#include <b/json/impl/null_resource.ipp>
#include <b/json/impl/object.ipp>
#include <b/json/impl/parse.ipp>
#include <b/json/impl/parser.ipp>
#include <b/json/impl/pointer.ipp>
#include <b/json/impl/serialize.ipp>
#include <b/json/impl/serializer.ipp>
#include <b/json/impl/static_resource.ipp>
#include <b/json/impl/stream_parser.ipp>
#include <b/json/impl/string.ipp>
#include <b/json/impl/value.ipp>
#include <b/json/impl/value_stack.ipp>
#include <b/json/impl/value_ref.ipp>

#include <b/json/detail/impl/shared_resource.ipp>
#include <b/json/detail/impl/default_resource.ipp>
#include <b/json/detail/impl/except.ipp>
#include <b/json/detail/impl/format.ipp>
#include <b/json/detail/impl/handler.ipp>
#include <b/json/detail/impl/stack.ipp>
#include <b/json/detail/impl/string_impl.ipp>

#include <b/json/detail/ryu/impl/d2s.ipp>
#include <b/json/detail/charconv/impl/from_chars.ipp>

#endif
