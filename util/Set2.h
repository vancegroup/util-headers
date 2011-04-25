/** @file Set2.h
	@brief Template class for holding two interchangeable elements that
	we nevertheless want to be compatible with STL containers and algos

	@date 2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/


#pragma once
#ifndef INCLUDED_Set2_h_GUID_cfb4b70a_f756_4367_b64f_f76f4569deda
#define INCLUDED_Set2_h_GUID_cfb4b70a_f756_4367_b64f_f76f4569deda

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <algorithm>

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{

	/** @brief Container class for two interchangeable values.

		Allows use of a pair of values without concern as to what order they
		are in.  Particularly useful as a key in maps to avoid needing
		double-sized nested maps.

		Should be compatible with most (if not all) STL containers and algorithms.

		@invariant Internally maintains ! (second < first)

		@tparam T Contained type.

		@todo How to enforce a single representation for cases in which
		! (a < b) but also ! (b < a), but a != b in some meaningful way?

		@todo Note about handling NAN?
	*/
	template<typename T>
	class Set2 {
		public:
			/// Contained value type
			typedef T value_type;

			/// Default constructor: requires T be default constructible and have
			/// an assignment operator
			Set2() {
				if (_second < _first) {
					std::swap(_first, _second);
				}
			}

			/// Constructor from values: requires T be copy constructible
			Set2(T const& a, T const& b) :
				_first(b < a ? b : a),
				_second(b < a ? a : b) {}

			/// Copy constructor
			Set2(Set2<T> const& other) :
				_first(other._first),
				_second(other._second) {}

			/// Assignment operator
			Set2<T> const& operator=(Set2<T> const& other) {
				if (&other == this) {
					/// Shortcut self-assignment
					return *this;
				}
				_first = other._first;
				_second = other._second;
				return *this;
			}

			/// Mutator: must change both at once to enforce internal order
			Set2<T> const& set(T const& a, T const& b) {
				Set2<T> temp(a, b);
				*this = temp;
				return *this;
			}

			/// Accessor for the "smaller" of the two elements
			T const& first() const {
				return _first;
			}

			/// Accessor for the "larger" of the two elements
			T const& second() const {
				return _second;
			}

		private:
			/// Storage of smaller element or element passed first
			T _first;

			/// Storage of larger element or element passed second
			T _second;
	};

/// @brief Comparison operator for Set2 containers: uses only operator<
/// @relates Set2
	template<typename T>
	bool operator<(Set2<T> const& a, Set2<T> const& b) {
		/// The somewhat awkward series of comparisons is to
		/// avoid using any operator except operator<
		if (a.first() < b.first()) {
			return true;
		} else if (b.first() < a.first()) {
			return false;
		} else {
			return a.second() < b.second();
		}
	}

/// @brief Equality operator for Set2 containers: uses operator==
/// @relates Set2
	template<typename T>
	bool operator==(Set2<T> const& a, Set2<T> const& b) {
		/// @todo should we be using combined < calls here?
		return (a.first() == b.first()) && (a.second() == b.second());
	}

/// @}

} // end of namespace util

#endif // INCLUDED_Set2_h_GUID_cfb4b70a_f756_4367_b64f_f76f4569deda

