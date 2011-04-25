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

	template<typename T>
	class WithHistory {
		public:
			typedef T value_type;
			typedef T & value_ref_type;
			typedef T const& value_const_ref_type;
		private:
			int _currentIdx;
			T _contained[2];
			T * _current;
			T * _previous;
		public:
			WithHistory() :
				_current(&(_contained[0])),
				_previous(&(_contained[1]))  {
			}

			WithHistory(T prevVal) :
				_current(&(_contained[0])),
				_previous(&(_contained[1])) {
				_contained[1] = prevVal;
			}
			value_ref_type current() {
				return *_current;
			}

			value_const_ref_type current() const {
				return *_current;
			}

			value_ref_type previous() {
				return *_previous;
			}

			value_const_ref_type previous() const {
				return *_previous;
			}

			void swap() {
				std::swap(_current, _previous);
			}

	};


} // end of namespace util

#endif // INCLUDED_WithHistory_h_GUID_9945f279_0f44_4873_bdc3_2a5ba6dba018
