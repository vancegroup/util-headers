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

	namespace {
		inline std::bitset<3> constructBitset(bool bit0, bool bit1, bool bit2) {
			return (std::bitset<3>(bit0)) | (std::bitset<3>(bit1) << 1) | (std::bitset<3>(bit2) << 2);
		}

		inline std::bitset<3> bitsetInsert(std::bitset<2> const & input, bool val, size_t location) {
			switch (location) {
				case 0:
					return constructBitset(val, input[0], input[1]);
					break;

				case 1:
					return constructBitset(input[0], val, input[1]);
					break;

				case 2:
					return constructBitset(input[0], input[1], val);
					break;

				default:
					throw std::out_of_range("Location to insert bit is out of range!");
			}
		}
	} // end of unnamed namespace

	template<typename _VecType = Eigen::Vector3d>
	struct Cube {
			typedef unsigned char BitIDType;
			typedef unsigned char IDType;
			typedef bool BitValueType;
			typedef _VecType VectorType;

			class Vertex;
			class Face;
			class FaceVertex;



			class Vertex {
				public:
					typedef Cube CubeType;
					typedef std::bitset<3> BitsetType;
					static const IDType COUNT = 8;

					Vertex() {}
					explicit Vertex(BitsetType const& val)
						: _v(val)
					{}

					explicit Vertex(IDType val)
						: _v(val) {
						if (val >= COUNT) {
							throw std::out_of_range("Vertex index specified is out of range  {0, 1, ... 7} !");
						}
					}

					VectorType get() const {
						return VectorType(_v[0], _v[1], _v[2]) * 2 - VectorType::Constant(1);
					}

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
					static const IDType COUNT = 6;
					Face()
						: _fixedBit(0)
						, _bitval(false)
					{}

					explicit Face(IDType j)
						: _fixedBit(j % 3)
						, _bitval(j / 3) {
						if (j >= COUNT) {
							throw std::out_of_range("Face index specified is out of range {0, 1, ... 5} !");
						}
					}

					Face(BitIDType fixedBit, BitValueType bitval)
						: _fixedBit(fixedBit)
						, _bitval(bitval) {
						if (fixedBit >= 3) {
							throw std::out_of_range("Face fixed bit index specified is out of range {0, 1, 2} !");
						}
					}

					VectorType getCenter() const {
						return VectorType(_fixedBit == 0 ? _bitval * 2 - 1 : 0,
						                  _fixedBit == 1 ? _bitval * 2 - 1 : 0,
						                  _fixedBit == 2 ? _bitval * 2 - 1 : 0);
					}

					VectorType getNormal() const {
						return getCenter(); /// @todo center same as normal for centered 2x2x2 cube?
					}

					BitIDType getFixedBitIndex() const {
						return _fixedBit;
					}

					BitValueType getFixedBitValue() const {
						return _bitval;
					}

					IDType getID() const {
						return _bitval * 3 + _fixedBit;
					}

				private:
					BitIDType _fixedBit;
					BitValueType _bitval;
			};

			class FaceVertex {
				public:
					typedef std::bitset<2> BitsetType;

					static const IDType COUNT = 4;
					FaceVertex(Face const& f, IDType k)
						: _fixedBit(f.getFixedBitIndex())
						, _bitval(f.getFixedBitValue())
						, _vertexID(k) {
						if (k >= COUNT) {
							throw std::out_of_range("Face vertex index specified is out of range {0, 1, 2, 3} !");
						}
					}

					Face getFace() const {
						return Face(_fixedBit, _bitval);
					}

					IDType getID() const {
						return _vertexID;
					}

					FaceVertex getNeighbor(IDType n) const {
						if (n >= 2) {
							throw std::out_of_range("Face vertex neighbor index specified is out of range {0, 1} !");
						}
						return FaceVertex(getFace(), BitsetType(_vertexID).flip(n).to_ulong());
					}

					operator Vertex() const {
						return Vertex(bitsetInsert(BitsetType(_vertexID), _bitval, _fixedBit));
					}
				private:
					BitIDType _fixedBit;
					BitValueType _bitval;
					IDType _vertexID;
			};
			struct FaceEdge;
			struct Edge;
	};

} // end of namespace util

#endif // INCLUDED_CubeComponents_h_GUID_eea925df_f01f_4e08_b4db_e9c2800b49a6
