// Copyright David Abrahams 2002.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_converter_shared_ptr_from_python_hpp_
#define boost_python_converter_shared_ptr_from_python_hpp_

#include <b/python/handle.hpp>
#include <b/python/converter/shared_ptr_deleter.hpp>
#include <b/python/converter/from_python.hpp>
#include <b/python/converter/rvalue_from_python_data.hpp>
#include <b/python/converter/registered.hpp>
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
# include <b/python/converter/pytype_function.hpp>
#endif
#include <b/shared_ptr.hpp>
#include <memory>

namespace boost { namespace python { namespace converter { 

template <class T, template <typename> class SP>
struct shared_ptr_from_python
{
  shared_ptr_from_python()
  {
    converter::registry::insert(&convertible, &construct, type_id<SP<T> >()
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
				, &converter::expected_from_python_type_direct<T>::get_pytype
#endif
				);
  }

 private:
  static void* convertible(PyObject* p)
  {
    if (p == Py_None)
      return p;
        
    return converter::get_lvalue_from_python(p, registered<T>::converters);
  }
    
  static void construct(PyObject* source, rvalue_from_python_stage1_data* data)
  {
    void* const storage = ((converter::rvalue_from_python_storage<SP<T> >*)data)->storage.bytes;
    // Deal with the "None" case.
    if (data->convertible == source)
      new (storage) SP<T>();
    else
    {
      void *const storage = ((converter::rvalue_from_python_storage<SP<T> >*)data)->storage.bytes;
      // Deal with the "None" case.
      if (data->convertible == source)
        new (storage) SP<T>();
      else
      {
        SP<void> hold_convertible_ref_count((void*)0, shared_ptr_deleter(handle<>(borrowed(source))) );
        // use aliasing constructor
        new (storage) SP<T>(hold_convertible_ref_count, static_cast<T*>(data->convertible));
      }
    }
    data->convertible = storage;
  }
};

}}} // namespace boost::python::converter

#endif
