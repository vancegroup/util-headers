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

namespace std {
	/// Forward declarations
	template<typename T, typename Allocator>
	class Vector;
	template<typename Key, typename T, typename Compare, typename Allocator>
	class Map;
	template<typename Key, typename Compare, typename Allocator>
	class Set;
} // end of namespace std

namespace util {
	namespace detail {
		/// Templated default function to clear an object using assignment
		/// operator and default constructor
		template<typename T>
		struct ClearByDefaultConstruction {
			void apply(T & obj) {
				obj = T();
			}
		};

		/// For all types without specializations, clearing history
		/// occurs by default construction and assignment.
		template<typename T>
		struct DefaultHistoryClear : ClearByDefaultConstruction<T> {};

		/// Templated way of clearing objects with a clear method.
		template<typename T>
		struct HistoryClearByClearMethod {
			void apply(T & obj) {
				obj.clear();
			}
		};
		/*
				/// use a clear method to clear std::vector types by default
				template<typename T>
				struct DefaultHistoryClear< std::vector<T> > : HistoryClearByClearMethod< std::vector<T> > {};

				/// use a clear method to clear std::map types by default
				template<typename KeyT, typename ValT>
				struct DefaultHistoryClear< std::map<KeyT, ValT> > : HistoryClearByClearMethod< std::map<KeyT, ValT> > {};

				/// use a clear method to clear std::set types by default
				template<typename T>
				struct DefaultHistoryClear< std::set<T> > : HistoryClearByClearMethod< std::set<T> > {};
		*/
	} // end of namespace detail

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
