// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef REGISTERED_POINTEE_DWA2002710_HPP
# define REGISTERED_POINTEE_DWA2002710_HPP
# include <b/python/converter/registered.hpp>
# include <b/python/converter/pointer_type_id.hpp>
# include <b/python/converter/registry.hpp>
# include <b/python/detail/type_traits.hpp>

namespace boost { namespace python { namespace converter { 

struct registration;

template <class T>
struct registered_pointee
    : registered<
        typename boost::python::detail::remove_pointer<
           typename boost::python::detail::remove_cv<
              typename boost::python::detail::remove_reference<T>::type
           >::type
        >::type
    >
{
};
}}} // namespace boost::python::converter

#endif // REGISTERED_POINTEE_DWA2002710_HPP
