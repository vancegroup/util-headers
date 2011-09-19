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
#ifndef INCLUDED_CubeComponents_h_GUID_eea925df_f01f_4e08_b4db_e9c2800b49a6
#define INCLUDED_CubeComponents_h_GUID_eea925df_f01f_4e08_b4db_e9c2800b49a6

// Internal Includes
// - none

// Library/third-party includes
#include <Eigen/Core>

// Standard includes
#include <bitset>
#include <cassert>
#include <stdexcept>

namespace util {


	template<typename _VecType = Eigen::Vector3d>
	struct Cube {
			typedef unsigned char BitIDType;
			typedef bool BitValueType;
			typedef _VecType VectorType;

			class Vertex {
				public:
					typedef Cube CubeType;
					typedef std::bitset<3> BitsetType;
					typedef unsigned char IDType;
					static const IDType COUNT = 8;

					Vertex() {}
					Vertex(BitsetType const& val)
						: _v(val)
					{}

					Vertex(IDType val)
						: _v(val) {
						if (val >= COUNT) {
							throw std::out_of_range("Vertex index specified is out of range!");
						}
					}

					VectorType get() const;

					IDType getID() const {
						return _v.to_ulong();
					}

					BitsetType const& getBitset() const {
						return _v;
					}

					Vertex getNeighbor(IDType m) {
						assert(m < 3);
						return Vertex(BitsetType(_v).flip(m));
					}

					bool operator==(Vertex const& other) const {
						return _v == other._v;
					}

					bool operator!=(Vertex const& other) const {
						return _v != other._v;
					}

				private:
					BitsetType _v;
			};

			class Face {
				public:

				private:
					BitIDType _fixedBit;
					BitValueType _bitval;
			};

			class FaceVertex {
				public:
					operator Vertex() const;
				private:
			};
			struct FaceEdge;
			struct Edge;
	};

	template<typename _VecType>
	inline _VecType Cube<_VecType>::Vertex::get() const {
		return _VecType(_v[0], _v[1], _v[2]) * 2 - _VecType::Constant(1);
	}

} // end of namespace util

#endif // INCLUDED_CubeComponents_h_GUID_eea925df_f01f_4e08_b4db_e9c2800b49a6
