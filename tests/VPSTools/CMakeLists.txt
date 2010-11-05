# CMake cross-platform build system
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

stamp_sources_with_version("${CPACK_PACKAGE_VERSION}"
	test_VPSInstance.cpp)

# VPSTools
add_boost_test(VPSInstance
	SOURCES
	test_VPSInstance.cpp
	LIBRARIES
	VPSTools
	TESTS
	ExplicitConstruction
	ImplicitConstruction
	IdenticalSingletons)
