
#pragma once

// #include "Base/Unit/Struct/FastPanelSlot.h"

//#include "CoreMinimal.h"


//-------#include "../../Ability/Enum/AbilityLogic.h"

#include "FastPanelSlot.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FFastPanelSlot 
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

	// ** if Item:		Index in InventoryComponent->Map
	// ** if Ability:	Index in AbilityComponent->Array
	// ** if -1:		Empty slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 IndexInContainer = -1;

	// ** If Ability (Subclass Link)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		//---		EAbilityType AbilityType = EAbilityType::none;
		// 777 TSubclassOf<UAbilityDT>& Ability_class;

	// ** if Ability, name of it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		FName AbilityName = FName("none");
};
