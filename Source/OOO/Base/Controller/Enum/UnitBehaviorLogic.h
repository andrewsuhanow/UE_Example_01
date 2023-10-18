

// #include "../Controller/Enum/UnitBehaviorLogic.h"

#pragma once

UENUM(BlueprintType, Blueprintable)  
enum class EUnitBehaviorLogic : uint8
{
	

	AI,
	Player,
	PlayerOnly,
	DailyBehavior,				// ** use "AI" logic if has enemy
	MAX
};
