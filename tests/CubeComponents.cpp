/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE CubeComponents

// Internal Includes
#include <util/CubeComponents.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;

typedef util::Cube<> Cube;
static const int CUBE_CORNER_COUNT = 8;

BOOST_AUTO_TEST_CASE(VertexConstructionDefault) {
	BOOST_CHECK_NO_THROW(Cube::Vertex());
}

BOOST_AUTO_TEST_CASE(VertexConstructionBitset) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Vertex(std::bitset<3>(i)));
	}
}

BOOST_AUTO_TEST_CASE(VertexConstructionInt) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Vertex(Cube::Vertex::IDType(i)));
	}
	for (unsigned int i = CUBE_CORNER_COUNT; i < 10; ++i) {
		BOOST_CHECK_THROW(Cube::Vertex(Cube::Vertex::IDType(i)), std::out_of_range);
	}
}

BOOST_AUTO_TEST_CASE(VertexUniqueGeneration) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Vertex(Cube::Vertex::BitsetType(i)));
	}
}
