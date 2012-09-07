/** @file
	@brief Header for invoking a functor with a type parameter chosen at
	runtime from a typelist.

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
#include <boost/mpl/less.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>

// Standard includes
// - none

namespace util {
	/// @addtogroup Metaprogramming
	/// @{

	/// @internal
	namespace detail {
		/// @brief Utility template to call a functor's apply method, templated
		/// on the MPL integral constant with value equal to that provided at runtime.
		///
		/// Iteration will find the appropriate constant in the half-open range
		/// [0, Limit) by default. (Directly calling the templated apply method
		/// with an alternate starting point is also possible)
		///
		/// @internal
		template<typename IntType, typename Limit, typename F>
		struct runtime_int_to_type_impl {
			private:
				/// @brief Self typedef for convenience.
				typedef runtime_int_to_type_impl<IntType, Limit, F> type;

				/// @brief Metafunction to determine when to stop recursing
				template<typename Current>
				struct IsValidIndex : boost::mpl::less<Current, Limit>::type {};


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

				/// @brief "base case" - when we've reached the end of where we should
				/// be iterating.
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
					type::apply<Current>(i, op, IsValidIndex<Current>());
				}

		};

		/// @brief Utility struct for apply_at
		///
		/// Templated functor with templated function call operator that
		/// looks up the element at the given index, and calls the user-provided
		/// functor with this type wrapped in boost::mpl::identity as the only
		/// argument
		///
		/// @internal
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

	/// @brief Invokes a functor with a type parameter chosen at runtime by index
	/// from a type sequence.
	///
	/// A template function that will call a user-provided functor
	/// passing a single parameter, a boost::mpl::identity object parameterized
	/// by the ith element of the given MPL sequence
	template<typename Sequence, typename F>
	inline void apply_at(typename boost::uint_value_t<boost::mpl::size<Sequence>::type::value>::least i, F operation) {
		typedef typename boost::mpl::size<Sequence>::type sequence_length;
		typedef typename boost::uint_value_t<sequence_length::value>::least index_type;
		typedef detail::apply_at_functor_impl<F, Sequence> functor_wrapper;
		typedef detail::runtime_int_to_type_impl<index_type, sequence_length, functor_wrapper &> int_to_type;

		functor_wrapper wrappedOp(operation);

		int_to_type::apply(i, wrappedOp);
	}
	/// @}
} // end of namespace util


#endif // INCLUDED_MPLRuntimeAt_h_GUID_6bdb6d98_b8f6_48d6_aa23_378c7de0e596
