
#pragma once

// #include "../Controller/Enum/TaskInstigator.h"


UENUM(BlueprintType)
enum class ETaskInstigator : uint8
{
	none		= 0,
	General		= 1,	// ** Player or LevelParty
	AI			= 2,
	Dominant	= 3,	// ** means: Hit, OnBlock, OnDodge, ...
	OtherTask	= 4,
	MAX
};


