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
	Ranged val(3);
	BOOST_CHECK_THROW(Ranged(7), std::out_of_range);
	BOOST_CHECK_THROW(val = 7, std::out_of_range);
}

BOOST_AUTO_TEST_CASE(URUMath) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_EQUAL(Ranged(3) + 1, 4);
	BOOST_CHECK_EQUAL(1 + Ranged(3), 4);
}

BOOST_AUTO_TEST_CASE(URRMath) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_EQUAL(Ranged(3) + 1, Ranged(4));
	BOOST_CHECK_EQUAL(1 + Ranged(3), Ranged(4));
}

BOOST_AUTO_TEST_CASE(UURMath) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_EQUAL(3 + 1, Ranged(4));
}

BOOST_AUTO_TEST_CASE(RRUMath) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_EQUAL(Ranged(3) + Ranged(1), 4);
}

BOOST_AUTO_TEST_CASE(RRRMath) {
	typedef RangedInt<1, 5> Ranged;
	BOOST_CHECK_EQUAL(Ranged(3) + Ranged(1), Ranged(4));
}

BOOST_AUTO_TEST_CASE(InRangeConstructionNotChecked) {
	typedef RangedInt<1, 5, NeverCheck> Ranged;
	BOOST_CHECK_NO_THROW(Ranged(1));
	BOOST_CHECK_NO_THROW(Ranged(3));
	BOOST_CHECK_NO_THROW(Ranged(5));
	Ranged a(3);
	Ranged b(4);
	Ranged c(b);
	BOOST_CHECK_NO_THROW(a = 1);
	BOOST_CHECK_NO_THROW(a = b);
}

BOOST_AUTO_TEST_CASE(OutOfRangeConstructionNotChecked) {
	typedef RangedInt<1, 5, NeverCheck> Ranged;
	BOOST_CHECK_NO_THROW(Ranged(7));
}

BOOST_AUTO_TEST_CASE(SameRangeCrossChecking) {
	typedef RangedInt<1, 5, NeverCheck> RangedLoose;
	typedef RangedInt<1, 5, AlwaysCheck> RangedStrict;
	RangedLoose loose(3);
	RangedStrict strict(3);
	BOOST_CHECK_NO_THROW(RangedLoose a(RangedStrict(3)));
	BOOST_CHECK_NO_THROW(loose = RangedStrict(3));
	BOOST_CHECK_THROW(RangedStrict(RangedLoose(7)), std::out_of_range);
	BOOST_CHECK_THROW(strict = RangedLoose(7), std::out_of_range);
}


