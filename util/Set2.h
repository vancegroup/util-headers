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

namespace util {

template<typename T>
class Set2 {
	/// @todo How to enforce a single representation for cases in which
	/// ! (a < b) but also ! (b < a), but a != b in some meaningful way?
	public:
		typedef T value_type;

		/// Default constructor: requires T be default constructible and assignment
		Set2() {
			if (_second < _first) {
				T temp(_first);
				_first = _second;
				_second = temp;
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
		T const& first() const { return _first; }

		/// Accessor for the "larger" of the two elements
		T const& second() const { return _second; }

	private:
		/// Storage of smaller element or element passed first
		T _first;

		/// Storage of larger element or element passed second
		T _second;
};

/// Comparison operator for Set2 containers: uses only operator<
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

/// Equality operator for Set2 containers: uses operator==
template<typename T>
bool operator==(Set2<T> const& a, Set2<T> const& b) {
	/// @todo should we be using combined < calls here?
	return (a.first() == b.first()) && (a.second() == b.second());
}

} // end of namespace util

#endif // INCLUDED_Set2_h_GUID_cfb4b70a_f756_4367_b64f_f76f4569deda

