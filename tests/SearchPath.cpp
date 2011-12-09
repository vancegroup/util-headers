/** @date	2011

	@author
	Leif Berg ( <lpberg@iastate.edu> ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE SearchPath tests

// Internal Includes
#include <util/SearchPath.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
// - none


using namespace boost::unit_test;
using namespace util;

BOOST_AUTO_TEST_CASE(ElementDefaultConstruction) {
	SearchPathElement a;
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString1) {
	SearchPathElement a("/bla/bla/");
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString2) {
	SearchPathElement a("/bla/bla/?");
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString3) {
	SearchPathElement a("/bla/bla/?.lua");
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), ".lua");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString4) {
	SearchPathElement a("");
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementGetFullSubstitution1) {
	SearchPathElement a("/bla/bla/");
	BOOST_CHECK_EQUAL(a.getFullWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetFullSubstitution2) {
	SearchPathElement a("/bla/bla/?");
	BOOST_CHECK_EQUAL(a.getFullWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetFullSubstitution3) {
	SearchPathElement a("/bla/bla/?.lua");
	BOOST_CHECK_EQUAL(a.getFullWithSubstitution(), "/bla/bla/?.lua");
}

BOOST_AUTO_TEST_CASE(ElementGetFullSubstitution4) {
	SearchPathElement a("");
	BOOST_CHECK_EQUAL(a.getFullWithSubstitution(), "?");
}
BOOST_AUTO_TEST_CASE(ElementGetFullSubstitution5) {
	SearchPathElement a("pre", "suff");
	BOOST_CHECK_EQUAL(a.getFullWithSubstitution(), "pre?suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString1) {
	SearchPathElement a("pre", "suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString2) {
	SearchPathElement a("", "suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString3) {
	SearchPathElement a("pre", "");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementPrefixMutator) {
	SearchPathElement a;
	a.setPrefix("pre");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementSuffixMutator) {
	SearchPathElement a;
	a.setSuffix("suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementPrefixAndSuffixMutator) {
	SearchPathElement a;
	a.setPrefix("pre");
	a.setSuffix("suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}





