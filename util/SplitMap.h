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

#pragma once
#ifndef _util_SplitMap_h_
#define _util_SplitMap_h_

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none

namespace util {

template<class MapType, class VectorType>
VectorType getAllKeys(MapType const & map) {
	VectorType ret;
	for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
		ret.push_back(it->first);
	}
	return ret;
}

template<class MapType, class VectorType>
VectorType getAllValues(MapType const & map) {
	VectorType ret;
	for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

template<class MapType, class PairVectorType>
PairVectorType getSplit(MapType const & map) {
	PairVectorType ret;
	for (typename MapType::const_iterator it = map.begin(); it != map.end(); ++it) {
		ret.first.push_back(it->first);
		ret.second.push_back(it->second);
	}
	return ret;
}


} // end of util namespace

#endif // _util_SplitMap_h_
