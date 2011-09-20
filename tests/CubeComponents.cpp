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
static const int CUBE_FACE_COUNT = 6;

BOOST_AUTO_TEST_CASE(VertexConstructionDefault) {
	BOOST_CHECK_NO_THROW(Cube::Vertex());
}

BOOST_AUTO_TEST_CASE(VertexConstructionBitset) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Vertex(Cube::Vertex::BitsetType(i)));
	}
}

BOOST_AUTO_TEST_CASE(VertexConstructionInt) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Vertex(Cube::IDType(i)));
	}
	for (unsigned int i = CUBE_CORNER_COUNT; i < 10; ++i) {
		BOOST_CHECK_THROW(Cube::Vertex(Cube::IDType(i)), std::out_of_range);
	}
}

BOOST_AUTO_TEST_CASE(VertexUniqueGeneration) {
	for (unsigned int i = 0; i < CUBE_CORNER_COUNT; ++i) {
		for (unsigned int j = 0; j < CUBE_CORNER_COUNT; ++j) {
			if (i == j) {
				BOOST_CHECK_EQUAL(Cube::Vertex(Cube::IDType(i)), Cube::Vertex(Cube::IDType(j)));
				BOOST_CHECK_EQUAL(Cube::Vertex(Cube::IDType(i)).get(), Cube::Vertex(Cube::IDType(j)).get());
			} else {
				BOOST_CHECK_NE(Cube::Vertex(Cube::IDType(i)), Cube::Vertex(Cube::IDType(j)));
				BOOST_CHECK_NE(Cube::Vertex(Cube::IDType(i)).get(), Cube::Vertex(Cube::IDType(j)).get());
			}
		}
	}
}

BOOST_AUTO_TEST_CASE(FaceConstructionDefault) {
	BOOST_CHECK_NO_THROW(Cube::Face());
}

BOOST_AUTO_TEST_CASE(FaceConstructionInt) {
	for (unsigned int i = 0; i < CUBE_FACE_COUNT; ++i) {
		BOOST_CHECK_NO_THROW(Cube::Face(Cube::IDType(i)));
	}
	for (unsigned int i = CUBE_FACE_COUNT; i < 10; ++i) {
		BOOST_CHECK_THROW(Cube::Face(Cube::IDType(i)), std::out_of_range);
	}
}

BOOST_AUTO_TEST_CASE(FaceIdentity) {
	for (unsigned int i = 0; i < CUBE_FACE_COUNT; ++i) {
		BOOST_CHECK_EQUAL(Cube::Face(Cube::IDType(i)).getID(), i);
	}
}

BOOST_AUTO_TEST_CASE(FaceVertexAccess) {
	for (unsigned int i = 0; i < CUBE_FACE_COUNT; ++i) {
		Cube::Face face = Cube::Face(Cube::IDType(i));
		BOOST_CHECK_NO_THROW(face.getCenter());
		for (unsigned int k = 0; k < 4; ++k) {
			BOOST_CHECK_NO_THROW(face.getFaceVertex(k));
			for (unsigned int k2 = 0; k2 < 4; ++k2) {
				if (k == k2) {
					BOOST_CHECK_EQUAL(face.getFaceVertex(k).getCubeVertex(), face.getFaceVertex(k2).getCubeVertex());
				} else {
					BOOST_CHECK_NE(face.getFaceVertex(k).getCubeVertex(), face.getFaceVertex(k2).getCubeVertex());
				}
			}
		}

		for (unsigned int k = 4; k < 6; ++k) {
			BOOST_CHECK_THROW(face.getFaceVertex(k), std::out_of_range);
		}
	}
}


BOOST_AUTO_TEST_CASE(FaceVertexIdentity) {
	for (unsigned int i = 0; i < CUBE_FACE_COUNT; ++i) {
		Cube::Face face = Cube::Face(Cube::IDType(i));
		for (unsigned int k = 0; k < 4; ++k) {
			BOOST_CHECK_EQUAL(face.getFaceVertex(k).getFace(), face);
			BOOST_CHECK_EQUAL(face.getFaceVertex(k).getID(), k);
		}
	}
}
