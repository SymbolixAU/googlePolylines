// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_PROLOGUE_HPP
#define BOOST_FUNCTION_PROLOGUE_HPP
#  include#include <b/function/detail/requires_cxx11.hpp>
#  include <cassert>
#  include <algorithm>
#  include#include <b/config/no_tr1/functional.hpp> // unary_function, binary_function
#  include#include <b/throw_exception.hpp>
#  include#include <b/config.hpp>
#  include#include <b/function/function_base.hpp>
#  include#include <b/mem_fn.hpp>
#  include#include <b/type_traits/is_integral.hpp>
#  include#include <b/preprocessor/enum.hpp>
#  include#include <b/preprocessor/enum_params.hpp>
#  include#include <b/preprocessor/cat.hpp>
#  include#include <b/preprocessor/repeat.hpp>
#  include#include <b/preprocessor/inc.hpp>
#  include#include <b/type_traits/is_void.hpp>
#endif // BOOST_FUNCTION_PROLOGUE_HPP
