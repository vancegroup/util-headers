add_custom_target(headercompile)


if(VRJUGGLER_FOUND)
	include_directories(${VRJUGGLER_INCLUDE_DIRS})
	set(LIBRARIES_BlockingInvokeFunctorVPR ${VRJUGGLER_LIBRARIES})
else()
	list(REMOVE_ITEM HEADERS BlockingInvokeFunctorVPR.h)
endif()

if(OPENSCENEGRAPH_FOUND)
	include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
	if(GMTL_FOUND)
		include_directories(${GMTL_INCLUDE_DIRS})
	else()
		list(REMOVE_ITEM HEADERS gmtlToOsgMatrix.h)
	endif()
else()
	list(REMOVE_ITEM HEADERS osgFindNamedNode.h)
endif()

foreach(HEADER ${HEADERS})
	string(REPLACE ".h" "" SHORTNAME "${HEADER}")
	set(stem "test_headercompile_${SHORTNAME}")
	configure_file(test_headercompile.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp" @ONLY)

	add_executable(${stem} "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp")
	if(LIBRARIES_${SHORTNAME})
		target_link_libraries(${stem} ${LIBRARIES_${SHORTNAME}})
	endif()
	add_test(${stem}_executes ${stem})
	add_dependencies(headercompile ${stem})
endforeach()

