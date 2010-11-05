# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

add_custom_target(util-DataStructures
	SOURCES
	LockFreeBuffer.h
	SplitMap.h)

add_custom_target(util-Math
	SOURCES
	RandomFloat.h
	Saturate.h)
	
add_custom_target(util-OSG
	SOURCES
	gmtlToOsgMatrix.h
	osgFindNamedNode.h)

add_custom_target(util-Other
	SOURCES
	Stride.h
	SizeGenerator.h
	GetLocalComputerName.h)
