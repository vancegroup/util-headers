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
#include <string>
#include <sstream>
#include <stdexcept>

namespace util {

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
			static inline return_type apply(const char * paramName, int val, FwdType const & d, int maxval = Max) {
				if (val == Iter) {
					return Call<boost::mpl::int_<Iter> >::apply(d);
				}
				return call_type_from_int_impl < Call, return_type, Max, Iter + 1 >::apply(paramName, val, d);
			}
		};
		inline std::string getOutOfRangeErrorString(const char * paramName, int val, int maxval) {
			std::ostringstream s;
			s << "Out-of-range value passed for parameter " << paramName << ": Given " << val << " when the max is  " << maxval;
			return s.str();
		}
		/// specialization for base case
		template<template<class> class Call, typename return_type, int MaxVal>
		struct call_type_from_int_impl<Call, return_type, MaxVal, MaxVal> {
			template<typename FwdType>
			static inline return_type apply(const char * paramName, int val, FwdType & d) {
				if (val > MaxVal) {
					throw std::runtime_error(getOutOfRangeErrorString(paramName, val, MaxVal));
				}
				return Call<boost::mpl::int_<MaxVal> >::apply(d);
			}
		};
	} // end of namespace detail
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
			return detail::call_type_from_int_impl<Next, return_type, 10>::apply("", value, forwarding_args);
		}
	};

	template<int MinVal, int MaxVal>
	struct DefaultValueToTemplatePolicy::Select<RangedInt<MinVal, MaxVal> > {

		template<typename return_type, template<class> class Next, typename T, typename U>
		static inline return_type apply(T const& value, U const& forwarding_args) {
			return detail::call_type_from_int_impl<Next, return_type, MaxVal, MinVal>::apply("", value, forwarding_args);
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
