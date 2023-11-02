
// #include "Base/Inventory/InventoryComponent.h"

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Struct/MainInventorSlot.h"

#include "../Item/Struct/ItemDT.h"

#include "Enum/SlotType.h"

#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()





public:	

	// ** FirstSlotIndexKEY:	KEY in Map : MainInventoryItem
	// ** FirstSlotIndexKEY:	This Array index
	// ** FirstSlotIndex:		first ItemSlot in this Attay
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")		
		TArray<FMainInventorSlot> MainInventorySlot;
	// ** First slot of "MainInventorySlot" position
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")
		TMap<int32, FItemDT> MainInventoryItem;

public:	

	// ** Add Item to main Inventory
	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool TryAddItemToInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1, TSubclassOf<class AWorldItem> WorldItem = nullptr) ;

/*
	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool AddItemToInventory(FItemDT* _ItemDT, ESlotType _SlotType) const;

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool AddItemToSlotIndex(FItemDT* _ItemDT, ESlotType _SlotType, int32 ToIndex) const;
*/


public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
