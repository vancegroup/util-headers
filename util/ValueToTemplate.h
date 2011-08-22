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
#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>

// Standard includes
#include <sstream>
#include <stdexcept>

namespace util {

	namespace detail {
		/// Class template used to perform recursive conversion of values in a tuple
		/// to template parameters - delegates the actual conversion to SelectionPolicy
		template<typename T, typename Metafunc, typename SelectionPolicy, typename Params = boost::mpl::vector<> >
		struct ConvertHead {
			typedef typename T::head_type head_type;
			typedef typename T::tail_type tail_type;
			typedef typename Metafunc::return_type return_type;

			template<typename Val>
			struct Next : ConvertHead<tail_type, Metafunc, SelectionPolicy, typename boost::mpl::push_back<Params, Val>::type > {};

			static inline return_type apply(T const& input) {
				return SelectionPolicy::template Select<head_type>::template apply<return_type, Next>(input.get_head(), input.get_tail());
			}

		};

		/// Partial specialization for base case: have reached the end
		/// of the tuple
		template<typename Metafunc, typename SelectionPolicy, typename Params>
		struct ConvertHead<boost::tuples::null_type, Metafunc, SelectionPolicy, Params> {
			typedef typename Metafunc::return_type return_type;
			static inline return_type apply(boost::tuples::null_type const&) {
				return Metafunc::template apply<Params>();
			}
		};

		template<template<class> class Call, typename return_type, int Max, int Iter = 0>
		struct call_type_from_int_impl {
			template<typename FwdType>
			static inline return_type apply(int val, FwdType const & d) {
				if (val == Iter) {
					return Call<boost::mpl::int_<Iter> >::apply(d);
				}
				return call_type_from_int_impl < Call, return_type, Max, Iter + 1 >::apply(val, d);
			}
		};

		/// specialization for base case
		template<template<class> class Call, typename return_type, int MaxVal>
		struct call_type_from_int_impl<Call, return_type, MaxVal, MaxVal> {
			template<typename FwdType>
			static inline return_type apply(int val, FwdType const& d) {
				if (val > MaxVal) {
					std::ostringstream s;
					s << "Out-of-range value passed for parameter - Given " << val << " when the max is " << MaxVal;
					throw std::runtime_error(s.str());
				}
				return Call<boost::mpl::int_<MaxVal> >::apply(d);
			}
		};
		template<template<class> class Call, typename return_type, int MinVal, int MaxVal, typename FwdType>
		inline return_type call_type_from_int_range(int val, FwdType const& fwdArgs) {
			if (val < MinVal || val > MaxVal) {
				std::ostringstream s;
				s << "Out-of-range value passed for parameter - Given " << val << " when the range is [" << MinVal << ", " << MaxVal << "]";
				throw std::runtime_error(s.str());
			}
			return call_type_from_int_impl<Call, return_type, MaxVal, MinVal>::apply(val, fwdArgs);
		}

		template<template<class> class Call, typename return_type, typename FwdType>
		inline return_type call_type_from_int(int val, FwdType const& fwdArgs) {
			return call_type_from_int_range<Call, return_type, 0, 10>(val, fwdArgs);
		}
	} // end of namespace detail

	template<int MinVal, int MaxVal>
	struct RangedInt {
		int value;
		RangedInt(int v) : value(v) {}
	};

	struct DefaultValueToTemplatePolicy {
		template<typename T>
		struct Select {};
	};
	template<>
	struct DefaultValueToTemplatePolicy::Select<bool> {

		template<typename return_type, template<class> class Next, typename T, typename U>
		static inline return_type apply(T const& value, U const& forwarding_args) {
			if (value) {
				return Next<typename boost::mpl::bool_<true> >::apply(forwarding_args);
			}
			return Next<typename boost::mpl::bool_<false> >::apply(forwarding_args);
		}

	};
	template<>
	struct DefaultValueToTemplatePolicy::Select<int> {

		template<typename return_type, template<class> class Next, typename T, typename U>
		static inline return_type apply(T const& value, U const& forwarding_args) {
			return detail::call_type_from_int<Next, return_type>(value, forwarding_args);
		}
	};

	template<int MinVal, int MaxVal>
	struct DefaultValueToTemplatePolicy::Select<RangedInt<MinVal, MaxVal> > {
		template<typename return_type, template<class> class Next, typename T, typename U>
		static inline return_type apply(T const& value, U const& forwarding_args) {
			return detail::call_type_from_int_range<Next, return_type, MinVal, MaxVal>(value.value, forwarding_args);
		}

	};
	/// @addtogroup GenericProgramming Generic Programming
	/// @{
	/** @brief At run-time, given a tuple, calls an appropriate version
	of the given metafunction with a mpl sequence template parameter equal
	to the runtime values passed.

	@tparam Metafunc Metafunction class, must define a "return_type" typedef
	and an "apply" static function template
	*/
	template<typename Metafunc, typename Input>
	inline typename Metafunc::return_type ValueToTemplate(Input const& input) {
		typedef DefaultValueToTemplatePolicy SelectionPolicy;
		return detail::ConvertHead<Input, Metafunc, SelectionPolicy>::apply(input);
	}
	/// @}

} // end of namespace util

#endif // INCLUDED_ValueToTemplate_h_GUID_aca63948_8bf1_45ed_ae9b_a1d817a97434
