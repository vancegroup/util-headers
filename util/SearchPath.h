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
#include <boost/tokenizer.hpp>

// Standard includes
#include <string>
#include <deque>
#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{
	/// @todo static const char PATH_SEPARATOR = ";";
	/** @brief Class representing an element in a search path.

		This uses the generalized concept of a search path as used
		by Lua: a "template" filename that may contain a character that
		is replaced to form a potential filename.
	*/
	class SearchPathElement {
		public:
			/// @name Constructors
			/// @{

			/// @brief default constructor - corresponds to "?"
			SearchPathElement()
				: _hasPlaceholder(true)
			{}

			/** @brief Named constructor for a search path element corresponding
				to a directory.

				This normalizes the element to end in / if it does not already.
			*/
			static SearchPathElement createFromDirectory(std::string const& elt);

			/** @brief Named constructor for a search path element in the Lua style:
				either a fixed value or containing a placeholder value (which splits the
				element into a prefix and suffix).
			*/
			static SearchPathElement createFromPlaceholderString(std::string const& elt,
			        const char placeholderChar = PLACEHOLDER);

			/** @brief Constructor from either a prefix alone or a path
				with a placeholder (a "Lua-style" search path element).

				Tries to guess what you mean - usually you want to use
				one of the named constructors.

				Five cases:
					1. /bla/bla/ - assumed to be equivalent to case 2.
					2. /bla/bla/?
					3. /bla/bla/?.lua or /bla/bla/lib?.so
					4. /bla/bla/fallback.lua - not converted to case 2 because
						it doesn't end in a path separator.
					5. Empty input - degenerate case, treated as case 1.
			*/
			explicit SearchPathElement(std::string const& elt)
				: _hasPlaceholder(true) {
				std::size_t placeholder = elt.find(PLACEHOLDER);
				if (placeholder == std::string::npos) {
					// Handle case 1 and 4
					// Didn't find a placeholder, so treat the whole thing as the prefix
					_prefix = elt;
					// Is this a directory? or a fixed path?
					_hasPlaceholder = !_endsInPathSeparator(elt);
				} else {
					// Found a placeholder: split into prefix and suffix
					// We're in case 2 or 3
					_prefix = elt.substr(0, placeholder);
					if (placeholder + 1 < elt.size()) {
						// We actually have a suffix: case 3
						_suffix = elt.substr(placeholder + 1);
					}
				}
				assert(_suffix.empty() || _hasPlaceholder);
			}

			/** @brief Constructor from a prefix and suffix
			*/
			SearchPathElement(std::string const & pre, std::string const & suff)
				: _prefix(pre)
				, _suffix(suff)
				, _hasPlaceholder(true)
			{}

			/// @}

			/// @name Accessors
			/// @{
			/// @brief Get prefix: the part before the placeholder
			std::string const& getPrefix() const;

			/// @brief Get suffix: the part after the placeholder if applicable.
			std::string const& getSuffix() const;

			/// @brief Is there a placeholder between the prefix and suffix?
			///
			/// If not, the suffix is mandated to be empty.
			bool hasPlaceholder() const;

			/// @brief Does this represent a directory?
			bool isDirectory() const;

			/// @brief Combine prefix, placeholder or value of your choice
			/// (if this element has a placeholder), and suffix
			std::string getStringWithSubstitution(std::string const& substitution = std::string(1, PLACEHOLDER)) const;

			/** @brief Get the directory

				Same functionality as "getPrefix", but throws an exception
				if this isn't actually a directory element (if it has a placeholder)
			*/
			std::string getDirectory() const;

			/// @}

			/// @name Mutators
			/// @{
			/// @brief Set prefix
			void setPrefix(std::string const & s);

			/// @brief Set suffix (only if this element has a placeholder!
			void setSuffix(std::string const & s);
			/// @}

			/// @brief Default placeholder item
			static const char PLACEHOLDER = '?';
		private:
			/// @brief Private constructor used by named constructors.
			SearchPathElement(std::string const & pre, std::string const & suff, bool hasPlaceholder)
				: _prefix(pre)
				, _suffix(suff)
				, _hasPlaceholder(hasPlaceholder) {
				assert(_suffix.empty() || _hasPlaceholder);
			}
			static bool _endsInPathSeparator(std::string const & s);
			std::string _prefix;
			std::string _suffix;
			bool _hasPlaceholder;
	};

	/// @brief Equality comparison operator for path elements.
	inline bool operator==(SearchPathElement const& lhs, SearchPathElement const& rhs) {
		return (lhs.getPrefix() == rhs.getPrefix()) &&
		       (lhs.getSuffix() == rhs.getSuffix()) &&
		       (lhs.hasPlaceholder() == rhs.hasPlaceholder());
	}

	/// @brief Output operator for path elements.
	inline std::ostream & operator<<(std::ostream & os, SearchPathElement const& rhs) {
		os << rhs.getStringWithSubstitution();
		return os;
	}

	/// @brief A container class for SearchPathElements.
	typedef std::deque<SearchPathElement> SearchPath;

	/** @brief Parse a search path string into a SearchPath (list of search path elements).

		Empty elements are dropped.
	*/
	inline SearchPath parseSearchPathFromString(std::string const& input, const char separator[] = ";") {
		SearchPath ret;
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> sep(separator);
		tokenizer tokens(input, sep);
		for (tokenizer::const_iterator it = tokens.begin(), end = tokens.end(); it != end; ++it) {
			ret.push_back(SearchPathElement(*it));
		}
		return ret;
	}

	/** @brief Join all elements of a search path, using a placeholder.

		If this is a "directories-style" search path (no suffixes on any)
		instead of a Lua-style search path, use convertSearchPathDirectoriesToString.
	*/
	inline std::string convertSearchPathToString(SearchPath const& input,
	        std::string const& placeholder = std::string(1, SearchPathElement::PLACEHOLDER),
	        const char separator = ';') {
		std::ostringstream os;
		for (int i = 0, n = input.size(); i < n; ++i) {
			os << input[i].getStringWithSubstitution(placeholder);
			if (i + 1 < n) {
				os << separator;
			}
		}
		return os.str();
	}

	inline SearchPathElement SearchPathElement::createFromDirectory(std::string const& elt) {
		if (_endsInPathSeparator(elt)) {
			return SearchPathElement(elt, "", false);
		} else {
			return SearchPathElement(elt + "/", "", false);
		}
	}

	inline SearchPathElement SearchPathElement::createFromPlaceholderString(std::string const& elt,
	        const char placeholderChar) {
		std::size_t placeholder = elt.find(placeholderChar);
		if (placeholder == std::string::npos) {
			// Handle case 1 and 4
			// Didn't find a placeholder so treat the whole thing as a fixed value.
			return SearchPathElement(elt, "", false);
		}
		// Found a placeholder: split into prefix and suffix
		// We're in case 2 or 3
		if (placeholder + 1 < elt.size()) {
			// We actually have a suffix: case 3
			return SearchPathElement(elt.substr(0, placeholder), elt.substr(placeholder + 1), true);
		}
		// case 2
		return SearchPathElement(elt.substr(0, placeholder), "", true);
	}

	inline std::string const& SearchPathElement::getPrefix() const {
		return _prefix;
	}

	inline std::string const& SearchPathElement::getSuffix() const {
		return _suffix;
	}

	inline bool SearchPathElement::hasPlaceholder() const {
		return _hasPlaceholder;
	}

	inline bool SearchPathElement::isDirectory() const {
		if (!_hasPlaceholder) {
			// It's a fixed string
			return false;
		}
		return _suffix.empty() && _endsInPathSeparator(_prefix);
	}

	inline std::string SearchPathElement::getStringWithSubstitution(std::string const& substitution) const {
		if (_hasPlaceholder) {
			return _prefix + substitution + _suffix;
		} else {
			return _prefix;
		}
	}

	std::string SearchPathElement::getDirectory() const {
		if (!isDirectory()) {
			throw std::logic_error("This search path element isn't a directory!");
		}
		return _prefix;
	}

	inline void SearchPathElement::setPrefix(std::string const& s) {
		/// @todo Check for placeholder in this value and handle it?
		/// Setting the prefix to something like /bla/?/ would be weird.
		_prefix = s;
	}

	inline void SearchPathElement::setSuffix(std::string const& s) {
		if (!_hasPlaceholder) {
			throw std::logic_error("Can't set the suffix of a search path element without a placeholder!");
		}
		/// @todo Check for placeholder in this value and handle it?
		/// Setting the prefix to something like /bla/?/ would be weird.
		_suffix = s;
	}

	inline bool SearchPathElement::_endsInPathSeparator(std::string const& s) {
		if (s.empty()) {
			return false;
		}

		return (s.at(s.size() - 1) == '/')
#ifdef _WIN32
		       || (s.at(s.size() - 1) == '\\')
#endif
		       ;
	}


/// @}

} // end of namespace util

#endif // INCLUDED_SearchPath_h_GUID_7a79b983_9d8b_4185_80ab_77146a676bdf
