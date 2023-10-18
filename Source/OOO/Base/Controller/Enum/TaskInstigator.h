
#pragma once

// #include "../Controller/Enum/TaskInstigator.h"


UENUM(BlueprintType)
enum class ETaskInstigator : uint8
{
	General	= 0,	// ** Player or LevelParty
	AI				= 1,
	Dominant	= 2,	// ** means: Hit, OnBlock, OnDodge, ...
	MAX
};