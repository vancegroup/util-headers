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

struct Fixture {
	Fixture() : StringId(typeid(std::string)), IntId(typeid(int)) {}
	TypeId StringId;
	TypeId IntId;
	TypeId EmptyId;
};

BOOST_AUTO_TEST_CASE(DefaultConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId());
}

BOOST_AUTO_TEST_CASE(TypeinfoConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId(typeid(int)));
	BOOST_REQUIRE_NO_THROW(TypeId(typeid(std::string)));
}

BOOST_AUTO_TEST_CASE(MPLIdentityConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId(boost::mpl::identity<int>()));
	BOOST_REQUIRE_NO_THROW(TypeId(boost::mpl::identity<std::string>()));
}

BOOST_AUTO_TEST_CASE(StaticTemplateConstructor) {
	BOOST_REQUIRE_NO_THROW(TypeId::create<int>());
	BOOST_REQUIRE_NO_THROW(TypeId::create<std::string>());
}

BOOST_AUTO_TEST_CASE(FixtureConstruction) {
	BOOST_REQUIRE_NO_THROW(Fixture());
}

BOOST_AUTO_TEST_CASE(EqualityComparison) {
	BOOST_CHECK_EQUAL(TypeId(), TypeId());
	BOOST_CHECK_EQUAL(TypeId(typeid(int)), TypeId(typeid(int)));
	BOOST_CHECK_EQUAL(TypeId(typeid(std::string)), TypeId(typeid(std::string)));

	BOOST_CHECK_NE(TypeId(), TypeId(typeid(std::string)));
	BOOST_CHECK_NE(TypeId(typeid(int)), TypeId(typeid(std::string)));

	BOOST_CHECK(TypeId(typeid(std::string)) == typeid(std::string));
	BOOST_CHECK(typeid(std::string) == TypeId(typeid(std::string)));

	BOOST_CHECK(TypeId() != typeid(std::string));
	BOOST_CHECK(typeid(std::string) != TypeId());
}

BOOST_AUTO_TEST_CASE(ConstructorEquality) {
	BOOST_CHECK_EQUAL(TypeId(typeid(int)), TypeId::create<int>());
	BOOST_CHECK_EQUAL(TypeId(typeid(std::string)), TypeId::create<std::string>());

	BOOST_CHECK_EQUAL(TypeId(typeid(int)), TypeId(boost::mpl::identity<int>()));
	BOOST_CHECK_EQUAL(TypeId(typeid(std::string)), TypeId(boost::mpl::identity<std::string>()));
}

BOOST_AUTO_TEST_CASE(EmptyMethod) {
	Fixture f;
	BOOST_CHECK(f.EmptyId.empty());
	BOOST_CHECK(!f.IntId.empty());
	BOOST_CHECK(!f.StringId.empty());
}

BOOST_AUTO_TEST_CASE(GetMethod) {
	Fixture f;
	BOOST_CHECK_NO_THROW(f.IntId.get());
	BOOST_CHECK_NO_THROW(f.StringId.get());
}

BOOST_AUTO_TEST_CASE(GetPointerMethod) {
	Fixture f;
	BOOST_CHECK_NO_THROW(f.EmptyId.getPointer());
	BOOST_CHECK_NO_THROW(f.IntId.getPointer());
	BOOST_CHECK_NO_THROW(f.StringId.getPointer());
}

BOOST_AUTO_TEST_CASE(NameMethod) {
	Fixture f;
	/// These are all the guarantees we give - and even that might be too much.
	BOOST_CHECK_EQUAL(std::string(f.EmptyId.name()), "");
	BOOST_CHECK_NE(std::string(f.IntId.name()), "");
	BOOST_CHECK_NE(std::string(f.StringId.name()), "");
}

BOOST_AUTO_TEST_CASE(Ordering) {
	Fixture f;
	BOOST_CHECK(!(f.EmptyId < f.EmptyId));
	BOOST_CHECK(!(f.EmptyId < f.IntId));
	BOOST_CHECK(!(f.EmptyId < typeid(int)));
	BOOST_CHECK(!(f.EmptyId < f.StringId));
	BOOST_CHECK(!(f.EmptyId < typeid(std::string)));


	BOOST_CHECK(!(f.EmptyId < f.EmptyId));
	BOOST_CHECK(!(f.IntId < f.IntId));
	BOOST_CHECK(!(f.StringId < f.StringId));

	BOOST_CHECK(f.StringId < f.EmptyId);
	BOOST_CHECK(typeid(std::string) < f.EmptyId);
	BOOST_CHECK(f.IntId < f.EmptyId);
	BOOST_CHECK(typeid(int) < f.EmptyId);

	BOOST_CHECK((f.IntId < f.StringId) || (f.StringId < f.IntId));
	BOOST_CHECK(!((f.IntId < f.StringId) && (f.StringId < f.IntId)));
}

BOOST_AUTO_TEST_CASE(Vector) {
	BOOST_REQUIRE_NO_THROW(TypeIdVector());
	TypeIdVector vec;
	Fixture f;
	BOOST_REQUIRE_NO_THROW(vec.push_back(f.EmptyId));
	BOOST_REQUIRE_NO_THROW(vec.push_back(f.IntId));
	BOOST_REQUIRE_NO_THROW(vec.push_back(f.StringId));

	BOOST_REQUIRE_EQUAL(vec.size(), 3);
	BOOST_CHECK_EQUAL(vec[0], f.EmptyId);
	BOOST_CHECK_EQUAL(vec[1], f.IntId);
	BOOST_CHECK_EQUAL(vec[2], f.StringId);

	BOOST_CHECK(vec != TypeIdVector());

	BOOST_REQUIRE_NO_THROW(TypeIdVector(vec));
	TypeIdVector v2(vec);
	BOOST_CHECK(vec == v2);
}

BOOST_AUTO_TEST_CASE(Set) {
	BOOST_REQUIRE_NO_THROW(TypeIdSet());
	TypeIdSet set;
	Fixture f;
	BOOST_REQUIRE_NO_THROW(set.insert(f.EmptyId));
	BOOST_REQUIRE_NO_THROW(set.insert(f.IntId));
	BOOST_REQUIRE_NO_THROW(set.insert(f.StringId));

	BOOST_REQUIRE_EQUAL(set.size(), 3);
	BOOST_CHECK(set.find(f.EmptyId) != set.end());
	BOOST_CHECK(set.find(f.IntId) != set.end());
	BOOST_CHECK(set.find(f.StringId) != set.end());

	BOOST_CHECK(set != TypeIdSet());

	BOOST_REQUIRE_NO_THROW(TypeIdSet(set));
	TypeIdSet s2(set);
	BOOST_CHECK(set == s2);

	BOOST_REQUIRE_NO_THROW(set.erase(set.find(f.IntId)));
	BOOST_REQUIRE_EQUAL(set.size(), 2);
	BOOST_CHECK(set.find(f.EmptyId) != set.end());
	BOOST_CHECK(set.find(f.IntId) == set.end());
	BOOST_CHECK(set.find(f.StringId) != set.end());
}

