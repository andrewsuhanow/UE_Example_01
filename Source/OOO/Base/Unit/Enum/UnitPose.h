

// #include "Base/Unit/Enum/UnitPose.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EUnitPose : uint8
{
	none = 0			UMETA(DisplayName = "none"),
	Crawl,
	Crouch,
	RelaxMove = 3,
	NormalMove,
	Run,
	Sprint,
	Fly,
	MAX
};




