/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE WithHistory

// Internal Includes
#include <util/WithHistory.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <vector>
#include <map>
#include <algorithm>


using namespace boost::unit_test;
using namespace util;

BOOST_AUTO_TEST_CASE(DefaultConstructionPOD) {
	WithHistory<int> a;
}

BOOST_AUTO_TEST_CASE(ValueConstructionPOD) {
	WithHistory<int> a(5);
	BOOST_CHECK_EQUAL(a.current(), 5);
}

BOOST_AUTO_TEST_CASE(DualValueConstructionPOD) {
	WithHistory<int> a(5, 10);
	BOOST_CHECK_EQUAL(a.current(), 5);
	BOOST_CHECK_EQUAL(a.previous(), 10);
}

BOOST_AUTO_TEST_CASE(DualValuePODSwap) {
	WithHistory<int> a(5, 10);
	BOOST_CHECK_EQUAL(a.current(), 5);
	BOOST_CHECK_EQUAL(a.previous(), 10);
	a.swap();
	BOOST_CHECK_EQUAL(a.current(), 10);
	BOOST_CHECK_EQUAL(a.previous(), 5);	
}
BOOST_AUTO_TEST_CASE(DualValuePODAdvanceByCopy) {
	WithHistory<int> a(5, 10);
	BOOST_CHECK_EQUAL(a.current(), 5);
	BOOST_CHECK_EQUAL(a.previous(), 10);
	a.advanceByCopy();
	BOOST_CHECK_EQUAL(a.current(), 5);
	BOOST_CHECK_EQUAL(a.previous(), 5);	
}

