
#pragma once

// #include "Base/Invertory/Struct/MainInventorSlot.h"

//#include "CoreMinimal.h"



#include "MainInventorSlot.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FMainInventorSlot
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

	// ** First slot of item position
	// ** and KEY in Map-Inventor-Container
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 FirstSlotIndexKEY = -1;

	// ** Pointer on FirstSlotIndexKEY if item bound several Slots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 FirstSlotIndex = -1;


};
