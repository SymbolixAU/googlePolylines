/*=============================================================================
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_V2_EVAL_HPP
#define BOOST_PHOENIX_CORE_V2_EVAL_HPP

#include <b/phoenix/core/limits.hpp>
#include <b/phoenix/core/environment.hpp>
#include <b/phoenix/core/is_actor.hpp>
#include <b/phoenix/core/meta_grammar.hpp>
#include <b/phoenix/core/terminal_fwd.hpp>
#include <b/phoenix/support/vector.hpp>
#include <b/proto/transform/fold.hpp>
#include <b/proto/transform/lazy.hpp>

namespace boost { namespace phoenix
{
    struct v2_eval
        : proto::callable
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval const &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename Eval, typename Env>
        typename result<v2_eval(Eval const&, Env)>::type
        operator()(Eval const & e, Env const & env) const
        {
            return e.eval(env);
        }
    };
}}

#endif
