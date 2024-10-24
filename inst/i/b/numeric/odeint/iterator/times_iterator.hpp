
/*
 [auto_generated]
 b/numeric/odeint/iterator/times_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with oscillator calls at times from a given sequence.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED


#include <b/numeric/odeint/util/stepper_traits.hpp>
#include <b/numeric/odeint/stepper/stepper_categories.hpp>
#include <b/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <b/numeric/odeint/iterator/impl/times_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the times_iterator_impl with the right tags */
    template< class Stepper , class System , class State , class TimeIterator
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class times_iterator : public times_iterator_impl<
            times_iterator< Stepper , System , State , TimeIterator , StepperTag > ,
            Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef times_iterator< Stepper , System , State , TimeIterator , StepperTag > iterator_type;

    public:
        times_iterator( Stepper stepper , System sys , State &s ,
                        TimeIterator t_start , TimeIterator t_end , time_type dt )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator, detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        times_iterator( Stepper stepper , System sys , State &s )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State , class TimeIterator >
    times_iterator< Stepper , System, State , TimeIterator > make_times_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt );
    }

    // ToDo: requires to specifically provide the TimeIterator template parameter, can this be improved?
    template< class TimeIterator , class Stepper , class System , class State >
    times_iterator< Stepper , System , State , TimeIterator > make_times_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
        //TimeIterator t_end )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x );
    }

    template< class Stepper , class System , class State , class TimeIterator >
    std::pair< times_iterator< Stepper , System , State , TimeIterator > ,
               times_iterator< Stepper , System , State , TimeIterator > >
    make_times_range(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt ) ,
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x )
            );
    }


    /**
     * \class times_iterator
     *
     * \brief ODE Iterator with given evaluation points. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from *t_start
     * to *t_end evaluated at time points given by the sequence t_start to t_end.
     * t_start and t_end are iterators representing a sequence of time points
     * where the solution of the ODE should be evaluated.
     * After each iteration the iterator dereferences to the state x at the next
     * time *t_start++ until t_end is reached.
     * This iterator can be used with Steppers, ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_times routine.
     *
     * times_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     * \tparam TimeIterator The iterator type for the sequence of time points.
     */



    /**
     * \fn make_times_iterator_begin( Stepper stepper ,
        System system ,
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for times_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator.
     */


    /**
     * \fn make_times_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for times_iterator. Constructs an end iterator.
     *
     * \tparam TimesIterator The iterator type of the time sequence, must be specifically provided.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The times iterator.
     *
     * This function needs the TimeIterator type specifically defined as a
     * template parameter.
     */


    /**
     * \fn make_times_range( Stepper stepper , System system , State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of times iterators. A range is here a pair
     * of times_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED
