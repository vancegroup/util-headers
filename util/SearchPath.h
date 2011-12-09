/** @file
	@brief Header

	@date 2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_SearchPath_h_GUID_7a79b983_9d8b_4185_80ab_77146a676bdf
#define INCLUDED_SearchPath_h_GUID_7a79b983_9d8b_4185_80ab_77146a676bdf

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <string>

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{
	/// @todo static const char PATH_SEPARATOR = ";";
	/** @brief Class representing an element in a search path.

		This uses the generalized concept of a search path as used
		by Lua: a filename with a character that is replaced to form
		a potential filename.
	*/
	class SearchPathElement {
		public:
			/// @brief default constructor
			SearchPathElement() {}

			/** @brief Constructor from either a prefix alone or a path with a placeholder

				Three cases:
					1. /bla/bla/
					2. /bla/bla/?
					3. /bla/bla/?.lua
			*/
			SearchPathElement(std::string const& elt) {
				std::size_t placeholder = elt.find(PLACEHOLDER);
				if (placeholder == std::string::npos) {
					// Handle case 1
					// Didn't find a placeholder, so treat the whole thing as the prefix
					_prefix = elt;
				} else {
					// Found a placeholder: split into prefix and suffix
					// We're in case 2 or 3
					_prefix = elt.substr(0, placeholder);
					if (placeholder + 1 < elt.size()) {
						// We actually have a suffix: case 3
						_suffix = elt.substr(placeholder + 1);
					}
				}
			}

			/** @brief Constructor from a prefix and suffix
			*/
			SearchPathElement(std::string const & pre, std::string const & suff)
				: _prefix(pre)
				, _suffix(suff)
			{}

			/// @brief Get prefix: the part before the placeholder
			std::string const& getPrefix() const;

			/// @brief Get suffix: the part after the placeholder
			std::string const& getSuffix() const;

			/// @brief Combine prefix, placeholder or value of your choice, and suffix
			std::string getFullWithSubstitution(std::string const& substitution = std::string(1, PLACEHOLDER)) const;

			/// @brief Set prefix
			void setPrefix(std::string const& s);

			/// @brief Set suffix
			void setSuffix(std::string const& s);
		private:
			static const char PLACEHOLDER = '?';
			std::string _prefix;
			std::string _suffix;
	};

	/// @brief Equality comparison operator for path elements.
	inline bool operator==(SearchPathElement const& lhs, SearchPathElement const& rhs) {
		return (lhs.getPrefix() == rhs.getPrefix()) && (lhs.getSuffix() == rhs.getSuffix());
	}

	inline std::string const& SearchPathElement::getPrefix() const {
		return _prefix;
	}

	inline std::string const& SearchPathElement::getSuffix() const {
		return _suffix;
	}

	inline std::string SearchPathElement::getFullWithSubstitution(std::string const& substitution) const {
		return _prefix + substitution + _suffix;
	}

	inline void SearchPathElement::setPrefix(std::string const& s) {
		/// @todo Check for placeholder in this value and handle it?
		/// Setting the prefix to something like /bla/?/ would be weird.
		_prefix = s;
	}

	inline void SearchPathElement::setSuffix(std::string const& s) {
		/// @todo Check for placeholder in this value and handle it?
		/// Setting the prefix to something like /bla/?/ would be weird.
		_suffix = s;
	}


/// @}

} // end of namespace util

#endif // INCLUDED_SearchPath_h_GUID_7a79b983_9d8b_4185_80ab_77146a676bdf
