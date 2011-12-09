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
	SearchPathElement a = SearchPathElement::createFromDirectory("/bla/bla/");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString2) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/?");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString3) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/?.lua");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), ".lua");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString4) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/Fallback");
	BOOST_CHECK(!a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/Fallback");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString5) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("");
	BOOST_CHECK(!a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution1) {
	SearchPathElement a = SearchPathElement::createFromDirectory("/bla/bla/");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution2) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/?");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution3) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/?.lua");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?.lua");
}
BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution4) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("/bla/bla/Fallback");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/Fallback");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution5) {
	SearchPathElement a = SearchPathElement::createFromPlaceholderString("");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString1) {
	SearchPathElement a("pre", "suff");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString2) {
	SearchPathElement a("", "suff");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString3) {
	SearchPathElement a("pre", "");
	BOOST_CHECK(a.hasPlaceholder());
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

BOOST_AUTO_TEST_CASE(LuaListEmpty) {
	BOOST_CHECK(SearchPathElement::splitListOfPathTemplates("").empty());
	BOOST_CHECK(SearchPathElement::listOfPathTemplatesToString(SearchPathElement::splitListOfPathTemplates("")).empty());
}

BOOST_AUTO_TEST_CASE(LuaListJustDelimiter) {
	BOOST_CHECK(SearchPathElement::splitListOfPathTemplates(";").empty());
	BOOST_CHECK(SearchPathElement::listOfPathTemplatesToString(SearchPathElement::splitListOfPathTemplates(";")).empty());
}

BOOST_AUTO_TEST_CASE(LuaListOneElement) {
	SearchPathElement::List a = SearchPathElement::splitListOfPathTemplates("one");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromPlaceholderString("one"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfPathTemplatesToString(a), "one");
}

BOOST_AUTO_TEST_CASE(LuaListOneElementWithTrailing) {
	SearchPathElement::List a = SearchPathElement::splitListOfPathTemplates("one;");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromPlaceholderString("one"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfPathTemplatesToString(a), "one");
}

BOOST_AUTO_TEST_CASE(LuaListTwoElements) {
	SearchPathElement::List a = SearchPathElement::splitListOfPathTemplates("one;two");
	BOOST_CHECK_EQUAL(a.size(), 2);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromPlaceholderString("one"));
	BOOST_CHECK_EQUAL(a.at(1), SearchPathElement::createFromPlaceholderString("two"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfPathTemplatesToString(a), "one;two");
}

BOOST_AUTO_TEST_CASE(DirectoryListEmpty) {
	BOOST_CHECK(SearchPathElement::splitListOfDirectories("").empty());
	BOOST_CHECK(SearchPathElement::listOfDirectoriesToString(SearchPathElement::splitListOfDirectories(";")).empty());
}

BOOST_AUTO_TEST_CASE(DirectoryListJustDelimiter) {
	BOOST_CHECK(SearchPathElement::splitListOfDirectories(";").empty());
	BOOST_CHECK(SearchPathElement::listOfDirectoriesToString(SearchPathElement::splitListOfDirectories(";")).empty());
}

BOOST_AUTO_TEST_CASE(DirectoryListOneElement) {
	SearchPathElement::List a = SearchPathElement::splitListOfDirectories("one");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfDirectoriesToString(a), "one/");
}

BOOST_AUTO_TEST_CASE(DirectoryListOneElementWithTrailing) {
	SearchPathElement::List a = SearchPathElement::splitListOfDirectories("one;");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfDirectoriesToString(a), "one/");
}

BOOST_AUTO_TEST_CASE(DirectoryListTwoElements) {
	SearchPathElement::List a = SearchPathElement::splitListOfDirectories("one;two");
	BOOST_CHECK_EQUAL(a.size(), 2);
	BOOST_CHECK_EQUAL(a.at(0), SearchPathElement::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(a.at(1), SearchPathElement::createFromDirectory("two"));
	BOOST_CHECK_EQUAL(SearchPathElement::listOfDirectoriesToString(a), "one/;two/");
}


