
#pragma once

// #include "Base/Invertory/Struct/MainInventorSlot.h"

//#include "CoreMinimal.h"



#include "MainInventorSlot.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FMainInventorSlot
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


	FMainInventorSlot() : CurrSlotIndex(-1), ItemPosIndex(-1) {};
	FMainInventorSlot(int32 _CurrSlotIndex, int32 _ItemPosIndex) : CurrSlotIndex(_CurrSlotIndex), ItemPosIndex(_ItemPosIndex) {};


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 CurrSlotIndex = -1;

	// ** First slot-index position (Item)
	// ** and, KEY in Map-Inventor-Container
	// ** -1 - if slot empty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 ItemPosIndex = -1;




};
