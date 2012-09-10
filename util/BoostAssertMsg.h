/** @file
	@brief Header

	@date 2012

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_BoostAssertMsg_h_GUID_2b5195d1_9921_401b_920c_7068ce573fd8
#define INCLUDED_BoostAssertMsg_h_GUID_2b5195d1_9921_401b_920c_7068ce573fd8

// Internal Includes
// - none

// Library/third-party includes
#include <boost/assert.hpp>

// Standard includes
// - none

#ifndef BOOST_ASSERT_MSG

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)

#define BOOST_ASSERT_MSG(expr, msg) ((void)0)

#elif defined(BOOST_ENABLE_ASSERT_HANDLER)

#include <boost/current_function.hpp>

namespace boost {
	void assertion_failed_msg(char const * expr, char const * msg,
	                          char const * function, char const * file, long line); // user defined
} // namespace boost

#define BOOST_ASSERT_MSG(expr, msg) ((expr) \
    ? ((void)0) \
    : ::boost::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else
#ifndef BOOST_ASSERT_HPP
#define BOOST_ASSERT_HPP
#include <cstdlib>
#include <iostream>
#include <boost/current_function.hpp>

//  IDE's like Visual Studio perform better if output goes to std::cout or
//  some other stream, so allow user to configure output stream:
#ifndef BOOST_ASSERT_MSG_OSTREAM
# define BOOST_ASSERT_MSG_OSTREAM std::cerr
#endif

namespace boost {
	namespace assertion {
		namespace detail {
			inline void assertion_failed_msg(char const * expr, char const * msg, char const * function,
			                                 char const * file, long line) {
				BOOST_ASSERT_MSG_OSTREAM
				        << "***** Internal Program Error - assertion (" << expr << ") failed in "
				        << function << ":\n"
				        << file << '(' << line << "): " << msg << std::endl;
				std::abort();
			}
		} // detail
	} // assertion
} // detail
#endif

#define BOOST_ASSERT_MSG(expr, msg) ((expr) \
    ? ((void)0) \
    : ::boost::assertion::detail::assertion_failed_msg(#expr, msg, \
          BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#endif

#endif

#endif // INCLUDED_BoostAssertMsg_h_GUID_2b5195d1_9921_401b_920c_7068ce573fd8
