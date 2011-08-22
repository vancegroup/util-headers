/** @date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE ValueToTemplate tests

// Internal Includes
#include <util/ValueToTemplate.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/mpl/at.hpp>

// Standard includes
#include <vector>
#include <map>
#include <string>


using namespace boost::unit_test;
using namespace util;
using boost::tuple;
using boost::make_tuple;
using std::string;

struct Metafunc {
	template<typename Seq>
	inline int apply() {
		return boost::mpl::at<0>::value + boost::mpl::at<1>::value + boost::mpl::at<2>::value;
	}
};

BOOST_AUTO_TEST_CASE(ThreeFalseBools) {
	boost::tuple<bool, bool, bool> val = boost::make_tuple(false, false, false);
	CountedUniqueValues<string> a;
	BOOST_CHECK_EQUAL(util::ValueToTemplate<Metafunc>(val), 0);
}
