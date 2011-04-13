# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

message(STATUS "")
message(STATUS "Bundled third-party code:")

if(BUILD_WITH_EIGEN3)
	message(STATUS "Using Eigen 3.0")
	list(APPEND THIRD_PARTY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/eigen") # for Eigen
else()
	message(STATUS "Using Eigen 2.0.x")
	list(APPEND THIRD_PARTY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/eigen-20") # for Eigen
endif()

# Loki lib SVN https://loki-lib.svn.sourceforge.net/svnroot/loki-lib/trunk@1081
message(STATUS "Using Loki template library r1081")
list(APPEND THIRD_PARTY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/loki-lib")

# Forward these include dirs up to the parent directory
set(THIRD_PARTY_INCLUDE_DIRS ${THIRD_PARTY_INCLUDE_DIRS} PARENT_SCOPE)
