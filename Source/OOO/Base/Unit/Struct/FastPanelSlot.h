
#pragma once

// #include "Base/Unit/Struct/FastPanelSlot.h"

//#include "CoreMinimal.h"


#include "../../Ability/Enum/AbilityType.h"

#include "FastPanelSlot.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FFastPanelSlot 
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

	// ** if Item:		Index in Map
	// ** if Ability:	This Array Index (no matter but -1)
	// ** if -1:		Empty slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 IndexInContainer = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		EAbilityType AbilityType = EAbilityType::none;

};
