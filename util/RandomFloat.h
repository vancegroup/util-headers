/**	@file	RandomFloat.h
	@brief	Utility header to generate a random float.

	@date	2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/
#pragma once
#ifndef _RandomFloat_h_
#define _RandomFloat_h_

// Local includes
// - none

// Library includes
// - none

// Standard includes
#include <cstdlib>

namespace util {
	/// Return a random float in [0, 1]
	inline float randomFloat() {
		return static_cast<float>(::std::rand())/RAND_MAX;
	}

	/// Return a random double in [0, 1]
	inline double randomDouble() {
		return static_cast<double>(::std::rand())/RAND_MAX;
	}
}

#endif // _RandomFloat_h_
