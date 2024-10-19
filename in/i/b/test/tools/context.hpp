//  (C) Copyright Gennadiy Rozental 2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision: 74248 $
//
//  Description : test tools context interfaces
// ***************************************************************************

#ifndef BOOST_TEST_TOOLS_CONTEXT_HPP_111712GER
#define BOOST_TEST_TOOLS_CONTEXT_HPP_111712GER

// Boost.Test
#include <b/test/utils/lazy_ostream.hpp>
#include <b/test/detail/pp_variadic.hpp>

#include <b/preprocessor/repetition/enum_params.hpp>
#include <b/preprocessor/repetition/enum_binary_params.hpp>
#include <b/preprocessor/repetition/repeat_from_to.hpp>

#include <b/preprocessor/variadic/to_seq.hpp>
#include <b/preprocessor/variadic/size.hpp>
#include <b/preprocessor/cat.hpp>
#include <b/preprocessor/seq/for_each_i.hpp>
#include <b/preprocessor/seq/for_each.hpp>
#include <b/preprocessor/seq/enum.hpp>
#include <b/preprocessor/control/iif.hpp>
#include <b/preprocessor/comparison/equal.hpp>

#include <b/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace boost {
namespace test_tools {
namespace tt_detail {

// ************************************************************************** //
// **************                 context_frame                ************** //
// ************************************************************************** //

struct BOOST_TEST_DECL context_frame {
    explicit    context_frame( ::boost::unit_test::lazy_ostream const& context_descr );
    ~context_frame();

    operator    bool();

private:
    // Data members
    int         m_frame_id;
};

//____________________________________________________________________________//

#define BOOST_TEST_INFO( context_descr )                                                        \
    ::boost::unit_test::framework::add_context( BOOST_TEST_LAZY_MSG( context_descr ) , false )  \
/**/

#define BOOST_TEST_INFO_SCOPE( context_descr )                                                 \
    ::boost::test_tools::tt_detail::context_frame BOOST_JOIN( context_frame_, __LINE__ ) =      \
       ::boost::test_tools::tt_detail::context_frame(BOOST_TEST_LAZY_MSG( context_descr ) )     \
/**/

//____________________________________________________________________________//


#define BOOST_CONTEXT_PARAM(r, ctx, i, context_descr)  \
  if( ::boost::test_tools::tt_detail::context_frame BOOST_PP_CAT(ctx, i) =                       \
        ::boost::test_tools::tt_detail::context_frame(BOOST_TEST_LAZY_MSG( context_descr ) ) )   \
/**/

#define BOOST_CONTEXT_PARAMS( params )                                                           \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONTEXT_PARAM,                                             \
                                BOOST_JOIN( context_frame_, __LINE__ ),                          \
                                params)                                                          \
/**/

#define BOOST_TEST_CONTEXT( ... )                                                                \
    BOOST_CONTEXT_PARAMS(  BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) )                               \
/**/


//____________________________________________________________________________//

} // namespace tt_detail
} // namespace test_tools
} // namespace boost

#include <b/test/detail/enable_warnings.hpp>

#endif // BOOST_TEST_TOOLS_CONTEXT_HPP_111712GER
