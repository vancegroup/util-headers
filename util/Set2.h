/** @file Set2.h
	@brief

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
	public:
		Set2(T const& a, T const& b) :
				_first(b < a ? b : a),
				_second(b < a ? a : b) {}
		Set2(Set2<T> const& other) :
			_first(other._first),
			_second(other._second) {}
		
		Set2<T> const& operator=(Set2<T> const& other) {
			_first = other._first;
			_second = other._second;
			return *this;
		}
		
		Set2<T> const& set(T const& a, T const& b) {
			Set2<T> temp(a, b);
			*this = temp;
			return *this;
		}
		
		T const& first() const { return _first; }
		T const& second() const { return _second; }
	
	private:
		T _first;
		T _second;
};

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

template<typename T>
bool operator==(Set2<T> const& a, Set2<T> const& b) {
	return (a.first() == b.first()) && (a.second() == b.second());
}

} // end of namespace util

#endif // INCLUDED_Set2_h_GUID_cfb4b70a_f756_4367_b64f_f76f4569deda

