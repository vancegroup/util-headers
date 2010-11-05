# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC


set(SOURCES
	LockFreeBuffer.h
	Saturate.h
	SplitMap.h
	Stride.h)

add_custom_target(UtilityHeaders SOURCES ${SOURCES})
