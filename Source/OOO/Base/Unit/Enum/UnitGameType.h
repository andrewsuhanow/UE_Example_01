
// ** #include "Base/Unit/Enum/UnitGameType.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EUnitGameType : uint8
{
	none,
	Human,
	Holem,
	Tank,
	MAX
};