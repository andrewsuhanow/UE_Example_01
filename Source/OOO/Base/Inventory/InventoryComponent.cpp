


// #include "Base/Inventory/InventoryComponent.h"
#include "InventoryComponent.h"

#include "../Item/WorldItem.h"
#include "../Item/Struct/ItemDT.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



bool UInventoryComponent::TryAddItemToInventory(FItemDT* ItemDT, int32 ToSlotIndex, TSubclassOf<AWorldItem> WorldItem) 
{
	if (WorldItem)
	{
		auto* ItemCDO = Cast<AWorldItem>(WorldItem->GetDefaultObject());
		if (ItemCDO)
		{
			FItemDT newItem(ItemCDO->ItemDT);
			MainInventoryItem.Add(MainInventoryItem.Num() - 1, newItem);
			//TArray<FMainInventorSlot> MainInventorySlot;
			//TMap<int32, FItemDT> MainInventoryItem;
			return true;
		}
	}
	else if(ItemDT)
	{
		FItemDT newItem(*ItemDT);
		MainInventoryItem.Add(MainInventoryItem.Num() - 1, newItem);
	}
	return false;
}