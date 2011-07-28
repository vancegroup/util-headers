/**	@file
	@brief	Utility header to generate a random float.

	@date	2010-2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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

	/// Return a random floating point type in [0, 1]
	template<typename Scalar>
	inline Scalar random01() {
		return static_cast<Scalar>(::std::rand()) / RAND_MAX;
	}

	/// Return a random float in [0, 1]
	inline float randomFloat() {
		return random01<float>();
	}

	/// Return a random double in [0, 1]
	inline double randomDouble() {
		return random01<double>();
	}


/// @}

}

#endif // INCLUDED_RandomFloat_h_GUID_8bc80329_72d0_45bc_af08_671fb074f875

