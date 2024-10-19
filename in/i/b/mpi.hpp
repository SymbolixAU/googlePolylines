// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface

//  See www.boost.org/libs/mpi for documentation.

/** @file mpi.hpp
 *
 *  This file is a top-level convenience header that includes all of
 *  the Boost.MPI library headers. Users concerned about compile time
 *  may wish to include only specific headers from the Boost.MPI
 *  library.
 *
 */
#ifndef BOOST_MPI_HPP
#define BOOST_MPI_HPP

#include <b/mpi/allocator.hpp>
#include <b/mpi/collectives.hpp>
#include <b/mpi/communicator.hpp>
#include <b/mpi/datatype.hpp>
#include <b/mpi/environment.hpp>
#include <b/mpi/graph_communicator.hpp>
#include <b/mpi/group.hpp>
#include <b/mpi/intercommunicator.hpp>
#include <b/mpi/nonblocking.hpp>
#include <b/mpi/operations.hpp>
#include <b/mpi/skeleton_and_content.hpp>
#include <b/mpi/timer.hpp>

#endif // BOOST_MPI_HPP
