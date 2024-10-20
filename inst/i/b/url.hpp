//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_HPP
#define BOOST_URL_HPP

#include <b/url/grammar.hpp>

#include <b/url/authority_view.hpp>
#include <b/url/decode_view.hpp>
#include <b/url/encode.hpp>
#include <b/url/encoding_opts.hpp>
#include <b/url/error.hpp>
#include <b/url/error_types.hpp>
#include <b/url/format.hpp>
#include <b/url/host_type.hpp>
#include <b/url/ignore_case.hpp>
#include <b/url/ipv4_address.hpp>
#include <b/url/ipv6_address.hpp>
#include <b/url/optional.hpp>
#include <b/url/param.hpp>
#include <b/url/params_base.hpp>
#include <b/url/params_encoded_base.hpp>
#include <b/url/params_encoded_ref.hpp>
#include <b/url/params_encoded_view.hpp>
#include <b/url/params_ref.hpp>
#include <b/url/params_view.hpp>
#include <b/url/parse.hpp>
#include <b/url/parse_path.hpp>
#include <b/url/parse_query.hpp>
#include <b/url/pct_string_view.hpp>
#include <b/url/scheme.hpp>
#include <b/url/segments_base.hpp>
#include <b/url/segments_encoded_base.hpp>
#include <b/url/segments_encoded_ref.hpp>
#include <b/url/segments_encoded_view.hpp>
#include <b/url/segments_ref.hpp>
#include <b/url/segments_view.hpp>
#include <b/url/static_url.hpp>
#include <b/core/detail/string_view.hpp>
#include <b/url/url.hpp>
#include <b/url/url_base.hpp>
#include <b/url/url_view.hpp>
#include <b/url/url_view_base.hpp>
#include <b/url/urls.hpp>
#include <b/url/variant.hpp>

#include <b/url/rfc/absolute_uri_rule.hpp>
#include <b/url/rfc/authority_rule.hpp>
#include <b/url/rfc/gen_delim_chars.hpp>
#include <b/url/rfc/ipv4_address_rule.hpp>
#include <b/url/rfc/ipv6_address_rule.hpp>
#include <b/url/rfc/origin_form_rule.hpp>
#include <b/url/rfc/pchars.hpp>
#include <b/url/rfc/pct_encoded_rule.hpp>
#include <b/url/rfc/query_rule.hpp>
#include <b/url/rfc/relative_ref_rule.hpp>
#include <b/url/rfc/reserved_chars.hpp>
#include <b/url/rfc/sub_delim_chars.hpp>
#include <b/url/rfc/unreserved_chars.hpp>
#include <b/url/rfc/uri_rule.hpp>
#include <b/url/rfc/uri_reference_rule.hpp>

#endif
