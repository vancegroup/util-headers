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
// - none

// Library/third-party includes
#include <boost/call_traits.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/tuple/tuple.hpp>

// Standard includes
// - none

namespace util {

	struct DefaultValueToTemplatePolicy {
		template<typename T>
		struct Select {}; /* {
			template<typename return_type, typename Next, typename T>
			static inline return_type apply(typename boost::call_traits<T>::param_type input);
		};*/


	};
	template<>
	struct DefaultValueToTemplatePolicy::Select<bool> {
		template<typename return_type, template<class> class Next, typename T>
		static inline return_type apply(T const& input) {
			if (input.get<0>()) {
				return Next<typename boost::mpl::bool_<true> >::apply(input.get_tail());
			}
		}
	};
	namespace detail {
		/*
			template<typename T>
			struct ValueContainer;
			template<>
			struct ValueWrapper<bool> {
				template<bool>
				struct type : boost::mpl::bool_<Val> {}
			};

			*/
		template<typename Metafunc, typename SelectionPolicy, typename Params = boost::mpl::vector<> >
		struct ConvertHead {
			template<typename Val>
			struct Next : ConvertHead<Metafunc, SelectionPolicy, boost::mpl::push_back<Params, Val> > {};

			template<typename T>
			static inline typename Metafunc::return_type apply(T const& input) {
				return SelectionPolicy::template Select<typename T::head_type>::template apply<typename Metafunc::return_type, Next>(input);
			}

		};
		template<typename Metafunc, typename SelectionPolicy, typename Params>
		struct ConvertHead<null_type, Metafunc, SelectionPolicy, Params> {
			static inline typename Metafunc::return_type apply(boost::tuples::null_type const&) {
				return Metafunc::apply<Params>();
			}
		};
	} // end of namespace detail
/// @addtogroup GenericProgramming Generic Programming
/// @{
	/** @brief At run-time, given a tuple, calls an appropriate version
		of the given metafunction with a mpl sequence template parameter equal
		to the runtime values passed.

		@tparam Metafunc Metafunction class, must define a "return_type" typedef
		and an "apply" static function template
	*/
	template<typename Metafunc, typename Input, typename SelectionPolicy = DefaultValueToTemplatePolicy>
	inline typename Metafunc::return_type ValueToTemplate(Input const& input) {
		return detail::ConvertHead<Input, Metafunc, SelectionPolicy>::apply(input);
	}
/// @}

} // end of namespace util

#endif // INCLUDED_ValueToTemplate_h_GUID_aca63948_8bf1_45ed_ae9b_a1d817a97434
