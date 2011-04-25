/** @file CountedUniqueValues.h
	@brief

	@date 2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

#pragma once
#ifndef INCLUDED_CountedUniqueValues_h_GUID_d5bcc295_2389_4737_8bff_bef3653249e8
#define INCLUDED_CountedUniqueValues_h_GUID_d5bcc295_2389_4737_8bff_bef3653249e8

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <vector>
#include <map>

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{

	/// A container template that numbers and stores unique values.
	template<typename value_type>
	class CountedUniqueValues {
		public:
			typedef unsigned int count_type;
			typedef std::vector<value_type> storage_type;

			count_type store(value_type const& v) {
				count_type i = _storage.size();
				if (_lookup.find(v) != _lookup.end()) {
					// Found it
					/// @todo double lookups
					i = _lookup[v];
				} else {
					// Adding it
					_storage.push_back(v);
					_lookup[v] = i;
				}
				return i;
			}


			/// @todo dangerous because of not changing the lookup?
			value_type & get(count_type const& i) {
				return _storage.at(i);
			}

			value_type const& get(count_type const& i) const {
				return _storage.at(i);
			}

			count_type size() const {
				return _storage.size();
			}

		protected:
			std::vector<value_type> _storage;
			std::map<value_type, count_type> _lookup;

	};


} // end of namespace util

#endif // INCLUDED_CountedUniqueValues_h_GUID_d5bcc295_2389_4737_8bff_bef3653249e8
