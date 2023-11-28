
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


// **************************************************************************************************	
// ***************************************    Main_Inventory    *************************************


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

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool TryAddItemToMainInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1, 
			TSubclassOf<class AWorldItem> WorldItem = nullptr, bool ForseAdd = false);

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void AssignItemIndexesToMainInvSlots(class AUnit* _Unit, const FItemDT* ItemDT,
			int32 FirstSlotIndex, int32& MainInvSlotsNum, 
			bool IsCanAddNewSlots = false, bool IsItemErase = false);

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool IsMainInventorySlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		FItemDT* GetItemRefFromMainInventory(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void RemoveItemFromMainInventory(int32 SlotIndex);


	// ** UFUNCTION(BlueprintCallable, Category = "OOO")
	bool CheckItemCollision(const class AUnit* UnitOvner, const FItemDT* ItemDT, int32 Position);


public:

	void AddItemToMainInventoryArray(AUnit* _Unit, const FItemDT* ItemDT, 
		int32 ToSlotIndex, int32& MainInvSlotsNum);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddSlotsRowToMainInventor(int32 _MainInvCollNum);

	///UFUNCTION(BlueprintCallable, Category = "OOO_GlobalInventory")
		bool AddStackableItemInMainInv(FItemDT* _FromItemDT, FItemDT* _ToItemDT);

// ****************************************************************************************************	
// ***************************************    Global_Inventory    *************************************

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_GlobalInventory")		
		TArray<FItemDT> GlobalInvItemSlot;

public:

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void AddItemToGlobalInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1);

	UFUNCTION(BlueprintCallable, Category = "OOO_GlobalInventory")
		bool IsGlobalInventorySlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		FItemDT* GetItemRefFromGlobalInventory(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO_GlobalInventory")
		void RemoveItemFromGlobalInventory(int32 SlotIndex);


public:

	///UFUNCTION(BlueprintCallable, Category = "OOO_GlobalInventory")
		bool AddStackableItemInGlobalInv(FItemDT* _ItemDT, 
			int32 _SlotIndex, int32 _NextSlotIndex = -1);








public:	

	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void Init();

};




