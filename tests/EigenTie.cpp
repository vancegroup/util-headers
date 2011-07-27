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
		util::Tie<3, double>(x, y, z) = orig;
		BOOST_CHECK_EQUAL(util::Tie(x, y, z), orig);
	
		BOOST_CHECK_EQUAL(x, val);
		BOOST_CHECK_EQUAL(y, val);
		BOOST_CHECK_EQUAL(z, val);
	}
}

BOOST_AUTO_TEST_CASE(ThreeZerosAssign) {
	testAssign(0.0);
}

BOOST_AUTO_TEST_CASE(ThreeOnesAssign) {
	testAssign(1.0);
}

