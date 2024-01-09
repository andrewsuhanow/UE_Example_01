
#pragma once



// #include "Base/Amunition/Enum/UseDistanceType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class EUseDistanceType : uint8
{
	optimal_dist,
	max_dist,
	max_dist_clear_vision,
	any_dist,
	any_dist_clear_vision,

	

	MAX
};
