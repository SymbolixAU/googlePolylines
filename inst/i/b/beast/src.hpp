//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_SRC_HPP
#define BOOST_BEAST_SRC_HPP

/*

This file is meant to be included once, in a translation unit of
the program, with the macro BOOST_BEAST_SEPARATE_COMPILATION defined.

*/

#define BOOST_BEAST_SOURCE

#include <b/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_HEADER_ONLY)
# error Do not compile Beast library source with BOOST_BEAST_HEADER_ONLY defined
#endif

#include <b/beast/_experimental/test/impl/error.ipp>
#include <b/beast/_experimental/test/impl/fail_count.ipp>
#include <b/beast/_experimental/test/impl/stream.ipp>
#include <b/beast/_experimental/test/detail/stream_state.ipp>

#include <b/beast/core/detail/base64.ipp>
#include <b/beast/core/detail/sha1.ipp>
#include <b/beast/core/detail/impl/temporary_buffer.ipp>
#include <b/beast/core/impl/error.ipp>
#include <b/beast/core/impl/file_posix.ipp>
#include <b/beast/core/impl/file_stdio.ipp>
#include <b/beast/core/impl/file_win32.ipp>
#include <b/beast/core/impl/flat_static_buffer.ipp>
#include <b/beast/core/impl/saved_handler.ipp>
#include <b/beast/core/impl/static_buffer.ipp>
#include <b/beast/core/impl/string.ipp>

#include <b/beast/http/detail/basic_parser.ipp>
#include <b/beast/http/detail/rfc7230.ipp>
#include <b/beast/http/impl/basic_parser.ipp>
#include <b/beast/http/impl/error.ipp>
#include <b/beast/http/impl/field.ipp>
#include <b/beast/http/impl/fields.ipp>
#include <b/beast/http/impl/rfc7230.ipp>
#include <b/beast/http/impl/status.ipp>
#include <b/beast/http/impl/verb.ipp>

#include <b/beast/websocket/detail/hybi13.ipp>
#include <b/beast/websocket/detail/mask.ipp>
#include <b/beast/websocket/detail/pmd_extension.ipp>
#include <b/beast/websocket/detail/prng.ipp>
#include <b/beast/websocket/detail/service.ipp>
#include <b/beast/websocket/detail/utf8_checker.ipp>
#include <b/beast/websocket/impl/error.ipp>

#include <b/beast/zlib/detail/deflate_stream.ipp>
#include <b/beast/zlib/detail/inflate_stream.ipp>
#include <b/beast/zlib/impl/error.ipp>

#endif
