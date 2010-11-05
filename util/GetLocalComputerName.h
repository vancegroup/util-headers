/**
	@file GetLocalComputerName.h
	@brief Provides a cross-platform interface to getting the computer name.

	@date
	2009

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

#pragma once
#ifndef INCLUDED_GetLocalComputerName_h_GUID_40bc94c9_d917_4cc2_9b0b_00fc13454b01
#define INCLUDED_GetLocalComputerName_h_GUID_40bc94c9_d917_4cc2_9b0b_00fc13454b01

// Local includes
// - none

// Library includes
#if defined(_WIN32)
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#endif

// Standard includes
#include <string>

namespace util {

/// @addtogroup FreeFunctions Free Functions
/// @{

std::string GetLocalComputerName() {
	char hostname[256];
	std::string host;
	for (int i = 0; i < 256; i++) { hostname[i] = 0; }
	int ret = gethostname(&hostname[0], 255);
	if (ret == 0) {
		host = std::string(hostname);
	}
	return host;
}

std::string GetLocalDomainName() {
	std::string domain("");
#if !defined(_WIN32)
	char domainname[256];
	for (int i = 0; i < 256; i++) { domainname[i] = 0; }
	int ret = getdomainname(&domainname[0], 256);
	if (ret == 0) {
		domain = domainname;
	}
#endif
   return domain;
}

std::string GetFullLocalComputerName() {
	return GetLocalComputerName() + GetLocalDomainName();
}

/// @}

} // end of util namespace

#endif // INCLUDED_GetLocalComputerName_h_GUID_40bc94c9_d917_4cc2_9b0b_00fc13454b01

