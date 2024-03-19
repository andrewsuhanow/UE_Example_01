
#pragma once



// #include "Base/Ability/Enum/SelectTargetType.h"

//#include "CoreMinimal.h"


UENUM(BlueprintType, Blueprintable)
enum class ESelectTargetType : uint8
{
	//SelectOnly = 0, 
	//WorldEffect,
	//Both,

	DefaultTargets,
	SelfCaster,
	PointAtCasterLocation,
	PointInFrontOfCaster,
	RandomUnitsAroundCasterInRadius,
	RandomPointAroundCasterInRadius,

	PointAtTargetLocation,
	PointInFrontOfTarget,
	RandomUnitsAroundTargetInRadius,
	RandomPointAroundTargetInRadius,

	MAX
};
