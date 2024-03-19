
// *******************
// *******************  Wrapping  for  abilityDT
// *******************
// *******************  TArray<FAbilityList> has contained in ability component
// *******************
// *******************  has additional param about how ability will be interactied with Unit (# remove from FastPanel after using, ...)
// *******************


// #include "Base/Ability/Struct/AbilityList.h"

#pragma once

#include "../Enum/AbilityTraseForm.h"
#include "../Enum/SelectTargetType.h"

#include "AbilityList.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FAbilityList
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		TSubclassOf<class UAbilityDT> Ability_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 CurrRollBackLeft = 0;

	// ** max charge (if current lover => will regenerate)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 ConsecutiveQuantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 RemoveItemAfterUse = false;
	
};