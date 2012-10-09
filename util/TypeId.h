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
			/// @brief default constructor - initializes to typeinfo of boost::mpl::void_
			TypeId() : _typeinfo(&null_type()) {}

			/// @brief constructor from type_info reference (return type of typeid operator)
			TypeId(std::type_info const & ti) : _typeinfo(&ti) {}

			/// @brief Templated constructor
			template<typename T>
			TypeId() : _typeinfo(&typeid(T)) {}

			/// @brief Templated constructor using boost::mpl::identity as a wrapper.
			template<typename T>
			TypeId(boost::mpl::identity<T> const&) : _typeinfo(&typeid(T)) {}

			/// @brief Some name, with no guarantee of uniqueness or usefulness.
			const char * name() const {
				return get().name();
			}

			bool before(std::type_info const& other) const {
				return get().before(other);
			}

			bool before(TypeId const& other) const {
				return get().before(other.get());
			}

			std::type_info const & get() const {
				return *_typeinfo;
			}

			bool empty() const {
				return get() == null_type();
			}

			static std::type_info const & null_type() {
				return typeid(boost::mpl::void_);
			}
		private:

			std::type_info const * _typeinfo;

	};

	inline bool operator<(TypeId const& lhs, TypeId const& rhs) {
		return lhs.before(rhs);
	}

	inline bool operator==(TypeId const& lhs, TypeId const& rhs) {
		return lhs.get() == rhs.get();
	}

	inline bool operator!=(TypeId const& lhs, TypeId const& rhs) {
		return lhs.get() != rhs.get();
	}

	inline bool operator==(std::type_info const& lhs, TypeId const& rhs) {
		return lhs == rhs.get();
	}

	inline bool operator!=(std::type_info const& lhs, TypeId const& rhs) {
		return lhs != rhs.get();
	}

	inline bool operator==(TypeId const& lhs, std::type_info const& rhs) {
		return lhs.get() == rhs;
	}

	inline bool operator!=(TypeId const& lhs, std::type_info const& rhs) {
		return lhs.get() != rhs;
	}
} // end of namespace util

#endif // INCLUDED_TypeId_h_GUID_db8ba085_2a20_480f_bea4_90d9ca6a4a3c
