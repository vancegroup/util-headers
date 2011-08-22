# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

set(UTIL_HEADERS
	Stride.h
	SizeGenerator.h)

set(DATASTRUCTURES_HEADERS
	BlockingInvokeFunctor.h
	CountedUniqueValues.h
	LockFreeBuffer.h
	SplitMap.h
	ValueToTemplate.h
	ValueToTemplatePolicy.h
	WithHistory.h)

if(VPR22_FOUND OR VPR20_FOUND)
	list(APPEND DATASTRUCTURES_HEADERS
		BlockingInvokeFunctorVPR.h)
endif()

set(MATH_HEADERS
	EigenTie.h
	RandomFloat.h
	Saturate.h)

set(FREEFUNCTION_HEADERS
	ChangeFileExtension.h
	GetLocalComputerName.h
	launchByAssociation.h)

if(OPENSCENEGRAPH_FOUND)
	list(APPEND FREEFUNCTION_HEADERS
		osgFindNamedNode.h)
	if(GMTL_FOUND)
		list(APPEND FREEFUNCTION_HEADERS
			gmtlToOsgMatrix.h)
	endif()
endif()


add_custom_target(util
	SOURCES
	${UTIL_HEADERS})

add_custom_target(util-DataStructures
	SOURCES
	${DATASTRUCTURES_HEADERS})

add_custom_target(util-Math
	SOURCES
	${MATH_HEADERS})

add_custom_target(util-FreeFunctions
	SOURCES
	${FREEFUNCTION_HEADERS})

set(HEADERS ${UTIL_HEADERS} ${DATASTRUCTURES_HEADERS} ${MATH_HEADERS} ${FREEFUNCTION_HEADERS} PARENT_SCOPE)
