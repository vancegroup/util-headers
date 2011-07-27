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

	template<int _Dim, typename _Scalar>
	class Tie;
}

namespace Eigen {
	namespace internal {
		template<typename Derived>
		struct traits;

		template<int _Dim, typename _Scalar>
		struct traits<util::Tie<_Dim, _Scalar> > {
			typedef _Scalar Scalar;
//			typedef Dense StorageKind;
//			typedef DenseIndex Index;
			//typedef MatrixXpr XprKind;
			enum {
				RowsAtCompileTime = _Dim,
				ColsAtCompileTime = 1,
				MaxRowsAtCompileTime = _Dim,
				MaxColsAtCompileTime = 1,
				Flags = 0, // no valid flags
				CoeffReadCost = NumTraits<Scalar>::ReadCost,
				Options = DontAlign,
//				InnerStrideAtCompileTime = 1,
//				OuterStrideAtCompileTime = (Options&RowMajor) ? ColsAtCompileTime : RowsAtCompileTime
			};
		};
	}
}
namespace util {

/// @addtogroup Math Math Utilities
/// @{

	template<int _Dim = 3, typename _Scalar = double>
	class Tie : public ::Eigen::MatrixBase<Tie<_Dim, _Scalar> > {
		public:
			typedef _Scalar Scalar;
			enum {
				Dim = _Dim
			};
			typedef Eigen::Matrix<_Scalar, _Dim, 1> Base;
		private:
			Scalar _dummy0;
			Scalar _dummy1;
			Scalar _dummy2;
			Scalar & _0;
			Scalar & _1;
			Scalar & _2;
			template<typename OtherDerived>
			Tie & _set(::Eigen::EigenBase<OtherDerived> const& other) {
				if (*this == other) {
					return *this;
				}
				if (_Dim > 0) {
					_0 = other[0];
				}
				
				if (_Dim > 1) {
					_1 = other[1];
				}
				
				if (_Dim > 2) {
					_2 = other[2];
				}
				return *this;
			}
		public:
			Tie(Scalar & x0, Scalar & x1, Scalar & x2)
				: _0(x0)
				, _1(x1) 
				, _2(x2)
			{
				assert(Dim == 3);
			}
			
			EIGEN_STRONG_INLINE Tie& operator=(const Tie& other)
			{
			  return Base::_set(other);
			}
			
			template<typename OtherDerived>
			EIGEN_STRONG_INLINE Tie & operator=(const ::Eigen::MatrixBase <OtherDerived>& other)
			{
				return _set(other);
			}
			
			Base operator Base() const
			{
				return Base(_0, _1, _2);
			}
	};

	template<typename Scalar>
	Tie<3, Scalar> TieVector(Scalar & x0, Scalar & x1, Scalar & x2) {
		return Tie<3, Scalar>(x0, x1, x2);
	}
/// @}

} // end of namespace util

#endif // INCLUDED_EigenTie_h_GUID_6c867047_6869_440c_8724_0d7733c6c7cd
