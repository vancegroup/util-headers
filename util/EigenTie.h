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
#ifndef INCLUDED_EigenTie_h_GUID_6c867047_6869_440c_8724_0d7733c6c7cd
#define INCLUDED_EigenTie_h_GUID_6c867047_6869_440c_8724_0d7733c6c7cd

// Internal Includes
// - none

// Library/third-party includes
#include <Eigen/Core>

// Standard includes
// - none

namespace util {

/// @addtogroup Math Math Utilities
/// @{
	namespace detail {
		template<int _Dim, typename _Scalar>
		class TieVector;

		template<int _Dim, typename _Scalar1, typename _Scalar2>
		bool operator==(TieVector<_Dim, _Scalar1> const& lhs, TieVector<_Dim, _Scalar2> const& rhs);

		template<int _Dim = 3, typename _Scalar = double>
		class TieVector {
			public:
				typedef _Scalar Scalar;
				enum {
					Dim = _Dim
				};
				typedef Eigen::Matrix<_Scalar, _Dim, 1> Base;
			private:
				Scalar * _data[Dim];

				template<typename OtherDerived>
				EIGEN_STRONG_INLINE TieVector & _set(::Eigen::MatrixBase<OtherDerived> const& other) {
					EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE(OtherDerived, int(Dim));
					if (*this == other) {
						return *this;
					}
					for (int i = 0; i < Dim; ++i) {
						*(_data[i]) = other[i];
					}
					return *this;
				}

			public:
#define EIGEN_TIE_STATIC_ASSERT_DIMENSION(_NUMARGS) assert(Dim == _NUMARGS && "YOU_DID_NOT_PASS_THE_CORRECT_AMOUNT_OF_ARGUMENTS_TO_TIE_TOGETHER")
//#define EIGEN_TIE_STATIC_ASSERT_DIMENSION(_NUMARGS) EIGEN_STATIC_ASSERT( (int(Dim) == int(_NUMARGS)), YOU_DID_NOT_PASS_THE_CORRECT_AMOUNT_OF_ARGUMENTS_TO_TIE_TOGETHER)
#define EIGEN_TIE_INITIALIZE_ELEMENT(_ELT) _data[_ELT] = &x ## _ELT

				TieVector(Scalar & x0) {
					EIGEN_TIE_STATIC_ASSERT_DIMENSION(1);
					EIGEN_TIE_INITIALIZE_ELEMENT(0);
				}

				TieVector(Scalar & x0, Scalar & x1) {
					EIGEN_TIE_STATIC_ASSERT_DIMENSION(2);
					EIGEN_TIE_INITIALIZE_ELEMENT(0);
					EIGEN_TIE_INITIALIZE_ELEMENT(1);
				}

				TieVector(Scalar & x0, Scalar & x1, Scalar & x2) {
					EIGEN_TIE_STATIC_ASSERT_DIMENSION(3);
					EIGEN_TIE_INITIALIZE_ELEMENT(0);
					EIGEN_TIE_INITIALIZE_ELEMENT(1);
					EIGEN_TIE_INITIALIZE_ELEMENT(2);
				}

				TieVector(Scalar & x0, Scalar & x1, Scalar & x2, Scalar & x3) {
					EIGEN_TIE_STATIC_ASSERT_DIMENSION(4);
					EIGEN_TIE_INITIALIZE_ELEMENT(0);
					EIGEN_TIE_INITIALIZE_ELEMENT(1);
					EIGEN_TIE_INITIALIZE_ELEMENT(2);
					EIGEN_TIE_INITIALIZE_ELEMENT(3);
				}

#undef EIGEN_TIE_INITIALIZE_ELEMENT
#undef EIGEN_TIE_STATIC_ASSERT_DIMENSION
				EIGEN_STRONG_INLINE TieVector& operator=(const TieVector& other) {
					if (*this == other) {
						return *this;
					}
					for (int i = 0; i < Dim; ++i) {
						*(_data[i]) = *(other._data[i]);
					}
					return *this;
				}

