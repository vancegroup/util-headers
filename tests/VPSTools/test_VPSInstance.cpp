/** @file	test_VPSInstance.cpp
	@version 1.0.0
	@brief	VPSInstance test driver

	@date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE VPSInstance basic tests

// Internal Includes
#include <VPSTools/VPSInstance.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/shared_ptr.hpp>

using namespace boost::unit_test;
using namespace VPSTools;

BOOST_AUTO_TEST_CASE(ExplicitConstruction) {
	VPSInstance::get();
	BOOST_CHECK(VPSInstance::get());
}

BOOST_AUTO_TEST_CASE(ImplicitConstruction) {
	BOOST_CHECK(VPSInstance::get());
}

BOOST_AUTO_TEST_CASE(IdenticalSingletons) {
	Vps* vps1;
	Vps* vps2;
	BOOST_REQUIRE( (vps1 = VPSInstance::get()) );
	BOOST_REQUIRE( (vps2 = VPSInstance::get()) );
	BOOST_CHECK_EQUAL(vps1, vps2);
}
