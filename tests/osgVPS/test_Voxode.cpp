/** @file	test_Voxode.cpp
	@version 1.0.0
	@brief	Voxode test driver

	@date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE Voxode basic tests

// Internal Includes
#include <osgVPS/VoxelizeVisitor.h>
#include <osgVPS/Voxode.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

#include <osg/ref_ptr>
#include <osgDB/ReadFile>

using namespace boost::unit_test;
using namespace osgVPS;

BOOST_AUTO_TEST_CASE(Construction) {
	Voxode vox;
	BOOST_CHECK(!vox.getModel());
}

BOOST_AUTO_TEST_CASE(HeapConstruction) {
	osg::ref_ptr<Voxode> vox = new Voxode;
	BOOST_CHECK(!vox->getModel());
}

BOOST_AUTO_TEST_CASE(RetrieveModel) {
	std::vector<std::string> files;

	files.push_back("block1m.osg");

	files.push_back("bluecone.obj");

	for (unsigned int i = 0; i < files.size(); ++i) {
		VoxelizeVisitor visitor;
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(files[i]);
		BOOST_REQUIRE(node.valid());
		visitor.voxelize(node.get());
		BOOST_CHECK(visitor.getVPSModel());
		osg::ref_ptr<Voxode> vox = new Voxode(visitor.getVPSModel());
		BOOST_CHECK_EQUAL(visitor.getVPSModel(), vox->getModel());
	}
}
