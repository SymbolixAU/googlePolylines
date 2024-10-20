//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_LEX_LEXER_SEQUENCE_HPP
#define BOOST_SPIRIT_LEX_LEXER_SEQUENCE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <b/spirit/home/lex/domain.hpp>
#include <b/spirit/home/lex/lexer_type.hpp>
#include <b/spirit/home/lex/meta_compiler.hpp>
#include <b/spirit/home/lex/detail/sequence_function.hpp>
#include <b/fusion/include/any.hpp>
#include <b/proto/operators.hpp>
#include <b/proto/tags.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<lex::domain, proto::tag::bitwise_or>  // enables |
      : mpl::true_ {};

    template <>
    struct flatten_tree<lex::domain, proto::tag::bitwise_or>  // flattens |
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace lex
{
    template <typename Elements>
    struct sequence : nary_lexer<sequence<Elements> >
    {
        sequence(Elements const& elements)
          : elements(elements) {}

        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state
          , String const& targetstate) const
        {
            typedef detail::sequence_collect_function<LexerDef, String>
                collect_function_type;
            collect_function_type f (lexdef, state, targetstate);
            fusion::any(elements, f);
        }

        template <typename LexerDef>
        void add_actions(LexerDef& lexdef) const 
        {
            detail::sequence_add_actions_function<LexerDef> f (lexdef);
            fusion::any(elements, f);
        }

        Elements elements;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Lexer generator: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::bitwise_or, Elements, Modifiers>
      : make_nary_composite<Elements, sequence>
    {};

}}} // namespace boost::spirit::lex

#endif
