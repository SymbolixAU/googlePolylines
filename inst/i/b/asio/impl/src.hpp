//
// impl/src.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SRC_HPP
#define BOOST_ASIO_IMPL_SRC_HPP

#define BOOST_ASIO_SOURCE

#include <b/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# error Do not compile Asio library source with BOOST_ASIO_HEADER_ONLY defined
#endif

#include <b/asio/impl/any_completion_executor.ipp>
#include <b/asio/impl/any_io_executor.ipp>
#include <b/asio/impl/cancellation_signal.ipp>
#include <b/asio/impl/connect_pipe.ipp>
#include <b/asio/impl/error.ipp>
#include <b/asio/impl/execution_context.ipp>
#include <b/asio/impl/executor.ipp>
#include <b/asio/impl/io_context.ipp>
#include <b/asio/impl/multiple_exceptions.ipp>
#include <b/asio/impl/serial_port_base.ipp>
#include <b/asio/impl/system_context.ipp>
#include <b/asio/impl/thread_pool.ipp>
#include <b/asio/detail/impl/buffer_sequence_adapter.ipp>
#include <b/asio/detail/impl/descriptor_ops.ipp>
#include <b/asio/detail/impl/dev_poll_reactor.ipp>
#include <b/asio/detail/impl/epoll_reactor.ipp>
#include <b/asio/detail/impl/eventfd_select_interrupter.ipp>
#include <b/asio/detail/impl/handler_tracking.ipp>
#include <b/asio/detail/impl/io_uring_descriptor_service.ipp>
#include <b/asio/detail/impl/io_uring_file_service.ipp>
#include <b/asio/detail/impl/io_uring_socket_service_base.ipp>
#include <b/asio/detail/impl/io_uring_service.ipp>
#include <b/asio/detail/impl/kqueue_reactor.ipp>
#include <b/asio/detail/impl/null_event.ipp>
#include <b/asio/detail/impl/pipe_select_interrupter.ipp>
#include <b/asio/detail/impl/posix_event.ipp>
#include <b/asio/detail/impl/posix_mutex.ipp>
#include <b/asio/detail/impl/posix_serial_port_service.ipp>
#include <b/asio/detail/impl/posix_thread.ipp>
#include <b/asio/detail/impl/posix_tss_ptr.ipp>
#include <b/asio/detail/impl/reactive_descriptor_service.ipp>
#include <b/asio/detail/impl/reactive_socket_service_base.ipp>
#include <b/asio/detail/impl/resolver_service_base.ipp>
#include <b/asio/detail/impl/scheduler.ipp>
#include <b/asio/detail/impl/select_reactor.ipp>
#include <b/asio/detail/impl/service_registry.ipp>
#include <b/asio/detail/impl/signal_set_service.ipp>
#include <b/asio/detail/impl/socket_ops.ipp>
#include <b/asio/detail/impl/socket_select_interrupter.ipp>
#include <b/asio/detail/impl/strand_executor_service.ipp>
#include <b/asio/detail/impl/strand_service.ipp>
#include <b/asio/detail/impl/thread_context.ipp>
#include <b/asio/detail/impl/throw_error.ipp>
#include <b/asio/detail/impl/timer_queue_ptime.ipp>
#include <b/asio/detail/impl/timer_queue_set.ipp>
#include <b/asio/detail/impl/win_iocp_file_service.ipp>
#include <b/asio/detail/impl/win_iocp_handle_service.ipp>
#include <b/asio/detail/impl/win_iocp_io_context.ipp>
#include <b/asio/detail/impl/win_iocp_serial_port_service.ipp>
#include <b/asio/detail/impl/win_iocp_socket_service_base.ipp>
#include <b/asio/detail/impl/win_event.ipp>
#include <b/asio/detail/impl/win_mutex.ipp>
#include <b/asio/detail/impl/win_object_handle_service.ipp>
#include <b/asio/detail/impl/win_static_mutex.ipp>
#include <b/asio/detail/impl/win_thread.ipp>
#include <b/asio/detail/impl/win_tss_ptr.ipp>
#include <b/asio/detail/impl/winrt_ssocket_service_base.ipp>
#include <b/asio/detail/impl/winrt_timer_scheduler.ipp>
#include <b/asio/detail/impl/winsock_init.ipp>
#include <b/asio/execution/impl/bad_executor.ipp>
#include <b/asio/experimental/impl/channel_error.ipp>
#include <b/asio/generic/detail/impl/endpoint.ipp>
#include <b/asio/ip/impl/address.ipp>
#include <b/asio/ip/impl/address_v4.ipp>
#include <b/asio/ip/impl/address_v6.ipp>
#include <b/asio/ip/impl/host_name.ipp>
#include <b/asio/ip/impl/network_v4.ipp>
#include <b/asio/ip/impl/network_v6.ipp>
#include <b/asio/ip/detail/impl/endpoint.ipp>
#include <b/asio/local/detail/impl/endpoint.ipp>

#endif // BOOST_ASIO_IMPL_SRC_HPP
