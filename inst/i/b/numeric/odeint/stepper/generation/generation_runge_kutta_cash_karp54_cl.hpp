/*
 [auto_generated]
 b/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54_classic.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the
 Runge-Kutta-Cash-Karp 54 method with the classical implementation.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

#include <b/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <b/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp>
#include <b/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// Specializations for runge_kutta_cash_karp54
template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
