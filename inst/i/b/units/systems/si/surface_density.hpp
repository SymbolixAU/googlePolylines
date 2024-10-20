// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_SI_SURFACE_DENSITY_HPP
#define BOOST_UNITS_SI_SURFACE_DENSITY_HPP

#include <b/units/systems/si/base.hpp>
#include <b/units/physical_dimensions/surface_density.hpp>

namespace boost {

namespace units { 

namespace si {

typedef unit<surface_density_dimension,si::system>  surface_density;

BOOST_UNITS_STATIC_CONSTANT(kilogram_per_square_meter,surface_density);
BOOST_UNITS_STATIC_CONSTANT(kilograms_per_square_meter,surface_density);
BOOST_UNITS_STATIC_CONSTANT(kilogramme_per_square_metre,surface_density);
BOOST_UNITS_STATIC_CONSTANT(kilogrammes_per_square_metre,surface_density);

} // namespace si

} // namespace units

} // namespace boost

#endif // BOOST_UNITS_SI_SURFACE_DENSITY_HPP
