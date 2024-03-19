
#pragma once



// #include "Base/Controller/Enum/TargetType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class ETargetType : uint8
{
	none = 0, 

	Self,
	Location,
	Locations,
	Unit,
	Units,
	

	MAX
};
