/** @file WithHistory.h
	@brief

	@date 2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

#pragma once
#ifndef INCLUDED_WithHistory_h_GUID_9945f279_0f44_4873_bdc3_2a5ba6dba018
#define INCLUDED_WithHistory_h_GUID_9945f279_0f44_4873_bdc3_2a5ba6dba018

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <algorithm>

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{
	/** @brief Container class for a value varying over time, where you might want
		to know not only the "current" value, but the value prior to most recent
		"advance/swap" event that your code initiates.

		One example would be values valid for the last frame and current frame of
		some simulation.

		Works nicely holding STL containers, as well as other "value-type" objects:
		that is, things that aren't complicated and pointer-y.

		@tparam T Contained type.
	*/
	template<typename T>
	class WithHistory {
		public:
			/// Contained value type
			typedef T value_type;

			/// Reference to contained value type
			typedef T & value_ref_type;

			/// Reference to const contained value type
			typedef T const& value_const_ref_type;
		private:
			/// One of the contained values
			T _a;

			/// The other contained value
			T _b;

			/// Pointer to the contained value deemed "current"
			T * _current;

			/// Pointer to the contained value deemed "previous"
			T * _previous;
		public:
			/// Default constructor: creates previous and current values
			/// by default construction
			WithHistory() :
				_current(&_a),
				_previous(&_b)  { }


			/// Value constructor: creates current value by copy construction,
			/// and previous value by default construction
			explicit WithHistory(T curVal) :
				_a(curVal),
				_current(&_a),
				_previous(&_b) { }

			/// Value constructor: creates current and previous values
			/// by copy construction.
			WithHistory(T curVal, T prevVal) :
				_a(curVal),
				_b(prevVal),
				_current(&_a),
				_previous(&_b) { }

			/// Copy constructor
			WithHistory(WithHistory const& other) :
				_a(other._a),
				_b(other._b),
				_current(&_a),
				_previous(&_b) { }

			/// Assignment operator
			WithHistory & operator=(WithHistory const& other) {
				if (this == &other) {
					/// self-assign is a no-op
					return *this;
				}
				current() = other.current();
				previous() = other.previous();
			}

			/// Accessor for current value - can be used as an l-value
			value_ref_type current() {
				return *_current;
			}

			/// Const accessor for current value
			value_const_ref_type current() const {
				return *_current;
			}

			/// Accessor for "previous" value - can be used as an l-value
			/// but this makes little sense in the context of this container.
			value_ref_type previous() {
				return *_previous;
			}

			/// Const accessor for "previous" value
			value_const_ref_type previous() const {
				return *_previous;
			}

			/// Advance history by a simple swap.
			///
			/// Make previous() return what current() returns now, and vice-versa.
			/// If you want to start with a "clean" current value, it is
			/// your responsibility to do so after this method.
			void swap() {
				std::swap(_current, _previous);
			}

			/// Advance history by copying.
			///
			/// Make previous() return what current() returns now, and initialize
			/// the new "current()" with a copy of this value.
			void advanceByCopy() {
				(*_previous) = (*_current);
				swap();
			}

	};

/// @}

} // end of namespace util

#endif // INCLUDED_WithHistory_h_GUID_9945f279_0f44_4873_bdc3_2a5ba6dba018
