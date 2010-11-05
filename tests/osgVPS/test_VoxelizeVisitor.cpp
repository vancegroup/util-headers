/** @file	test_VoxelizeVisitor.cpp
	@version 1.0.0
	@brief	VoxelizeVisitor test driver

	@date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE VoxelizeVisitor basic tests

// Internal Includes
#include <osgVPS/VoxelizeVisitor.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/shared_ptr.hpp>

#include <osgDB/ReadFile>

using namespace boost::unit_test;
using namespace osgVPS;

BOOST_AUTO_TEST_CASE(Construction) {
	VoxelizeVisitor visitor;
}

BOOST_AUTO_TEST_CASE(ThrowBeforeVoxelization) {
	VoxelizeVisitor visitor;
	BOOST_CHECK_THROW( visitor.getVPSModel(), NotYetVoxelizedException );
}

BOOST_AUTO_TEST_CASE(ApplyVoxelizeVisitor) {
	std::vector<std::string> files;
	std::vector<unsigned int> tris;
	std::vector<unsigned int> parts;

	files.push_back("block1m.osg");
	parts.push_back(1);
	tris.push_back(12);

	files.push_back("bluecone.obj");
	parts.push_back(1);
	tris.push_back(102);

	files.push_back("headtranslated.ive");
	parts.push_back(1);
	tris.push_back(17402);

	for (unsigned int i = 0; i < files.size(); ++i) {
		VoxelizeVisitor visitor;
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(files[i]);
		BOOST_REQUIRE(node.valid());
		node->accept(visitor);
		BOOST_CHECK(visitor.getVPSModel());
		BOOST_CHECK_EQUAL(visitor.getNumParts(), parts[i]);
		BOOST_CHECK_EQUAL(visitor.getTotalTriangles(), tris[i]);
	}
}
