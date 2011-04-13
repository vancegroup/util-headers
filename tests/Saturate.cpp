/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Saturate tests

// Internal Includes
#include <util/Saturate.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Standard includes
#include <math.h>


using namespace boost::unit_test;

//Run tests with this:
//"C:/Program Files (x86)/CMake 2.8/bin/ctest.exe" -C RelWithDebInfo -R util -V


//Zeros tests---------------------------------------------
BOOST_AUTO_TEST_CASE(TwoParamNoSaturateZeros) {
	Eigen::Vector3d orig(0.0, 0.0, 0.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(ThreeParamNoSaturateZeros) {
	Eigen::Vector3d orig(0.0, 0.0, 0.0);
	Eigen::Vector3d othervec(0.0, 0.0, 0.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK_EQUAL(orig, othervec);
	BOOST_CHECK(result == false);
}
//-------------------------------------------------


//One dimensional tests----------------------------------
BOOST_AUTO_TEST_CASE(TwoParam1DNoSaturate) {
	Eigen::Vector3d orig(0.0, 0.0, 1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(TwoParam1DNoSaturateNeg) {
	Eigen::Vector3d orig(0.0, 0.0, -1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(TwoParam1DSaturate) {
	Eigen::Vector3d orig(0.0, 0.0, 3.0);
	Eigen::Vector3d expected(0.0, 0.0, 2.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 2.0;
	bool result = util::saturate(vec, mxMagnitude);

	BOOST_CHECK_EQUAL(expected, vec);
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(TwoParam1DSaturateNeg) {
	Eigen::Vector3d orig(0.0, 0.0, -3.0);
	Eigen::Vector3d expected(0.0, 0.0, -2.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 2.0;
	bool result = util::saturate(vec, mxMagnitude);

	BOOST_CHECK_EQUAL(expected, vec);
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(ThreeParam1DNoSaturate) {
	Eigen::Vector3d orig(0.0, 0.0, 1.0);
	Eigen::Vector3d othervec(0.0, 0.0, 1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK_EQUAL(orig, othervec);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(ThreeParam1DNoSaturateNeg) {
	Eigen::Vector3d orig(0.0, 0.0, -1.0);
	Eigen::Vector3d othervec(0.0, 0.0, -1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	BOOST_CHECK_EQUAL(orig, vec);
	BOOST_CHECK_EQUAL(orig, othervec);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(ThreeParam1DSaturate) {
	Eigen::Vector3d orig(0.0, 0.0, 3.0);
	Eigen::Vector3d othervec(0.0, 0.0, 3.0);
	Eigen::Vector3d expected(0.0, 0.0, 2.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 2.0;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	BOOST_CHECK_EQUAL(expected, vec);
	BOOST_CHECK_EQUAL(expected, othervec);
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(ThreeParam1DSaturateNeg) {
	Eigen::Vector3d orig(0.0, 0.0, -3.0);
	Eigen::Vector3d othervec(0.0, 0.0, -3.0);
	Eigen::Vector3d expected(0.0, 0.0, -2.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 2.0;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	BOOST_CHECK_EQUAL(expected, vec);
	BOOST_CHECK_EQUAL(expected, othervec);
	BOOST_CHECK(result == true);
}
//------------------------------------------------------------------

//Three dimensional tests----------------------------------------------
BOOST_AUTO_TEST_CASE(TwoParam3DNoSaturate) {
	Eigen::Vector3d orig(1.0, 1.0, 1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(orig[i], vec[i], 0.0001);
	}
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(TwoParam3DNoSaturateNeg) {
	Eigen::Vector3d orig(-1.0, -1.0, -1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = 5.0;
	bool result = util::saturate(vec, mxMagnitude);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(orig[i], vec[i], 0.0001);
	}
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(TwoParam3DSaturate) {
	Eigen::Vector3d orig(4.0, 4.0, 4.0);
	Eigen::Vector3d expected(3.0, 3.0, 3.0);

	Eigen::Vector3d vec = orig;
	double mxMagnitude = sqrt(3.0 * 3.0 + 3.0 * 3.0 + 3.0 * 3.0);
	bool result = util::saturate(vec, mxMagnitude);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(expected[i], vec[i], 0.0001);
	}
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(TwoParam3DSaturateNeg) {
	Eigen::Vector3d orig(-4.0, -4.0, -4.0);
	Eigen::Vector3d expected(-3.0, -3.0, -3.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = sqrt(-3.0 * -3.0 + -3.0 * -3.0 + -3.0 * -3.0);
	bool result = util::saturate(vec, mxMagnitude);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(expected[i], vec[i], 0.0001);
	}
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(ThreeParam3DNoSaturate) {
	Eigen::Vector3d orig(1.0, 1.0, 1.0);
	Eigen::Vector3d othervec(1.0, 1.0, 1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = sqrt(1.0 * 1.0 + 1.0 * 1.0 + 1.0 * 1.0);
	bool result = util::saturate(vec, mxMagnitude, othervec);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(orig[i], vec[i], 0.0001);
		BOOST_CHECK_CLOSE(orig[i], othervec[i], 0.0001);
	}
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(ThreeParam3DNoSaturateNeg) {
	Eigen::Vector3d orig(-1.0, -1.0, -1.0);
	Eigen::Vector3d othervec(-1.0, -1.0, -1.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = sqrt(-1.0 * -1.0 + -1.0 * -1.0 + -1.0 * -1.0);
	bool result = util::saturate(vec, mxMagnitude, othervec);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(orig[i], vec[i], 0.0001);
		BOOST_CHECK_CLOSE(orig[i], othervec[i], 0.0001);
	}
	BOOST_CHECK(result == false);
}



BOOST_AUTO_TEST_CASE(ThreeParam3DSaturate) {
	Eigen::Vector3d orig(4.0, 4.0, 4.0);
	Eigen::Vector3d othervec(4.0, 4.0, 4.0);
	double exp_result = sqrt(3.0 * 3.0 + 3.0 * 3.0 + 3.0 * 3.0);
	Eigen::Vector3d expected(3.0, 3.0, 3.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = exp_result;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(expected[i], vec[i], 0.0001);
		BOOST_CHECK_CLOSE(expected[i], othervec[i], 0.0001);
	}
	BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(ThreeParam3DSaturateNeg) {
	Eigen::Vector3d orig(-4.0, -4.0, -4.0);
	Eigen::Vector3d othervec(-4.0, -4.0, -4.0);
	double exp_result = sqrt(-3.0 * -3.0 + -3.0 * -3.0 + -3.0 * -3.0);
	Eigen::Vector3d expected(-3.0, -3.0, -3.0);
	Eigen::Vector3d vec = orig;
	double mxMagnitude = exp_result;
	bool result = util::saturate(vec, mxMagnitude, othervec);

	for (unsigned int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE(expected[i], vec[i], 0.0001);
		BOOST_CHECK_CLOSE(expected[i], othervec[i], 0.0001);
	}
	BOOST_CHECK(result == true);
}
//--------------------------------------------------------------------
