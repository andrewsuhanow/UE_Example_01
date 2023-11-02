
#pragma once

//#include "Base/Enum/TurnBaseGameState.h"

UENUM(BlueprintType, Blueprintable)
enum class ETurnBaseGameState : uint8
{
	RealTime			UMETA(DisplayName = "Crawl"),
	Pause,
	TurnBase,
	MAX
};