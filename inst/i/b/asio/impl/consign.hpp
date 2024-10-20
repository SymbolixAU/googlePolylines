//
// impl/consign.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_CONSIGN_HPP
#define BOOST_ASIO_IMPL_CONSIGN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <b/asio/detail/config.hpp>
#include <b/asio/associator.hpp>
#include <b/asio/async_result.hpp>
#include <b/asio/detail/handler_cont_helpers.hpp>
#include <b/asio/detail/type_traits.hpp>
#include <b/asio/detail/utility.hpp>

#include <b/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Class to adapt a consign_t as a completion handler.
template <typename Handler, typename... Values>
class consign_handler
{
public:
  typedef void result_type;

  template <typename H>
  consign_handler(H&& handler, std::tuple<Values...> values)
    : handler_(static_cast<H&&>(handler)),
      values_(static_cast<std::tuple<Values...>&&>(values))
  {
  }

  template <typename... Args>
  void operator()(Args&&... args)
  {
    static_cast<Handler&&>(handler_)(static_cast<Args&&>(args)...);
  }

//private:
  Handler handler_;
  std::tuple<Values...> values_;
};

template <typename Handler>
inline bool asio_handler_is_continuation(
    consign_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Values, typename... Signatures>
struct async_result<consign_t<CompletionToken, Values...>, Signatures...>
  : async_result<CompletionToken, Signatures...>
{
  template <typename Initiation>
  struct init_wrapper
  {
    init_wrapper(Initiation init)
      : initiation_(static_cast<Initiation&&>(init))
    {
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler,
        std::tuple<Values...> values, Args&&... args)
    {
      static_cast<Initiation&&>(initiation_)(
          detail::consign_handler<decay_t<Handler>, Values...>(
            static_cast<Handler&&>(handler),
            static_cast<std::tuple<Values...>&&>(values)),
          static_cast<Args&&>(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<CompletionToken, Signatures...>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, static_cast<std::tuple<Values...>&&>(token.values_),
        static_cast<Args&&>(args)...))
  {
    return async_initiate<CompletionToken, Signatures...>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, static_cast<std::tuple<Values...>&&>(token.values_),
        static_cast<Args&&>(args)...);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename... Values, typename DefaultCandidate>
struct associator<Associator,
    detail::consign_handler<Handler, Values...>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::consign_handler<Handler, Values...>& h) noexcept
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_);
  }

  static auto get(const detail::consign_handler<Handler, Values...>& h,
      const DefaultCandidate& c) noexcept
    -> decltype(Associator<Handler, DefaultCandidate>::get(h.handler_, c))
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <b/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CONSIGN_HPP
