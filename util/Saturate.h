/**	@file
	@brief	Simple vector saturation.

	@date
	2009-2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2009-2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_util_Saturate_h_GUID_8E496A1E_CA76_11DF_8972_7DCDDFD72085
#define INCLUDED_util_Saturate_h_GUID_8E496A1E_CA76_11DF_8972_7DCDDFD72085

// Local includes
// - none

// Library includes
#include <Eigen/Core>

// Standard includes
// - none

namespace util {

/// @addtogroup Math Math Utilities
/// @{

	/** Saturate the vector at the given max magnitude.

		@param vec The input and output vector
		@param maxMagnitude the maximum magnitude @paramref vec is permitted to have

		@returns true if this vector was saturated.

		vec stays the same if it has magnitude < maxMagnitude, otherwise
		it returns a vector of magnitude maxMagnitude in the direction of vec
	*/
	inline bool saturate(Eigen::Vector3d & vec, double const maxMagnitude) {
		if (vec.squaredNorm() > maxMagnitude * maxMagnitude) {
			const double reduction = (maxMagnitude / vec.norm());
			vec *= reduction;
			return true;
		}
		return false;
	}

	/** Saturate the vector at the given max magnitude.

		@param vec The input and output vector
		@param maxMagnitude the maximum magnitude @paramref vec is permitted to have
		@param otherVec the paired vector which will be scaled in proportion to @paramref vec's scaling

		@returns true if this vector was saturated.

		vec stays the same if it has magnitude < maxMagnitude, otherwise
		it returns a vector of magnitude maxMagnitude in the direction of vec.
		If vec is scaled down to not exceed maxMagnitude, scale down otherVec
		by the same proportion.
	*/
	inline bool saturate(Eigen::Vector3d & vec, double const maxMagnitude, Eigen::Vector3d & otherVec) {
		if (vec.squaredNorm() > maxMagnitude * maxMagnitude) {
			const double reduction = (maxMagnitude / vec.norm());
			vec *= reduction;
			otherVec *= reduction;
			return true;
		}
		return false;
	}

/// @}

}
#endif // INCLUDED_util_Saturate_h_GUID_8E496A1E_CA76_11DF_8972_7DCDDFD72085

