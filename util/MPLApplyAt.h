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
#ifndef INCLUDED_MPLApplyAt_h_GUID_6bdb6d98_b8f6_48d6_aa23_378c7de0e596
#define INCLUDED_MPLApplyAt_h_GUID_6bdb6d98_b8f6_48d6_aa23_378c7de0e596

// Internal Includes
// - none

// Library/third-party includes
#include <boost/integer.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>

// Standard includes
// - none

namespace util {
	namespace detail {
		/// @brief Utility template to call a functor's apply method, templated
		/// on the MPL integral constant with value equal to that provided at runtime.
		template<typename IntType, typename Limit, typename F>
		struct runtime_int_to_type_impl {
			private:
				typedef typename boost::mpl::lambda<boost::mpl::less<boost::mpl::_, Limit> >::type validity_check;
				typedef runtime_int_to_type_impl<IntType, Limit, F> type;
				/// @brief Main recursive function: checks for equality and either
				/// runs functor or recurses with the next integer.
				template<typename Current>
				static void apply(IntType i, F op, boost::mpl::bool_<true> const&) {
					if (Current::value == i) {
						op.template operator()<Current>();
					} else {
						type::apply<typename boost::mpl::next<Current>::type>(i, op);
					}
				}

				template<typename Current>
				static void apply(IntType, F, boost::mpl::bool_<false> const&) {
					/// @todo appropriate error behavior?
				}

			public:
				/// @brief main entrance point: starts off at zero.
				static void apply(IntType i, F op) {
					typedef boost::mpl::int_<0> Zero;
					type::apply<Zero>(i, op);
				}

				/// @brief Utility trampoline for recursion: performs the application
				/// of the validity check for tag-dispatching of recusive call or base case.
				template<typename Current>
				static void apply(IntType i, F op) {
					type::apply<Current>(i, op, typename boost::mpl::apply<validity_check, Current>::type());
				}

		};

		template<typename F, typename Sequence>
		struct apply_at_functor_impl {
			apply_at_functor_impl(F operation) : op(operation) {}

			template<typename Index>
			void operator()() {
				op.operator()(boost::mpl::identity<typename boost::mpl::at<Sequence, Index>::type >());
			}

			F op;
		};

	} // end of namespace detail

	/// @brief A template function that will call a user-provided functor
	///
	template<typename Sequence, typename F>
	inline void apply_at(typename boost::uint_value_t<boost::mpl::size<Sequence>::type::value>::least index, F operation) {
		typedef typename boost::mpl::size<Sequence>::type sequence_length;
		typedef typename boost::uint_value_t<sequence_length::value>::least index_type;
		typedef detail::apply_at_functor_impl<F, Sequence> functor_wrapper;
		typedef detail::runtime_int_to_type_impl<index_type, sequence_length, functor_wrapper &> int_to_type;

		functor_wrapper wrappedOp(operation);

		int_to_type::apply(index, wrappedOp);
	}
} // end of namespace util


#endif // INCLUDED_MPLRuntimeAt_h_GUID_6bdb6d98_b8f6_48d6_aa23_378c7de0e596
