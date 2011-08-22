/** @date	2011

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE FusionMapToTemplate tests

// Internal Includes
#include <util/FusionMapToTemplate.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/mpl/at.hpp>

// Standard includes
// - none

using namespace boost::unit_test;
using namespace util;
using boost::fusion::make_pair;

struct One;
struct Two;
struct Three;

typedef boost::fusion::map <
boost::fusion::pair<One, int>,
      boost::fusion::pair<Two, int>,
      boost::fusion::pair<Three, int> > MapType;

struct SumFunc {
	typedef int result_type;
	template<typename Map>
	static inline int apply() {
		return boost::mpl::at<Map, One >::type::value + boost::mpl::at<Map, Two>::type::value + boost::mpl::at<Map, Three>::type::value;
	}
};

template<typename Key>
struct ValueAt {
	typedef int result_type;
	template<typename Map>
	static inline int apply() {
		return boost::mpl::at<Map, Key>::type::value;
	}
};

BOOST_AUTO_TEST_CASE(SummingFunc) {
	BOOST_CHECK_EQUAL((util::FusionMapToTemplate<SumFunc>(MapType(
	                       make_pair<One>(1),
	                       make_pair<Two>(2),
	                       make_pair<Three>(3))))
	                  , 6);
}

BOOST_AUTO_TEST_CASE(KeywiseFunc) {
	BOOST_CHECK_EQUAL((util::FusionMapToTemplate<ValueAt<One> >(MapType(
	                       make_pair<One>(1),
	                       make_pair<Two>(2),
	                       make_pair<Three>(3))))
	                  , 1);
	BOOST_CHECK_EQUAL((util::FusionMapToTemplate<ValueAt<Two> >(MapType(
	                       make_pair<One>(1),
	                       make_pair<Two>(2),
	                       make_pair<Three>(3))))
	                  , 2);

	BOOST_CHECK_EQUAL((util::FusionMapToTemplate<ValueAt<Three> >(MapType(
	                       make_pair<One>(1),
	                       make_pair<Two>(2),
	                       make_pair<Three>(3))))
	                  , 3);
}
