/**
@file ChangeFileExtension.cpp
@author Ryan Pavlik
@version 1.0
*/

#include "ChangeFileExtension.h"

std::string changeFileExtension(const std::string & origName, const std::string & newExt) {
	std::string fn = origName;
	if (fn.rfind(".") != std::string::npos) {
		fn.erase(fn.rfind("."));
	}
	fn += newExt;
	return fn;
}