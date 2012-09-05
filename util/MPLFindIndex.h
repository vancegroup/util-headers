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
#ifndef INCLUDED_MPLFindIndex_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00
#define INCLUDED_MPLFindIndex_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/contains.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>

// Standard includes
// - none

namespace util {
	namespace detail {
		/// @brief Utility template used by find_index
		template<typename Sequence, typename Target>
		struct find_index_impl {
			BOOST_MPL_ASSERT((boost::mpl::contains<Sequence, Target>));
			typedef typename boost::mpl::begin<Sequence>::type first;
			typedef typename boost::mpl::find<Sequence, Target>::type position;

			enum {
				value = (boost::mpl::distance<first, position>::value)
			};
		};
	} // end of namespace detail

	/// @brief Metafunction to find the index of a given type in an MPL sequence.
	/// Builds on boost::mpl::find and boost::mpl::distance
	template<typename Sequence, typename Target>
	struct find_index : boost::mpl::int_<detail::find_index_impl<Sequence, Target>::value>  {};
} // end of namespace util

#endif // INCLUDED_MPLFindIndex_h_GUID_85ff7967_6f99_4669_91c8_2b6c63e12e00
