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
using namespace util::SearchPath;

BOOST_AUTO_TEST_CASE(ElementDefaultConstruction) {
	FilenameTemplate a;
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString1) {
	FilenameTemplate a = FilenameTemplate::createFromDirectory("/bla/bla/");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString2) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/?");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString3) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/?.lua");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/");
	BOOST_CHECK_EQUAL(a.getSuffix(), ".lua");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString4) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/Fallback");
	BOOST_CHECK(!a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "/bla/bla/Fallback");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionString5) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("");
	BOOST_CHECK(!a.hasPlaceholder());
	BOOST_CHECK(!a.isDirectory());
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution1) {
	FilenameTemplate a = FilenameTemplate::createFromDirectory("/bla/bla/");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution2) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/?");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution3) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/?.lua");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/?.lua");
}
BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution4) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("/bla/bla/Fallback");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "/bla/bla/Fallback");
}

BOOST_AUTO_TEST_CASE(ElementGetStringWithSubstitution5) {
	FilenameTemplate a = FilenameTemplate::createFromTemplate("");
	BOOST_CHECK_EQUAL(a.getStringWithSubstitution(), "");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString1) {
	FilenameTemplate a("pre", "suff");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString2) {
	FilenameTemplate a("", "suff");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementConstructionTwoString3) {
	FilenameTemplate a("pre", "");
	BOOST_CHECK(a.hasPlaceholder());
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementPrefixMutator) {
	FilenameTemplate a;
	a.setPrefix("pre");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "");
}

BOOST_AUTO_TEST_CASE(ElementSuffixMutator) {
	FilenameTemplate a;
	a.setSuffix("suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(ElementPrefixAndSuffixMutator) {
	FilenameTemplate a;
	a.setPrefix("pre");
	a.setSuffix("suff");
	BOOST_CHECK_EQUAL(a.getPrefix(), "pre");
	BOOST_CHECK_EQUAL(a.getSuffix(), "suff");
}

BOOST_AUTO_TEST_CASE(LuaListEmpty) {
	BOOST_CHECK(FilenameTemplate::splitListOfFilenameTemplates("").empty());
	BOOST_CHECK(FilenameTemplate::listOfFilenameTemplatesToString(FilenameTemplate::splitListOfFilenameTemplates("")).empty());
}

BOOST_AUTO_TEST_CASE(LuaListJustDelimiter) {
	BOOST_CHECK(FilenameTemplate::splitListOfFilenameTemplates(";").empty());
	BOOST_CHECK(FilenameTemplate::listOfFilenameTemplatesToString(FilenameTemplate::splitListOfFilenameTemplates(";")).empty());
}

BOOST_AUTO_TEST_CASE(LuaListOneElement) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfFilenameTemplates("one");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromTemplate("one"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfFilenameTemplatesToString(a), "one");
}

BOOST_AUTO_TEST_CASE(LuaListOneElementWithTrailing) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfFilenameTemplates("one;");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromTemplate("one"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfFilenameTemplatesToString(a), "one");
}

BOOST_AUTO_TEST_CASE(LuaListTwoElements) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfFilenameTemplates("one;two");
	BOOST_CHECK_EQUAL(a.size(), 2);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromTemplate("one"));
	BOOST_CHECK_EQUAL(a.at(1), FilenameTemplate::createFromTemplate("two"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfFilenameTemplatesToString(a), "one;two");
}

BOOST_AUTO_TEST_CASE(DirectoryListEmpty) {
	BOOST_CHECK(FilenameTemplate::splitListOfDirectories("").empty());
	BOOST_CHECK(FilenameTemplate::listOfDirectoriesToString(FilenameTemplate::splitListOfDirectories(";")).empty());
}

BOOST_AUTO_TEST_CASE(DirectoryListJustDelimiter) {
	BOOST_CHECK(FilenameTemplate::splitListOfDirectories(";").empty());
	BOOST_CHECK(FilenameTemplate::listOfDirectoriesToString(FilenameTemplate::splitListOfDirectories(";")).empty());
}

BOOST_AUTO_TEST_CASE(DirectoryListOneElement) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfDirectories("one");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfDirectoriesToString(a), "one/");
}

BOOST_AUTO_TEST_CASE(DirectoryListOneElementWithTrailing) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfDirectories("one;");
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfDirectoriesToString(a), "one/");
}

BOOST_AUTO_TEST_CASE(DirectoryListTwoElements) {
	FilenameTemplate::List a = FilenameTemplate::splitListOfDirectories("one;two");
	BOOST_CHECK_EQUAL(a.size(), 2);
	BOOST_CHECK_EQUAL(a.at(0), FilenameTemplate::createFromDirectory("one"));
	BOOST_CHECK_EQUAL(a.at(1), FilenameTemplate::createFromDirectory("two"));
	BOOST_CHECK_EQUAL(FilenameTemplate::listOfDirectoriesToString(a), "one/;two/");
}


