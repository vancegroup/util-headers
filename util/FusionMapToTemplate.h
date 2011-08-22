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
#ifndef INCLUDED_FusionMapToTemplate_h_GUID_700bbf73_dd60_462f_9127_edb6b505b3a2
#define INCLUDED_FusionMapToTemplate_h_GUID_700bbf73_dd60_462f_9127_edb6b505b3a2

// Internal Includes
#include "ValueToTemplatePolicy.h"

// Library/third-party includes
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>

// Standard includes
// - none

namespace util {

	namespace detail {
		/// Class template used to perform recursive conversion of values in a fusion::map
		/// to template parameters - delegates the actual conversion to SelectionPolicy
		template<typename Iter, typename EndIter, typename Op, template<class> class SelectionPolicy, typename Params = boost::mpl::map<> >
		struct ConvertElement {
			typedef typename boost::fusion::result_of::first <
			typename boost::fusion::result_of::value_of<Iter>::type
			>::type KeyType;

			typedef typename boost::fusion::result_of::second <
			typename boost::fusion::result_of::value_of<Iter>::type
			>::type ValueType;
			typedef typename Op::result_type result_type;
			typedef typename boost::fusion::result_of::next<Iter>::type NextIter;

			template<typename Val>
			struct Next {
				typedef typename boost::mpl::insert<Params, boost::mpl::pair<KeyType, Val> >::type NewParams;
				static inline result_type apply(boost::fusion::vector<NextIter, EndIter> arg) {
					return ConvertElement<NextIter, EndIter, Op, SelectionPolicy, NewParams>::apply(boost::fusion::at_c<0>(arg), boost::fusion::at_c<1>(arg));
				}
			};

			static inline result_type apply(Iter input, EndIter end) {
				return SelectionPolicy<ValueType>::template apply<result_type, Next>(deref(input).second, boost::fusion::vector<NextIter, EndIter>(boost::fusion::next(input), end));
			}

		};

		/// Partial specialization for base case: have reached the end
		/// of the map
		template<typename EndIter, typename Op, template<class> class SelectionPolicy, typename Params>
		struct ConvertElement<EndIter, EndIter, Op, SelectionPolicy, Params> {
			typedef typename Op::result_type result_type;
			static inline result_type apply(EndIter, EndIter) {
				return Op::template apply<Params>();
			}
		};

	} // end of namespace detail

	/// @addtogroup GenericProgramming Generic Programming
	/// @{
	/** @brief At run-time, given a boost::fusion::Map, calls an appropriate version
	of the given metafunction with a mpl map template parameter equal
	to the runtime values passed.

	@sa ValueToTemplate

	@tparam Op Class defining a static function template called "apply"
	and a typedef called "result_type"
	*/
	template<typename Op, typename Input>
	inline typename Op::result_type FusionMapToTemplate(Input const& input) {
		typedef typename boost::fusion::result_of::begin<Input const>::type Iter;
		typedef typename boost::fusion::result_of::end<Input const>::type EndIter;
		return detail::ConvertElement<Iter, EndIter, Op, DefaultValueToTemplatePolicy>::apply(boost::fusion::begin(input), boost::fusion::end(input));
	}
	/// @}

} // end of namespace util

#endif // INCLUDED_FusionMapToTemplate_h_GUID_700bbf73_dd60_462f_9127_edb6b505b3a2
