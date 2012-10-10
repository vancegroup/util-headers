/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TypeId

// Internal Includes
#include <util/TypeId.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <vector>
#include <set>
#include <string>

using namespace boost::unit_test;

using util::TypeId;
typedef std::vector<util::TypeId> TypeIdVector;
typedef std::set<util::TypeId> TypeIdSet;

BOOST_AUTO_TEST_CASE(DefaultConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId());
}

BOOST_AUTO_TEST_CASE(TypeinfoConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId(typeid(int)));
	BOOST_REQUIRE_NO_THROW(TypeId(typeid(std::string)));
}

BOOST_AUTO_TEST_CASE(EqualityComparison) {
	BOOST_CHECK_EQUAL(TypeId(), TypeId());
	BOOST_CHECK_EQUAL(TypeId(typeid(int)), TypeId(typeid(int)));
	BOOST_CHECK_EQUAL(TypeId(typeid(std::string)), TypeId(typeid(std::string)));

	BOOST_CHECK_NE(TypeId(), TypeId(typeid(std::string)));

	BOOST_CHECK(TypeId(typeid(std::string)) == typeid(std::string));
	BOOST_CHECK(typeid(std::string) == TypeId(typeid(std::string)));

	BOOST_CHECK(TypeId() != typeid(std::string));
	BOOST_CHECK(typeid(std::string) != TypeId());
}

