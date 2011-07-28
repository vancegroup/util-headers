/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE EigenTie tests

#define UTIL_EIGEN_TIE_UNIQUE_ASSIGN_EXCEPTION
#ifdef NDEBUG
#	undef NDEBUG
#endif

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
		BOOST_REQUIRE_NO_THROW(util::TieVector(x, y, z) = orig);
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
		BOOST_REQUIRE_NO_THROW(util::TieVector(x, y, z) = orig);
		BOOST_REQUIRE_NO_THROW(util::TieVector(a, b, c) = util::TieVector(x, y, z));
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
	testTieTieAssign(0.0);
}

BOOST_AUTO_TEST_CASE(ThreeOnesTieTieAssign) {
	testTieTieAssign(1.0);
}

BOOST_AUTO_TEST_CASE(ThrowsTwoNotUnique) {
	Eigen::Vector3d orig(0, 0, 0);
	double x, y;
	BOOST_CHECK_THROW(util::TieVector(x, x, y) = orig, std::logic_error);

	BOOST_CHECK_THROW(util::TieVector(x)(x)(y) = orig, std::logic_error);
}
BOOST_AUTO_TEST_CASE(ThrowsThreeNotUnique) {
	Eigen::Vector3d orig(0, 0, 0);
	double x;
	BOOST_CHECK_THROW(util::TieVector(x, x, x) = orig, std::logic_error);

	BOOST_CHECK_THROW(util::TieVector(x)(x)(x) = orig, std::logic_error);
}

