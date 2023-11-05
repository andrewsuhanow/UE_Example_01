
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

	// ** ItemPosIndex:		KEY in Map : MainInventoryItem.
	// **					First ItemSlot in this Array.
	// ** CurrSlotIndex:	This Array index.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")		
		TArray<FMainInventorSlot> MainInventorySlot;
	// ** KAY = First slot of "MainInventorySlot" position
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")
		TMap<int32, FItemDT> MainInventoryItem;

public:	

	// ** Add Item to main Inventory
	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool TryAddItemToInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1, TSubclassOf<class AWorldItem> WorldItem = nullptr) ;


public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void Init();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddSlotsRowToMainInventor(int32 _MainInvCollNum);


	// ** UFUNCTION(BlueprintCallable, Category = "OOO")
		bool CheckItemCollision(const class AUnit* UnitOvner, const FItemDT* ItemDT, int32 Position);
};

