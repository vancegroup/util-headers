/** @file
	@brief Header

	@date 2012

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
#ifndef INCLUDED_VectorSimulator_h_GUID_3982483b_70a3_4b3a_a50a_4d948fb44655
#define INCLUDED_VectorSimulator_h_GUID_3982483b_70a3_4b3a_a50a_4d948fb44655

// Internal Includes
// - none

// Library/third-party includes
#include <boost/config.hpp>

#if !defined(UTIL_HEADERS_VECTORSIMULATOR_NO_EXCEPTIONS)
#  if defined(BOOST_NO_EXCEPTIONS) || defined(BOOST_EXCEPTION_DISABLE)
#    define UTIL_HEADERS_VECTORSIMULATOR_NO_EXCEPTIONS 1
#  endif
#endif

// Standard includes
#if !defined(UTIL_HEADERS_VECTORSIMULATOR_NO_EXCEPTIONS)
#include <stdexcept>
#endif

namespace util {

	class vector_simulator_access {
			template<typename T, typename TI>
			static bool rangecheck(T const& obj, TI index) {
				return obj.rangecheck(index);
			}
	};

	template<typename Derived, typename Value, typename SizeType = typename Derived::size_type>
	class vector_simulator {
		public:
			typedef Value value_type;
			typedef SizeType size_type;
			typedef value_type & reference;
			typedef value_type const & const_reference;

#if defined(UTIL_HEADERS_VECTORSIMULATOR_NO_EXCEPTIONS)
			reference at(std::size_t i) {
				return getDerived()[i];
			}

			const_reference at(size_type i) const {
				return getDerived()[i];
			}

#else // exception-using code
			reference at(std::size_t i) {
				if (vector_simulator_access::rangecheck(getDerived(), i)) {
					return getDerived()[i];
				} else {
					throw std::out_of_range("Out of range access in at()");
				}
			}

			const_reference at(size_type i) const {
				if (vector_simulator_access::rangecheck(getDerived(), i)) {
					return getDerived()[i];
				} else {
					throw std::out_of_range("Out of range access in constant at()");
				}
			}
#endif

			reference front() {
				return getDerived()[0];
			}

			const_reference front() const {
				return getDerived()[0];
			}

			reference back() {
				return getDerived()[getDerived().size() - 1];
			}

			const_reference back() const {
				return getDerived()[getDerived().size() - 1];
			}
		private:
			Derived & getDerived() {
				return *static_cast<Derived*>(this);
			}
			Derived const & getDerived() const {
				return *static_cast<Derived const *>(this);
			}

	};


} // end of namespace util

#endif // INCLUDED_VectorSimulator_h_GUID_3982483b_70a3_4b3a_a50a_4d948fb44655
