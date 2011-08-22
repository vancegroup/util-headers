# CMake cross-platform build system
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

add_boost_test(Saturate
	SOURCES
	Saturate.cpp
	TESTS
	TwoParamNoSaturateZeros
	ThreeParamNoSaturateZeros
	TwoParam1DNoSaturate
	TwoParam1DNoSaturateNeg
	TwoParam1DSaturate
	TwoParam1DSaturateNeg
	ThreeParam1DNoSaturate
	ThreeParam1DNoSaturateNeg
	ThreeParam1DSaturate
	ThreeParam1DSaturateNeg
	TwoParam3DNoSaturate
	TwoParam3DNoSaturateNeg
	TwoParam3DSaturate
	TwoParam3DSaturateNeg
	ThreeParam3DNoSaturate
	ThreeParam3DNoSaturateNeg
	ThreeParam3DSaturate
	ThreeParam3DSaturateNeg)

add_boost_test(Set2
	SOURCES
	Set2.cpp
	TESTS
	DefaultConstruction
	ConstructionSmallerFirst
	ConstructionSmallerSecond
	ConstructionEqual
	CopyConstruction
	AssignmentOperator
	AssignmentOperatorBothWays
	AssignmentOperatorSelfAssign
	MutatorSmallerFirst
	MutatorSmallerSecond
	MutatorBothEqual
	MutatorNoChange
	MutatorNoEffectiveChange
	ComparisonFirstsUnequal
	ComparisonFirstsEqual
	ComparisonBothEqual
	VectorCompatibility
	VectorSort
	VectorSortNoOp
	MapCompatibility
	MapUpdate)

add_boost_test(CountedUniqueValues
	SOURCES
	CountedUniqueValues.cpp)

add_boost_test(EigenTie
	SOURCES
	EigenTie.cpp
	TESTS
	ThreeZerosAssign
	ThreeOnesAssign
	ThreeZerosTieTieAssign
	ThreeOnesTieTieAssign
	ThreeZerosChainedAssign
	ThreeOnesChainedAssign
	AliasingAcrossAssign
	NoThrowForRHSNotUnique
	ThrowsTwoNotUnique
	ThrowsThreeNotUnique)

add_boost_test(ValueToTemplate
	SOURCES
	ValueToTemplate.cpp)

add_boost_test(WithHistory
	SOURCES
	WithHistory.cpp
	TESTS
	DefaultConstructionPOD
	ValueConstructionPOD
	ValuePODSwap
	ValuePODAdvanceByCopy
	DualValueConstructionPOD
	CopyFromDefaultConstructionPOD
	CopyFromValueConstructionPOD
	CopyFromDualValueConstructionPOD
	DualValuePODSwap
	DualValuePODAdvanceByCopy
	DefaultConstructionVector
	ValueConstructionVector
	ValueVectorSwap
	ValueVectorAdvanceByCopy
	DualValueConstructionVector
	DualValueVectorSwap
	DualValueVectorAdvanceByCopy
	CopyFromDefaultConstructionVector
	CopyFromValueConstructionVector
	CopyFromDualValueConstructionVector)

add_subdirectory(cleanbuild)
