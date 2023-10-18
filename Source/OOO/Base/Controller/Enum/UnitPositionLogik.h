

//#include "../Controller/Enum/UnitPositionLogik.h"

#pragma once

UENUM(BlueprintType, Blueprintable)  
enum class EUnitPositionLogik : uint8
{
	None = 0					UMETA(DisplayName = ""),		// ** for ButtonImage  Select-Group

	PointOnly,
	PointRadius, 
	ShaseTarget,
	ShaseTargetWithReturn,
	MAX
};
