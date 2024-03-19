

#pragma once

// #include "Base/Fraction/UnitAttitudeStatus.h"

#include "UnitAttitudeStatus.generated.h"


UENUM(BlueprintType, Blueprintable)      
enum class EUnitAttitudeStatus : uint8
{
	none,
	Friend,		// = 0 UMETA(DisplayName = "OOO"),
	Neutral,
	Enemy,
	Any,

	Victim,
	MAX
};






