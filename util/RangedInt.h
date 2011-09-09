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
#ifndef INCLUDED_RangedInt_h_GUID_2295a8dd_08fa_4f09_9708_9dc525156a3d
#define INCLUDED_RangedInt_h_GUID_2295a8dd_08fa_4f09_9708_9dc525156a3d

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <stdexcept>
#include <cassert>


namespace util {

	struct AlwaysCheck {
		static const bool checked = true;
	};
	struct NeverCheck {
		static const bool checked = false;
	};

#ifdef NDEBUG
	struct CheckInDebug : NeverCheck {};
#else
	struct CheckInDebug : AlwaysCheck {};
#endif

	struct ThrowOutOfRange {
		template<int MinVal>
		static void belowMin(int) {
			throw std::out_of_range("Below minimum value for a ranged int!");
		}

		template<int MaxVal>
		static void aboveMax(int) {
			throw std::out_of_range("Above maximum value for a ranged int!");
		}
	};

	struct AssertOutOfRange {
		template<int MinVal>
		static void belowMin(int val) {
			assert(val >= MinVal);
		}
		template<int MaxVal>
		static void aboveMax(int val) {
			assert(val <= MaxVal);
		}
	};

	template<int MinVal, int MaxVal, typename CheckingPolicy, typename ErrorPolicy>
	class RangedInt;

	namespace detail {
		struct NullCheck {
			static void check(int) {}
		};

		template<bool actuallyCheck, int MinVal, typename ErrorPolicy>
		struct CheckMin {
			static void check(int val) {
				if (val < MinVal) {
					ErrorPolicy::template belowMin<MinVal>(val);
				}
			}
		};

		template<int MinVal, typename ErrorPolicy>
		struct CheckMin<false, MinVal, ErrorPolicy> : NullCheck { };

		template<bool actuallyCheck, int MaxVal, typename ErrorPolicy>
		struct CheckMax {
			static void check(int val) {
				if (val > MaxVal) {
					ErrorPolicy::template aboveMax<MaxVal>(val);
				}
			}
		};


		template<int  MaxVal, typename ErrorPolicy>
		struct CheckMax<false,  MaxVal, ErrorPolicy> : NullCheck { };

		template<bool actuallyCheck, int MinVal, int MaxVal, typename ErrorPolicy>
		struct DoRangeCheck {
			static void check(int val) {
				CheckMin<actuallyCheck, MinVal, ErrorPolicy>::check(val);
				CheckMax<actuallyCheck, MaxVal, ErrorPolicy>::check(val);
			}
		};
	} // end of namespace detail

/// @addtogroup DataStructures Data Structures
/// @{

	/// A lightweight container template for integer values from a compile-time-defined range,
	/// with range checking and error handling as policy classes.
	/// @todo static assert that minVal <= maxVal
	template<int MinVal, int MaxVal, typename CheckingPolicy = AlwaysCheck, typename ErrorPolicy = ThrowOutOfRange>
	class RangedInt {
		public:
			static const bool checked = CheckingPolicy::checked;
			static const int min_val = MinVal;
			static const int max_val = MaxVal;

			typedef RangedInt<MinVal, MaxVal, CheckingPolicy, ErrorPolicy> self_type;

		private:
			int value;
			void _rangeCheck() const {
				detail::DoRangeCheck<checked, MinVal, MaxVal, ErrorPolicy>::check(value);
			}

			template<typename SrcType>
			void _crossRangeCheck(SrcType const&) {
				detail::CheckMin < (checked && ((SrcType::min_val < MinVal) || !SrcType::checked)), MinVal, ErrorPolicy >::check(value);
				detail::CheckMax < (checked && ((SrcType::max_val > MaxVal) || !SrcType::checked)), MaxVal, ErrorPolicy >::check(value);
			}

		public:
			operator int() const {
				return value;
			}

			RangedInt(int v)
				: value(v) {
				_rangeCheck();
			}

			RangedInt(self_type const& other)
				: value(other.value) {
				/* known ok, copy from same type */
			}

			template<int SrcMin, int SrcMax, typename SrcCheckingPolicy, typename SrcErrorPolicy>
			RangedInt(RangedInt<SrcMin, SrcMax, SrcCheckingPolicy, SrcErrorPolicy> const& other)
				: value(int(other)) {
				_crossRangeCheck(other);
			}

			self_type & operator=(int v) {
				value = v;
				_rangeCheck();
				return *this;
			}

			self_type & operator=(self_type const& other) {
				/* known ok, copy from same type */
				value = other.value;
				return *this;
			}

			template<int SrcMin, int SrcMax, typename SrcCheckingPolicy, typename SrcErrorPolicy>
			self_type & operator=(RangedInt<SrcMin, SrcMax, SrcCheckingPolicy, SrcErrorPolicy> const& other) {
				value = int(other);
				_crossRangeCheck(other);
				return *this;
			}
	};


} // end of namespace util

#endif // INCLUDED_RangedInt_h_GUID_2295a8dd_08fa_4f09_9708_9dc525156a3d
