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

	/// Container class for a value varying over time, where you might want
	/// to know not only the "current" value, but the value prior to most recent
	/// "advance/swap" event that your code initiates.
	/// last/this frame, etc.
	/// Does just swell holding STL containers.
	template<typename T>
	class WithHistory {
		public:
			typedef T value_type;
			typedef T & value_ref_type;
			typedef T const& value_const_ref_type;
		private:
			int _currentIdx;
			T _a;
			T _b;
			T * _current;
			T * _previous;
		public:
			/// Default constructor: creates previous and current values
			/// by default construction
			WithHistory() :
				_current(&_a),
				_previous(&_b)  { }


			/// Value constructor: creates current value by copy construction,
			/// and previous value by default construction
			WithHistory(T curVal) :
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

			/// Make previous() return what current() returns now, and vice-versa.
			/// If you want to start with a "clean" current value, it is
			/// your responsibility to do so after this method.
			void swap() {
				std::swap(_current, _previous);
			}

			/// Make previous() return what current() returns now, and initialize
			/// the new "current()" with a copy of this value.
			void advanceByCopy() {
				(*_previous) = (*_current);
				swap();
			}

	};


} // end of namespace util

#endif // INCLUDED_WithHistory_h_GUID_9945f279_0f44_4873_bdc3_2a5ba6dba018
