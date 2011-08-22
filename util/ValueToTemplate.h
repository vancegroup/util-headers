/** @file
	@brief Header

	@date 2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_ValueToTemplate_h_GUID_aca63948_8bf1_45ed_ae9b_a1d817a97434
#define INCLUDED_ValueToTemplate_h_GUID_aca63948_8bf1_45ed_ae9b_a1d817a97434

// Internal Includes
#include "ValueToTemplatePolicy.h"

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/tuple/tuple.hpp>

// Standard includes
// - none

namespace util {

	namespace detail {
		/// Class template used to perform recursive conversion of values in a tuple
		/// to template parameters - delegates the actual conversion to SelectionPolicy
		template<typename T, typename Op, template<class> class SelectionPolicy, typename Params = boost::mpl::vector<> >
		struct ConvertHead {
			typedef typename T::head_type head_type;
			typedef typename T::tail_type tail_type;
			typedef typename Op::result_type result_type;

			template<typename Val>
			struct Next : ConvertHead<tail_type, Op, SelectionPolicy, typename boost::mpl::push_back<Params, Val>::type > {};

			static inline result_type apply(T const& input) {
				return SelectionPolicy<head_type>::template apply<result_type, Next>(input.get_head(), input.get_tail());
			}

		};

		/// Partial specialization for base case: have reached the end
		/// of the tuple
		template<typename Op, template<class> class SelectionPolicy, typename Params>
		struct ConvertHead<boost::tuples::null_type, Op, SelectionPolicy, Params> {
			typedef typename Op::result_type result_type;
			static inline result_type apply(boost::tuples::null_type const&) {
				return Op::template apply<Params>();
			}
		};

	} // end of namespace detail

	/// @addtogroup GenericProgramming Generic Programming
	/// @{
	/** @brief At run-time, given a tuple, calls an appropriate version
	of the given metafunction with a mpl sequence template parameter equal
	to the runtime values passed.

	@tparam Op Class defining a static function template called "apply"
	and a typedef called "result_type"
	*/
	template<typename Op, typename Input>
	inline typename Op::result_type ValueToTemplate(Input const& input) {
		return detail::ConvertHead<Input, Op, DefaultValueToTemplatePolicy>::apply(input);
	}
	/// @}

} // end of namespace util

#endif // INCLUDED_ValueToTemplate_h_GUID_aca63948_8bf1_45ed_ae9b_a1d817a97434
