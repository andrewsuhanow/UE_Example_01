
// ** !!!!!!!!!!!!!!!! 
// ** !!!!!!!!!!!!!!!! Abulity may spend mana, stamina, ..., or item from invertory   
// ** !!!!!!!!!!!!!!!! 
// ** !!!!!!!!!!!!!!!! use in AbilityDT
// ** !!!!!!!!!!!!!!!! 





// #include "Base/Ability/Struct/AbilityCost.h"

#pragma once

#include "../Enum/AbilityTraseForm.h"
#include "../Enum/SelectTargetType.h"
#include "../../UnitState/Struct/UnitParamModifier.h"

#include "AbilityCost.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FAbilityCost
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()




	FAbilityCost();


	// ** Change any Unit-Param
	// ** ModifierParam.Value = 0.f:  Not change param
	// ** ModifierType: use here (-1) only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		FUnitParamModifier ModifierParam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 RollBackTimeRound = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		FName ConsumeItemName = FName("none");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 ConsumeItemCount = 0;
};