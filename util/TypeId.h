/** @file
	@brief Header

	@date 2012

	@versioninfo@

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_TypeId_h_GUID_db8ba085_2a20_480f_bea4_90d9ca6a4a3c
#define INCLUDED_TypeId_h_GUID_db8ba085_2a20_480f_bea4_90d9ca6a4a3c

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/void.hpp>
#include <boost/mpl/identity.hpp>

// Standard includes
#include <typeinfo>

namespace util {
	/// @brief A simple wrapper/handle class for type_info for use in containers, etc.
	class TypeId {
		public:
			/// @brief default constructor
			TypeId() : _typeinfo(null_type_ptr()) {}

			/// @brief constructor from type_info reference (return type of typeid operator)
			TypeId(std::type_info const & ti) : _typeinfo(&ti) {}

			/// @brief Templated constructor using boost::mpl::identity as a wrapper.
			template<typename T>
			TypeId(boost::mpl::identity<T> const&) : _typeinfo(&typeid(T)) {}

			/// @brief templated static factory method - easier than nesting a typeid call.
			template<typename T>
			static TypeId create() {
				return TypeId(typeid(T));
			}

			/// @brief Some name, with no guarantee of uniqueness or usefulness.
			const char * name() const {
				if (empty()) {
					return "";
				} else {
					return get().name();
				}
			}

			bool before(std::type_info const& other) const {
				if (empty()) {
					return false;
				}
				return get().before(other);
			}

			bool before(TypeId const& other) const {
				if (empty()) {
					return false;
				}
				if (other.empty()) {
					return true;
				}
				return get().before(other.get());
			}

			std::type_info const & get() const {
				return *_typeinfo;
			}

			std::type_info const * getPointer() const {
				return _typeinfo;
			}

			bool empty() const {
				return getPointer() == null_type_ptr();
			}

			static std::type_info const * null_type_ptr() {
				return &typeid(boost::mpl::void_);
			}
		private:

			std::type_info const * _typeinfo;

	};

	inline bool operator<(TypeId const& lhs, TypeId const& rhs) {
		return lhs.before(rhs);
	}

	inline bool operator==(TypeId const& lhs, TypeId const& rhs) {
		return lhs.empty() && rhs.empty() ? true :
		       (lhs.empty() || rhs.empty() ? false : lhs.get() == rhs.get());
	}

	inline bool operator!=(TypeId const& lhs, TypeId const& rhs) {
		return lhs.empty() && rhs.empty() ? false :
		       (lhs.empty() || rhs.empty() ? true : lhs.get() != rhs.get());
	}

	inline bool operator==(std::type_info const& lhs, TypeId const& rhs) {
		return rhs.empty() ? false : lhs == rhs.get();
	}

	inline bool operator!=(std::type_info const& lhs, TypeId const& rhs) {
		return rhs.empty() ? true : lhs != rhs.get();
	}

	inline bool operator==(TypeId const& lhs, std::type_info const& rhs) {
		return lhs.empty() ? false : lhs.get() == rhs;
	}

	inline bool operator!=(TypeId const& lhs, std::type_info const& rhs) {
		return lhs.empty() ? true : lhs.get() != rhs;
	}

	template<typename StreamType>
	StreamType & operator<<(StreamType & s, TypeId const& rhs) {
		s << rhs.name();
		return s;
	}
} // end of namespace util

#endif // INCLUDED_TypeId_h_GUID_db8ba085_2a20_480f_bea4_90d9ca6a4a3c
