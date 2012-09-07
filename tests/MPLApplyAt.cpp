/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE MPLApplyAt

// Internal Includes
#include <util/MPLApplyAt.h>

// Library/third-party includes
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/vector.hpp>
#include <BoostTestTargetConfig.h>

// Standard includes
#include <typeinfo>

using namespace boost::unit_test;

/**** Check with a list of MPL integral constant types ****/

struct NumberGetterFunctor {
	NumberGetterFunctor(int & dst) : dest(dst) {}

	template<typename Num>
	void operator()(boost::mpl::identity<Num> const&) {
		dest = Num();
	}
	int & dest;

};

BOOST_AUTO_TEST_CASE(NumberGetter) {
	static const int low = 0;
	static const int high = 5;
	typedef boost::mpl::range_c<int, low, high> sequence;

	for (int i = low; i < high; ++i) {
		int result = -1;
		util::apply_at<sequence>(i, NumberGetterFunctor(result));
		BOOST_CHECK_EQUAL(i, result);
	}
}

BOOST_AUTO_TEST_CASE(NumberGetterBigger) {
	static const int low = 0;
	static const int high = 5;
	typedef boost::mpl::range_c < int, low + 5, high + 5 > sequence;

	for (int i = low; i < high; ++i) {
		int result = -1;
		util::apply_at<sequence>(i, NumberGetterFunctor(result));
		BOOST_CHECK_EQUAL(i + 5, result);
	}
}

/**** Check with a list of real types ****/

typedef const std::type_info * typeinfoptr;
struct TypeInfoAddressFunctor {
	TypeInfoAddressFunctor(typeinfoptr & dst) : dest(dst) {}

	template<typename T>
	void operator()(boost::mpl::identity<T> const&) {
		dest = &typeid(T);
	}
	typeinfoptr & dest;

};

BOOST_AUTO_TEST_CASE(ActualTypes) {
	typedef boost::mpl::vector<unsigned int, int, char, double, float> sequence;
	{
		typeinfoptr result = NULL;
		util::apply_at<sequence>(0, TypeInfoAddressFunctor(result));
		BOOST_CHECK_EQUAL(&typeid(unsigned int), result);
	}
	{
		typeinfoptr result = NULL;
		util::apply_at<sequence>(1, TypeInfoAddressFunctor(result));
		BOOST_CHECK_EQUAL(&typeid(int), result);
	}
	{
		typeinfoptr result = NULL;
		util::apply_at<sequence>(2, TypeInfoAddressFunctor(result));
		BOOST_CHECK_EQUAL(&typeid(char), result);
	}
	{
		typeinfoptr result = NULL;
		util::apply_at<sequence>(3, TypeInfoAddressFunctor(result));
		BOOST_CHECK_EQUAL(&typeid(double), result);
	}
	{
		typeinfoptr result = NULL;
		util::apply_at<sequence>(4, TypeInfoAddressFunctor(result));
		BOOST_CHECK_EQUAL(&typeid(float), result);
	}
}

