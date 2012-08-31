/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE TupleTransmission

// Internal Includes
#include <util/TupleTransmission.h>
#include <util/booststdint.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <string>
#include <sstream>


using namespace boost::unit_test;
using namespace stdint;


BOOST_AUTO_TEST_CASE(SizeofSimple) {
	using util::transmission::MessageDescription;
	namespace mpl = boost::mpl;
	BOOST_CHECK_EQUAL( int(MessageDescription<mpl::vector<int16_t, int16_t, int16_t> >::message_size) , 3 * 2);
	BOOST_CHECK_EQUAL( int(MessageDescription<mpl::vector<uint16_t, uint16_t, uint16_t> >::message_size) , 3 * 2);
	BOOST_CHECK_EQUAL( int(MessageDescription<mpl::vector<int8_t> >::message_size) , 1);
	BOOST_CHECK_EQUAL( int(MessageDescription<mpl::vector<> >::message_size) , 0);
}

/*
BOOST_AUTO_TEST_CASE(ConstantVecRoundTrip) {

	Eigen::Vector3d deserialized;

	std::stringstream ss;
	{
		Eigen::Vector3d c(Eigen::Vector3d::Constant(1));
		boost::archive::text_oarchive outArchive(ss);
		outArchive << c;
	}
	std::cout << ss.str();
	{
		boost::archive::text_iarchive inArchive(ss);
		inArchive >> deserialized;
	}
	BOOST_CHECK_EQUAL(Eigen::Vector3d::Constant(1), deserialized);
}
*/
