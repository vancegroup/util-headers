# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

set(UTIL_HEADERS
	SizeGenerator.h
	Stride.h)

set(DATASTRUCTURES_HEADERS
	BlockingInvokeFunctor.h
	booststdint.h
	CountedUniqueValues.h
	FusionMapToTemplate.h
	LockFreeBuffer.h
	RangedInt.h
	SearchPath.h
	SplitMap.h
	TupleTransmission.h
	ValueToTemplate.h
	ValueToTemplatePolicy.h
	WithHistory.h)

if(VPR22_FOUND OR VPR20_FOUND)
	list(APPEND DATASTRUCTURES_HEADERS
		BlockingInvokeFunctorVPR.h)
else()
	list(APPEND UNTESTED_HEADERS
		BlockingInvokeFunctorVPR.h)
endif()

set(METAPROGRAMMING_HEADERS
	MPLApplyAt.h
	MPLFindIndex.h)

set(MATH_HEADERS
	CubeComponents.h
	EigenMatrixSerialize.h
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
else()
	list(APPEND UNTESTED_HEADERS
		osgFindNamedNode.h)
endif()
if(OPENSCENEGRAPH_FOUND AND GMTL_FOUND)
	list(APPEND FREEFUNCTION_HEADERS
		gmtlToOsgMatrix.h)
else()
	list(APPEND UNTESTED_HEADERS
		gmtlToOsgMatrix.h)
endif()


add_custom_target(util
	SOURCES
	Documentation.dox
	${UTIL_HEADERS})

add_custom_target(util-DataStructures
	SOURCES
	${DATASTRUCTURES_HEADERS})

add_custom_target(util-Math
	SOURCES
	${MATH_HEADERS})

add_custom_target(util-Metaprogramming
	SOURCES
	${METAPROGRAMMING_HEADERS})

add_custom_target(util-FreeFunctions
	SOURCES
	${FREEFUNCTION_HEADERS})

set(HEADERS ${UTIL_HEADERS} ${DATASTRUCTURES_HEADERS} ${MATH_HEADERS} ${METAPROGRAMMING_HEADERS} ${FREEFUNCTION_HEADERS} PARENT_SCOPE)
set(UNTESTED_HEADERS ${UNTESTED_HEADERS} PARENT_SCOPE)
