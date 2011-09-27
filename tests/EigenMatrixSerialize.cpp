/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE EigenMatrixSerialize

// Internal Includes
#include <util/EigenMatrixSerialize.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Standard includes
#include <string>
#include <sstream>

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(IdentityRoundTrip) {
	
	Eigen::Matrix4d deserialized;
	
	std::stringstream ss;
	{
		Eigen::Matrix4d identity(Eigen::Matrix4d::Identity());
		boost::archive::text_oarchive outArchive(ss);
		outArchive << identity;
	}
	std::cout << ss.str();
	{
		boost::archive::text_iarchive inArchive(ss);
		inArchive >> deserialized;
	}
	BOOST_CHECK_EQUAL(Eigen::Matrix4d::Identity(), deserialized);
}
