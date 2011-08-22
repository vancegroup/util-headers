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
namespace mpl = boost::mpl;

struct Metafunc {
	typedef int return_type;
	template<typename Seq>
	static inline int apply() {
		return boost::mpl::at_c<Seq, 0 >::type::value + boost::mpl::at_c<Seq, 1>::type::value + boost::mpl::at_c<Seq, 2>::type::value;
	}
};

BOOST_AUTO_TEST_CASE(AllBools) {
	BOOST_CHECK_EQUAL((util::ValueToTemplate<Metafunc>(boost::make_tuple(false, false, false))), 0);
	BOOST_CHECK_EQUAL((util::ValueToTemplate<Metafunc>(boost::make_tuple(false, true, false))), 1);
}

BOOST_AUTO_TEST_CASE(BoolsAndInts) {
	BOOST_CHECK_EQUAL((util::ValueToTemplate<Metafunc>(boost::make_tuple(5, false, 3))), 8);
}

}
