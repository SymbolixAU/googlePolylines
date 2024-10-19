// Copyright Jim Bosch 2010-2012.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_numpy_hpp_
#define boost_python_numpy_hpp_

#include <b/python/numpy/dtype.hpp>
#include <b/python/numpy/ndarray.hpp>
#include <b/python/numpy/scalars.hpp>
#include <b/python/numpy/matrix.hpp>
#include <b/python/numpy/ufunc.hpp>
#include <b/python/numpy/invoke_matching.hpp>
#include <b/python/numpy/config.hpp>

namespace boost { namespace python { namespace numpy {

/**
 *  @brief Initialize the Numpy C-API
 *
 *  This must be called before using anything in boost.numpy;
 *  It should probably be the first line inside BOOST_PYTHON_MODULE.
 *
 *  @internal This just calls the Numpy C-API functions "import_array()"
 *            and "import_ufunc()", and then calls
 *            dtype::register_scalar_converters().
 */
BOOST_NUMPY_DECL void initialize(bool register_scalar_converters=true);

}}} // namespace boost::python::numpy

#endif
