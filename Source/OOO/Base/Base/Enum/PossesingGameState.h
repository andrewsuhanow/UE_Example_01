
#pragma once

// #include "Base/Enum/PossesingGameState.h"

UENUM(BlueprintType, Blueprintable)
enum class EPossesingGameState : uint8
{
	top_down			UMETA(DisplayName = "top_down"),
	possesing,
	possesing_ai,
	
	MAX
};



