/**
	@file  GetLocalComputerName.h
	@brief Provides a cross-platform interface to getting the computer name.

	@date
	2009-2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2009-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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
#include <cstring>

namespace util {

/// @addtogroup FreeFunctions Free Functions
/// @{

	static const size_t NETWORK_STR_LEN = 256;
	std::string GetLocalComputerName() {
		char hostname[NETWORK_STR_LEN];
		std::memset(hostname, 0, sizeof(hostname));
		int ret = gethostname(hostname, NETWORK_STR_LEN);
		if (ret == 0) {
			return std::string(hostname);
		}
		return std::string();
	}

	std::string GetLocalDomainName() {
#if !defined(_WIN32)
		char domainname[NETWORK_STR_LEN];
		std::memset(domainname, 0, sizeof(domainname));
		int ret = getdomainname(&domainname[0], NETWORK_STR_LEN);
		if (ret == 0) {
			return std::string(domainname);
		}
#endif
		return std::string();
	}

	std::string GetFullLocalComputerName() {
		return GetLocalComputerName() + GetLocalDomainName();
	}

/// @}

} // end of util namespace

#endif // INCLUDED_GetLocalComputerName_h_GUID_40bc94c9_d917_4cc2_9b0b_00fc13454b01

