
// #include "Base/Ability/Struct/AbilityDT.h"

#pragma once

#include "../Enum/AbilityType.h"

#include "Engine/DataTable.h"

#include "AbilityDT.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FAbilityDT : public FTableRowBase //  FTableRowBase - make avaulable in DataTable
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	
		EAbilityType AbilityType = EAbilityType::none;


	
};