# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

add_custom_target(util
	SOURCES
	Stride.h
	SizeGenerator.h)

add_custom_target(util-DataStructures
	SOURCES
	CountedUniqueValues.h
	LockFreeBuffer.h
	SplitMap.h)

add_custom_target(util-Math
	SOURCES
	RandomFloat.h
	Saturate.h)
	
add_custom_target(util-FreeFunctions
	SOURCES
	ChangeFileExtension.h
	GetLocalComputerName.h
	gmtlToOsgMatrix.h
	osgFindNamedNode.h)


