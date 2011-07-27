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
	template<int _Dim, typename _Scalar>
	class Tie;

	template<int _Dim, typename _Scalar1, typename _Scalar2>
	bool operator==(Tie<_Dim, _Scalar1> const& lhs, Tie<_Dim, _Scalar2> const& rhs);

	template<int _Dim = 3, typename _Scalar = double>
	class Tie {
		public:
			typedef _Scalar Scalar;
			enum {
				Dim = _Dim
			};
			typedef Eigen::Matrix<_Scalar, _Dim, 1> Base;
		private:
			Scalar * _data[Dim];

			template<typename OtherDerived>
			Tie & _set(::Eigen::MatrixBase<OtherDerived> const& other) {
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

			Tie(Scalar & x0, Scalar & x1, Scalar & x2) {
				EIGEN_TIE_STATIC_ASSERT_DIMENSION(3);
				EIGEN_TIE_INITIALIZE_ELEMENT(0);
				EIGEN_TIE_INITIALIZE_ELEMENT(1);
				EIGEN_TIE_INITIALIZE_ELEMENT(2);
			}

			Tie(Scalar & x0, Scalar & x1, Scalar & x2, Scalar & x3) {
				EIGEN_TIE_STATIC_ASSERT_DIMENSION(4);
				EIGEN_TIE_INITIALIZE_ELEMENT(0);
				EIGEN_TIE_INITIALIZE_ELEMENT(1);
				EIGEN_TIE_INITIALIZE_ELEMENT(2);
				EIGEN_TIE_INITIALIZE_ELEMENT(3);
			}

#undef EIGEN_TIE_INITIALIZE_ELEMENT
#undef EIGEN_TIE_STATIC_ASSERT_DIMENSION
			EIGEN_STRONG_INLINE Tie& operator=(const Tie& other) {
				if (*this == other) {
					return *this;
				}
				for (int i = 0; i < Dim; ++i) {
					*(_data[i]) = *(other._data[i]);
				}
				return *this;
			}

			template<typename OtherDerived>
			EIGEN_STRONG_INLINE Tie & operator=(const ::Eigen::MatrixBase <OtherDerived>& other) {
				return _set(other);
			}

			Base convert() const {
				Base temp;
				for (int i = 0; i < Dim; ++i) {
					temp[i] = *(_data[i]);
				}
				return temp;
			}

			operator Base() const {
				return convert();
			}

			Scalar coeff(int i) const {
				return *(_data[i]);
			}
	};

	template<typename StreamType, int _Dim, typename _Scalar>
	StreamType & operator<<(StreamType & os, Tie<_Dim, _Scalar> const& val) {
		os << val.convert();
		return os;
	}

	template<int _Dim, typename _Scalar1, typename _Scalar2>
	inline bool operator==(Tie<_Dim, _Scalar1> const& lhs, Tie<_Dim, _Scalar2> const& rhs) {
		for (int i = 0; i < _Dim; ++i) {
			if (lhs.coeff(i) != rhs.coeff(i)) {
				return false;
			}
		}
		return true;
	}

	template<int _Dim, typename _Scalar, typename Derived>
	inline bool operator==(Tie<_Dim, _Scalar> const& tieVal, ::Eigen::MatrixBase<Derived> const& other) {
		return tieVal.convert() == other;
	}

	template<int _Dim, typename _Scalar, typename Derived>
	inline bool operator==(::Eigen::MatrixBase<Derived> const& other, Tie<_Dim, _Scalar> const& tieVal) {
		return tieVal.convert() == other;
	}

	template<int _Dim, typename _Scalar1, typename _Scalar2>
	inline bool operator!=(Tie<_Dim, _Scalar1> const& lhs, Tie<_Dim, _Scalar2> const& rhs) {
		return !(lhs == rhs);
	}

	template<int _Dim, typename _Scalar, typename Derived>
	inline bool operator!=(Tie<_Dim, _Scalar> const& tieVal, ::Eigen::MatrixBase<Derived> const& other) {
		return !(tieVal == other);
	}

	template<int _Dim, typename _Scalar, typename Derived>
	inline bool operator!=(::Eigen::MatrixBase<Derived> const& other, Tie<_Dim, _Scalar> const& tieVal) {
		return !(tieVal == other);
	}

	template<typename Scalar>
	inline Tie<3, Scalar> TieVector(Scalar & x0, Scalar & x1, Scalar & x2) {
		return Tie<3, Scalar>(x0, x1, x2);
	}
/// @}

} // end of namespace util

#endif // INCLUDED_EigenTie_h_GUID_6c867047_6869_440c_8724_0d7733c6c7cd
