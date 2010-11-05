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
#ifndef INCLUDED_RandomFloat_h_GUID_8bc80329_72d0_45bc_af08_671fb074f875
#define INCLUDED_RandomFloat_h_GUID_8bc80329_72d0_45bc_af08_671fb074f875


// Local includes
// - none

// Library includes
// - none

// Standard includes
#include <cstdlib>

namespace util {

/// @addtogroup Math Math Utilities
/// @{

	/// Return a random float in [0, 1]
	inline float randomFloat() {
		return static_cast<float>(::std::rand())/RAND_MAX;
	}

	/// Return a random double in [0, 1]
	inline double randomDouble() {
		return static_cast<double>(::std::rand())/RAND_MAX;
	}


/// @}

}

#endif // INCLUDED_RandomFloat_h_GUID_8bc80329_72d0_45bc_af08_671fb074f875

