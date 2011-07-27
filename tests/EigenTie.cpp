/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE EigenTie tests

// Internal Includes
#include <util/EigenTie.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <Eigen/Core>

// Standard includes
// - none

using namespace boost::unit_test;
namespace {
	void testAssign(double val) {
		Eigen::Vector3d orig(val, val, val);
		double x, y, z;
		util::TieVector(x, y, z) = orig;
		BOOST_CHECK_EQUAL(util::TieVector(x, y, z), orig);

		BOOST_CHECK_EQUAL(x, val);
		BOOST_CHECK_EQUAL(y, val);
		BOOST_CHECK_EQUAL(z, val);

		x++;
		BOOST_CHECK_NE(util::TieVector(x, y, z), orig);

	}
	void testTieTieAssign(double val) {
		Eigen::Vector3d orig(val, val, val);
		double x, y, z;
		double a, b, c;
		util::TieVector(x, y, z) = orig;
		util::TieVector(a, b, c) = util::TieVector(x, y, z);
		BOOST_CHECK_EQUAL(util::TieVector(x, y, z), util::TieVector(a, b, c));

		BOOST_CHECK_EQUAL(a, val);
		BOOST_CHECK_EQUAL(b, val);
		BOOST_CHECK_EQUAL(c, val);

		x++;
		BOOST_CHECK_NE(util::TieVector(x, y, z), util::TieVector(a, b, c));
	}
}

BOOST_AUTO_TEST_CASE(ThreeZerosAssign) {
	testAssign(0.0);
}

BOOST_AUTO_TEST_CASE(ThreeOnesAssign) {
	testAssign(1.0);
}

BOOST_AUTO_TEST_CASE(ThreeZerosTieTieAssign) {
	testAssign(0.0);
}

BOOST_AUTO_TEST_CASE(ThreeOnesTieTieAssign) {
	testAssign(1.0);
}

