/** @file	SplitMap.h
	@brief	header to split std::maps (or things that look like them)
	into things you'd rather have.

	@date	2010

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
#ifndef INCLUDED_SplitMap_h_GUID_7c123d17_2fc7_4404_8108_3dc819b374b9
#define INCLUDED_SplitMap_h_GUID_7c123d17_2fc7_4404_8108_3dc819b374b9

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none


namespace util {

/// @addtogroup FreeFunctions Free Functions
/// @{

/// Given a map, return a vector of all the keys
	template<class MapType, class VectorType>
	VectorType getAllKeys(MapType const & map) {
		VectorType ret;
		for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
			ret.push_back(it->first);
		}
		return ret;
	}

/// Given a map, return a vector of all the values
	template<class MapType, class VectorType>
	VectorType getAllValues(MapType const & map) {
		VectorType ret;
		for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
			ret.push_back(it->second);
		}
		return ret;
	}

/// Given a map, return a vector of keys and a vector of values
	template<class MapType, class PairVectorType>
	PairVectorType getSplit(MapType const & map) {
		PairVectorType ret;
		for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
			ret.first.push_back(it->first);
			ret.second.push_back(it->second);
		}
		return ret;
	}

/// @}

} // end of util namespace

#endif // INCLUDED_SplitMap_h_GUID_7c123d17_2fc7_4404_8108_3dc819b374b9

