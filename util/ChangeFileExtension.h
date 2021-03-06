/** @file
	@brief Free function (inline) to change the last file extension.

	@versioninfo@

	@date 2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_ChangeFileExtension_h_GUID_91554aea_338c_412e_bc88_e676a7f79a21
#define INCLUDED_ChangeFileExtension_h_GUID_91554aea_338c_412e_bc88_e676a7f79a21

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <string>

namespace util {

/// @addtogroup FreeFunctions Free Functions
/// @{

/// Remove the last file extension, if present, and append the new provided one
	inline std::string changeFileExtension(const std::string & origName, const std::string & newExt) {
		std::string fn = origName;
		if (fn.rfind(".") != std::string::npos) {
			fn.erase(fn.rfind("."));
		}
		fn += newExt;
		return fn;
	}

/// @}

} // end of namespace util

#endif // INCLUDED_ChangeFileExtension_h_GUID_91554aea_338c_412e_bc88_e676a7f79a21

