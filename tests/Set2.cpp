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
#include <algorithm>


using namespace boost::unit_test;
using namespace util;

BOOST_AUTO_TEST_CASE(DefaultConstruction) {
	Set2<int> a;
	BOOST_CHECK_LE(a.first(), a.second());
}

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

BOOST_AUTO_TEST_CASE(CopyConstruction) {
	Set2<int> a(5, 10);
	Set2<int> b(a);

	BOOST_CHECK_EQUAL(a.first(), 5);
	BOOST_CHECK_EQUAL(a.second(), 10);

	BOOST_CHECK_EQUAL(b.first(), 5);
	BOOST_CHECK_EQUAL(b.second(), 10);

	BOOST_CHECK_EQUAL(a.first(), b.first());
	BOOST_CHECK_EQUAL(a.second(), b.second());
}

BOOST_AUTO_TEST_CASE(AssignmentOperator) {
	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	BOOST_REQUIRE_NO_THROW(a = b);
	BOOST_CHECK_EQUAL(a.first(), 20);
	BOOST_CHECK_EQUAL(a.second(), 30);

	BOOST_CHECK_EQUAL(a.first(), b.first());
	BOOST_CHECK_EQUAL(a.second(), b.second());
}

BOOST_AUTO_TEST_CASE(AssignmentOperatorBothWays) {
	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	BOOST_REQUIRE_NO_THROW(a = b);
	BOOST_REQUIRE_NO_THROW(b = a);
	BOOST_CHECK_EQUAL(a.first(), 20);
	BOOST_CHECK_EQUAL(a.second(), 30);

	BOOST_CHECK_EQUAL(a.first(), b.first());
	BOOST_CHECK_EQUAL(a.second(), b.second());
}

BOOST_AUTO_TEST_CASE(AssignmentOperatorSelfAssign) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a = a);
	BOOST_CHECK_EQUAL(a.first(), 5);
	BOOST_CHECK_EQUAL(a.second(), 10);
}

BOOST_AUTO_TEST_CASE(MutatorSmallerFirst) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a.set(20, 30));
	BOOST_CHECK_EQUAL(a.first(), 20);
	BOOST_CHECK_EQUAL(a.second(), 30);
}

BOOST_AUTO_TEST_CASE(MutatorSmallerSecond) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a.set(30, 20));
	BOOST_CHECK_EQUAL(a.first(), 20);
	BOOST_CHECK_EQUAL(a.second(), 30);
}

BOOST_AUTO_TEST_CASE(MutatorBothEqual) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a.set(20, 20));
	BOOST_CHECK_EQUAL(a.first(), 20);
	BOOST_CHECK_EQUAL(a.second(), 20);
}

BOOST_AUTO_TEST_CASE(MutatorNoChange) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a.set(5, 10));
	BOOST_CHECK_EQUAL(a.first(), 5);
	BOOST_CHECK_EQUAL(a.second(), 10);
}

BOOST_AUTO_TEST_CASE(MutatorNoEffectiveChange) {
	Set2<int> a(5, 10);

	BOOST_REQUIRE_NO_THROW(a.set(10, 5));
	BOOST_CHECK_EQUAL(a.first(), 5);
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
	std::vector<Set2<int> > v;

	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	v.push_back(a);
	v.push_back(b);

	BOOST_CHECK(v[0] == a);
	BOOST_CHECK(v[1] == b);
}

BOOST_AUTO_TEST_CASE(VectorSort) {
	std::vector<Set2<int> > v;

	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	// pushing in the "wrong" order
	v.push_back(b);
	v.push_back(a);

	std::sort(v.begin(), v.end());

	BOOST_CHECK(v[0] == a);
	BOOST_CHECK(v[1] == b);
}

BOOST_AUTO_TEST_CASE(VectorSortNoOp) {
	std::vector<Set2<int> > v;

	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	v.push_back(a);
	v.push_back(b);

	std::sort(v.begin(), v.end());

	BOOST_CHECK(v[0] == a);
	BOOST_CHECK(v[1] == b);
}

BOOST_AUTO_TEST_CASE(MapCompatibility) {
	std::map<Set2<int>, int> m;

	Set2<int> a(5, 10);
	Set2<int> b(20, 30);

	m.insert(std::make_pair(a, 1));
	m[b] = 2;

	BOOST_REQUIRE_EQUAL(m.size(), 2);
	BOOST_CHECK(m[a] == 1);
	BOOST_CHECK(m[b] == 2);

	BOOST_CHECK(m.find(a)->first == a);
	BOOST_CHECK(m.find(a)->second == 1);

	BOOST_CHECK(m.find(b)->first == b);
	BOOST_CHECK(m.find(b)->second == 2);
}
