


// #include "Base/Inventory/InventoryComponent.h"
#include "InventoryComponent.h"

#include "../Unit/Base/Unit.h"

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


void UInventoryComponent::Init()
{
	AUnit* UnitOwner = Cast<AUnit>(GetOwner());

	int32 mainInvCollNum = UnitOwner->GetMainInvCollNum();
	int32 fullRowNum = UnitOwner->FullRowNum;
	
	for (int32 i = MainInventorySlot.Num(); i < fullRowNum; ++i)
		AddSlotsRowToMainInventor(mainInvCollNum);
}


void UInventoryComponent::AddSlotsRowToMainInventor(int32 _MainInvCollNum)
{
	int32 mainInventorySlotNum = MainInventorySlot.Num();

	for (int32 i = mainInventorySlotNum; i < _MainInvCollNum + mainInventorySlotNum; ++i)
	{
		int32 SlotIndex = i;
		int32 ItemInMapIndexKEY = -1;
		MainInventorySlot.Add(FMainInventorSlot(SlotIndex, ItemInMapIndexKEY));
	}
}




bool UInventoryComponent::CheckItemCollision(const AUnit* UnitOwner, const FItemDT* ItemDT, int32 _Position)
{

	int32 mainInventorySlotNum = MainInventorySlot.Num();
	if (_Position > mainInventorySlotNum)
		return false;


	int32 itemInvertorWidth = ItemDT->GetItemHorizontalSize();		// ** Item.X 
	int32 ItemInvertorHeight = ItemDT->GetItemVerticalSize();		// ** Item.Y
	int32 mainInvCollNum = UnitOwner->GetMainInvCollNum();
	int32 mainInvRowNum = UnitOwner->GetMainInvRowNum();


	// ** Check Right border
	float positionInLastRow = _Position % mainInvCollNum;			// ** Get NumPosition in Current Row
	float restInRow = (mainInvCollNum - positionInLastRow);
	if (itemInvertorWidth > restInRow)  							// ** check Right collision
		return false;	// ** can't Add

	// ** Check Bottom border
	float CurrRowNum = _Position / mainInvCollNum;					// ** get current row
	bool isCollidedBotton = false;
	if (UnitOwner->FullRowNum > (CurrRowNum + ItemInvertorHeight))	// ** check bottom collision
		isCollidedBotton = true;
	if (UnitOwner->IsInventorSizeFixed && !isCollidedBotton)		// ** check invertor bottom fixation
		return false;	// ** can't Add



	// ** Check all Curr-Item points
	for (int32 W = 0; W < itemInvertorWidth; ++W)
		for (int32 H = 0; H < ItemInvertorHeight; ++H)
		{
			int32 CheckedIndex = _Position + W + H * mainInvCollNum;
			if (CheckedIndex >= mainInventorySlotNum)					// ** if pos under bottom
				continue;
			if(MainInventorySlot[CheckedIndex].ItemPosIndex >= 0)		// ** Check slot empty?
				return false;	// ** can't Add
		}

	return true;
}



bool UInventoryComponent::TryAddItemToInventory(FItemDT* ItemDT, int32 ToSlotIndex, TSubclassOf<AWorldItem> WorldItem) 
{
	FItemDT newItemDT;

	// ** SubclassOf 
	if (WorldItem)
	{
		auto* ItemCDO = Cast<AWorldItem>(WorldItem->GetDefaultObject());
		if (ItemCDO)
			newItemDT = ItemCDO->ItemDT;
	}
	// ** ItemDT
	else if(ItemDT)
	{
		newItemDT = *ItemDT;
	}

	AUnit* unit = Cast<AUnit>(GetOwner());
	int32 mainInventorySlotNum = MainInventorySlot.Num();

	// ** Add to any slot
	if (ToSlotIndex == -1)
	{
		// ** check each Slot 
		for (ToSlotIndex = 0; ToSlotIndex < mainInventorySlotNum; ++ToSlotIndex)
		{

			bool isSlotCollisionFree = CheckItemCollision(unit, &newItemDT, ToSlotIndex);
			if (isSlotCollisionFree)
			{
				// Item Map-Array
				MainInventoryItem.Add(ToSlotIndex, newItemDT);

				// ** Other item slot
				int32 mainInvCollNum = unit->GetMainInvCollNum();
				for (int32 Hor = 0; Hor < newItemDT.GetItemHorizontalSize(); ++Hor)
					for (int32 Wert = 0; Wert < newItemDT.GetItemVerticalSize(); ++Wert)
					{
						int32 ChangingSlotIndex = ToSlotIndex + Hor + Wert * mainInvCollNum;
						if (ChangingSlotIndex >= mainInventorySlotNum)
						{
							AddSlotsRowToMainInventor(mainInvCollNum);
							AddSlotsRowToMainInventor(mainInvCollNum);
							mainInventorySlotNum = MainInventorySlot.Num();
						}
						MainInventorySlot[ChangingSlotIndex].CurrSlotIndex = ChangingSlotIndex;
						MainInventorySlot[ChangingSlotIndex].ItemPosIndex = ToSlotIndex;
					}
				return true;
			}
		}
	}
	// ** Add to Slot NUM: "ToSlotIndex"
	else
	{
		bool isSlotCollisionFree = CheckItemCollision(unit, &newItemDT, ToSlotIndex);							
		if (isSlotCollisionFree)
		{
			// Item Map-Array
			MainInventoryItem.Add(ToSlotIndex, newItemDT);													// ---@@---  double text FIX

			// ** Other item slot
			int32 mainInvCollNum = unit->GetMainInvCollNum();
			for (int32 Hor = 0; Hor < ItemDT->GetItemHorizontalSize(); ++Hor)								// ---@@---  double text FIX
				for (int32 Wert = 0; Wert < ItemDT->GetItemVerticalSize(); ++Wert)							// ---@@---  double text FIX
				{
					int32 ChangingSlotIndex = ToSlotIndex + Hor + Wert * mainInvCollNum;
					if (ChangingSlotIndex >= mainInventorySlotNum)
					{
						AddSlotsRowToMainInventor(mainInvCollNum);
						AddSlotsRowToMainInventor(mainInvCollNum);
						mainInventorySlotNum = MainInventorySlot.Num();
					}
					MainInventorySlot[ToSlotIndex + Hor + Wert].CurrSlotIndex = ToSlotIndex + Hor + Wert;	// ---@@---  double text FIX
					MainInventorySlot[ToSlotIndex + Hor + Wert].ItemPosIndex = ToSlotIndex;					// ---@@---  double text FIX
				}
			return true;
		}
	}
	return false;
}