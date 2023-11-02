
#pragma once



// #include "Base/Ability/Enum/AbilityType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class EAbilityType : uint8
{
	none = 0, 

	
	drink,

	throw_sing,
	throw_knife,

	use_up,
	usem_middle,
	use_down,

	harvest,

	pick_up,
	drop,

	healdt,

	MAX
};
