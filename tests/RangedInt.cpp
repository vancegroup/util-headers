/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE RangedInt

// Internal Includes
#include <util/RangedInt.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
// - none

using namespace boost::unit_test;
using namespace util;

BOOST_AUTO_TEST_CASE(InRangeConstructionDefaults) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_NO_THROW(Ranged(1));
	BOOST_CHECK_NO_THROW(Ranged(3));
	BOOST_CHECK_NO_THROW(Ranged(5));
}

BOOST_AUTO_TEST_CASE(OutOfRangeConstructionDefaults) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_THROW(Ranged(7), std::out_of_range);
}

