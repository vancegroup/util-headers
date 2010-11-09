/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE CountedUniqueValues tests

// Internal Includes
#include <util/CountedUniqueValues.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <vector>
#include <map>
#include <string>


using namespace boost::unit_test;
using namespace util;
using std::string;

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	CountedUniqueValues<string> a;
	BOOST_CHECK_EQUAL(a.size(), 0);
}

BOOST_AUTO_TEST_CASE(IncrementalCounts) {
	CountedUniqueValues<string> a;
	BOOST_CHECK_EQUAL(a.store("foo"), 0);
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.store("bar"), 1);
	BOOST_CHECK_EQUAL(a.size(), 2);
}
