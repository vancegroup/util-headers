# CMake cross-platform build system
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

stamp_sources_with_version("${CPACK_PACKAGE_VERSION}"
	test_VoxelizeVisitor.cpp
	test_Voxode.cpp)

add_boost_test(VoxelizeVisitor
	SOURCES
	test_VoxelizeVisitor.cpp
	LIBRARIES
	osgVPS
	RESOURCES
	"${TESTS_DATA}/block1m.osg"
	"${TESTS_DATA}/bluecone.obj"
	"${TESTS_DATA}/headtranslated.ive"
	TESTS
	Construction
	ThrowBeforeVoxelization
	ApplyVoxelizeVisitor)

add_boost_test(Voxode
	SOURCES
	test_Voxode.cpp
	LIBRARIES
	osgVPS
	RESOURCES
	"${TESTS_DATA}/block1m.osg"
	"${TESTS_DATA}/bluecone.obj"
	"${TESTS_DATA}/headtranslated.ive")
