/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Set2 tests

// Internal Includes
#include <util/Set2.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <vector>
#include <map>


using namespace boost::unit_test;
using namespace util;

BOOST_AUTO_TEST_CASE(ConstructionSmallerFirst) {
	Set2<int> a(5, 10);
	BOOST_CHECK_EQUAL(a.first(), 5);
	BOOST_CHECK_EQUAL(a.second(), 10);
}

BOOST_AUTO_TEST_CASE(ConstructionSmallerSecond) {
	Set2<int> a(10, 5);
	BOOST_CHECK_EQUAL(a.first(), 5);
	BOOST_CHECK_EQUAL(a.second(), 10);
}

BOOST_AUTO_TEST_CASE(ConstructionEqual) {
	Set2<int> a(10, 10);
	
	BOOST_CHECK_EQUAL(a.first(), 10);
	BOOST_CHECK_EQUAL(a.second(), 10);
}

BOOST_AUTO_TEST_CASE(ComparisonFirstsUnequal) {
	Set2<int> a(5, 10);
	Set2<int> b(20, 30);
	
	BOOST_CHECK(a < b);
	BOOST_CHECK(! (b < a) );
	
	BOOST_CHECK(! (a == b) );
	BOOST_CHECK(! (b == a) );
}

BOOST_AUTO_TEST_CASE(ComparisonFirstsEqual) {
	Set2<int> a(5, 10);
	Set2<int> b(5, 30);
	
	BOOST_CHECK(a < b);
	BOOST_CHECK(! (b < a) );
	
	BOOST_CHECK(! (a == b) );
	BOOST_CHECK(! (b == a) );
}

BOOST_AUTO_TEST_CASE(ComparisonBothEqual) {
	Set2<int> a(5, 10);
	Set2<int> b(5, 10);
	
	BOOST_CHECK(! (a < b) );
	BOOST_CHECK(! (b < a) );
	
	BOOST_CHECK(a == b);
	BOOST_CHECK(b == a);
}

BOOST_AUTO_TEST_CASE(VectorCompatibility) {


}