				template<typename OtherDerived>
				EIGEN_STRONG_INLINE TieVector & operator=(const ::Eigen::MatrixBase <OtherDerived>& other) {
					return _set(other);
				}

				EIGEN_STRONG_INLINE Base convert() const {
					Base temp;
					for (int i = 0; i < Dim; ++i) {
						temp[i] = *(_data[i]);
					}
					return temp;
				}

				EIGEN_STRONG_INLINE operator Base() const {
					return convert();
				}

				EIGEN_STRONG_INLINE Scalar coeff(int i) const {
					return *(_data[i]);
				}
		};

		template<typename StreamType, int _Dim, typename _Scalar>
		EIGEN_STRONG_INLINE StreamType & operator<<(StreamType & os, TieVector<_Dim, _Scalar> const& val) {
			os << val.convert();
			return os;
		}

		template<int _Dim, typename _Scalar1, typename _Scalar2>
		EIGEN_STRONG_INLINE bool operator==(TieVector<_Dim, _Scalar1> const& lhs, TieVector<_Dim, _Scalar2> const& rhs) {
			for (int i = 0; i < _Dim; ++i) {
				if (lhs.coeff(i) != rhs.coeff(i)) {
					return false;
				}
			}
			return true;
		}

		template<int _Dim, typename _Scalar, typename Derived>
		EIGEN_STRONG_INLINE bool operator==(TieVector<_Dim, _Scalar> const& tieVal, ::Eigen::MatrixBase<Derived> const& other) {
			return tieVal.convert() == other;
		}

		template<int _Dim, typename _Scalar, typename Derived>
		EIGEN_STRONG_INLINE bool operator==(::Eigen::MatrixBase<Derived> const& other, TieVector<_Dim, _Scalar> const& tieVal) {
			return tieVal.convert() == other;
		}

		template<int _Dim, typename _Scalar1, typename _Scalar2>
		EIGEN_STRONG_INLINE bool operator!=(TieVector<_Dim, _Scalar1> const& lhs, TieVector<_Dim, _Scalar2> const& rhs) {
			return !(lhs == rhs);
		}

		template<int _Dim, typename _Scalar, typename Derived>
		EIGEN_STRONG_INLINE bool operator!=(TieVector<_Dim, _Scalar> const& tieVal, ::Eigen::MatrixBase<Derived> const& other) {
			return !(tieVal == other);
		}

		template<int _Dim, typename _Scalar, typename Derived>
		EIGEN_STRONG_INLINE bool operator!=(::Eigen::MatrixBase<Derived> const& other, TieVector<_Dim, _Scalar> const& tieVal) {
			return !(tieVal == other);
		}

	} // end of namespace detail

#define EIGEN_TIE_DEFINE_CREATION_FUNCTION( _DIM, _ARGS, _ARGNAMES) \
	template<typename Scalar> \
	EIGEN_STRONG_INLINE detail::TieVector<_DIM, Scalar> TieVector _ARGS { \
		return detail::TieVector<_DIM, Scalar> _ARGNAMES ; \
	} \
 
	EIGEN_TIE_DEFINE_CREATION_FUNCTION(1,
	                                   (Scalar & x0),
	                                   (x0)
	                                  )

	EIGEN_TIE_DEFINE_CREATION_FUNCTION(2,
	                                   (Scalar & x0, Scalar & x1),
	                                   (x0, x1)
	                                  )

	EIGEN_TIE_DEFINE_CREATION_FUNCTION(3,
	                                   (Scalar & x0, Scalar & x1, Scalar & x2),
	                                   (x0, x1, x2)
	                                  )

	EIGEN_TIE_DEFINE_CREATION_FUNCTION(4,
	                                   (Scalar & x0, Scalar & x1, Scalar & x2, Scalar & x3),
	                                   (x0, x1, x2, x3)
	                                  )

#undef EIGEN_TIE_DEFINE_CREATION_FUNCTION
/// @}

} // end of namespace util

#endif // INCLUDED_EigenTie_h_GUID_6c867047_6869_440c_8724_0d7733c6c7cd
