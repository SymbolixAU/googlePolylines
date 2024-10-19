//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_HPP
#define BOOST_COMPUTE_HPP

#include <b/compute/algorithm.hpp>
#include <b/compute/allocator.hpp>
#include <b/compute/async.hpp>
#include <b/compute/buffer.hpp>
#include <b/compute/cl.hpp>
#include <b/compute/command_queue.hpp>
#include <b/compute/config.hpp>
#include <b/compute/container.hpp>
#include <b/compute/context.hpp>
#include <b/compute/device.hpp>
#include <b/compute/functional.hpp>
#include <b/compute/image.hpp>
#include <b/compute/iterator.hpp>
#include <b/compute/kernel.hpp>
#include <b/compute/lambda.hpp>
#include <b/compute/pipe.hpp>
#include <b/compute/platform.hpp>
#include <b/compute/program.hpp>
#include <b/compute/random.hpp>
#include <b/compute/svm.hpp>
#include <b/compute/system.hpp>
#include <b/compute/types.hpp>
#include <b/compute/user_event.hpp>
#include <b/compute/utility.hpp>
#include <b/compute/version.hpp>

#ifdef BOOST_COMPUTE_HAVE_HDR_CL_EXT
#include <b/compute/cl_ext.hpp>
#endif

#endif // BOOST_COMPUTE_HPP
