


// #include "Base/Inventory/InventoryComponent.h"
#include "InventoryComponent.h"

#include "../Unit/Base/Unit.h"

#include "../Base/BaseGameMode.h"

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
	

	//SetDefaultGlobalInv();


	for (int32 i = MainInventorySlot.Num(); i < fullRowNum; ++i)
		AddSlotsRowToMainInventor(mainInvCollNum);
}





// **************************************************************************************************	
// ***************************************    Main_Inventory    *************************************



bool UInventoryComponent::TryAddItemToMainInventory(FItemDT* ItemDT, int32 ToSlotIndex, TSubclassOf<AWorldItem> WorldItem, bool ForseAdd)
{
 
	// ****  Get Item-Data

	AUnit* unit = Cast<AUnit>(GetOwner());
	int32 mainInvSlotsNum = MainInventorySlot.Num();
	FItemDT newItemDT;
	/// ** SubclassOf 
	if (WorldItem)
	{
		auto* ItemCDO = Cast<AWorldItem>(WorldItem->GetDefaultObject());
		if (ItemCDO)
			newItemDT = ItemCDO->ItemDT;
	}
	/// ** ItemDT
	else if (ItemDT)
		newItemDT = *ItemDT;
	


	// **** Add to any slot

	if (ToSlotIndex == -1)
	{
		// ** check each Slot on stackablest
		for (ToSlotIndex = 0; ToSlotIndex < mainInvSlotsNum; ++ToSlotIndex)
		{
			int32 indexInMap = MainInventorySlot[ToSlotIndex].ItemPosIndex;
			FItemDT* itemDT_under = MainInventoryItem.Find(indexInMap);
			if (itemDT_under)
				if (itemDT_under->IsItemStackable() && *itemDT_under == newItemDT)
				{
					if (AddStackableItemInMainInv(&newItemDT, itemDT_under))
						return true;
					else
						continue;
				}
		}

		// ** check each Slot 
		for (ToSlotIndex = 0; ToSlotIndex < mainInvSlotsNum; ++ToSlotIndex)
		{
			if (CheckItemCollision(unit, &newItemDT, ToSlotIndex))
			{
				AddItemToMainInventoryArray(unit, &newItemDT, ToSlotIndex, mainInvSlotsNum);
				return true;
			}
		}
	}


	// **** Add to Slot-Index
	else
	{
		if (ToSlotIndex >= MainInventorySlot.Num())
			return false;	/// ** incorrect index

		//-------------bool isSlotEmpty = (-1 == MainInventorySlot[ToSlotIndex].ItemPosIndex);
		int32 itemIndexInMap = MainInventorySlot[ToSlotIndex].ItemPosIndex;
		FItemDT* itemDT_under = itemDT_under = MainInventoryItem.Find(itemIndexInMap);

		// ** Slot is not empty
		if (itemDT_under)
		{
			// ** Test and try Add() if Stackable
			if (itemDT_under->IsItemStackable() && *itemDT_under == newItemDT)
			{
				if (AddStackableItemInMainInv(&newItemDT, itemDT_under))
					return true;
				else if (TryAddItemToMainInventory(&newItemDT, -1, nullptr))
					return true;
				else
				{
					// ** 
					// ** 
					// ** 
					// ** Drop item or set in last
					ItemDT->Count = newItemDT.Count;
					// ** 
					// ** 
					// ** 
				}
			}


			if (!ForseAdd)
				return false;


			// ** remove Under-item(temporare) from Slots-Array (not from Map-Array)
			// ** it maight resume back (if)
			bool eraseItemIndexes = true;
			AssignItemIndexesToMainInvSlots(unit, itemDT_under, itemIndexInMap, mainInvSlotsNum, false, eraseItemIndexes);

		}

		bool isSlotCollisionFree = CheckItemCollision(unit, &newItemDT, ToSlotIndex);
		if (isSlotCollisionFree)
		{
			// ** Remove Under-item and Add new-Item 
			MainInventoryItem.Remove(itemIndexInMap);
			AddItemToMainInventoryArray(unit, &newItemDT, ToSlotIndex, mainInvSlotsNum);
			return true;
		}
		else if (itemDT_under)
		{
			// ** resume Under-item to SlotsArray (it stil placed in Map-Array)
			bool eraseItemIndexes = false;
			AssignItemIndexesToMainInvSlots(unit, itemDT_under, itemIndexInMap, mainInvSlotsNum, false, eraseItemIndexes);
		}
	}
	return false;
}




bool UInventoryComponent::IsMainInventorySlotEmpty(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MainInventorySlot.Num())
		return true;

	if (MainInventorySlot[SlotIndex].ItemPosIndex == -1)
		return true;

	return false;
}

FItemDT* UInventoryComponent::GetItemRefFromMainInventory(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MainInventorySlot.Num())
		return nullptr;

	int32 indexInItemsMap = MainInventorySlot[SlotIndex].ItemPosIndex;
	if (indexInItemsMap != -1)
	{
		return MainInventoryItem.Find(indexInItemsMap);
	}
	
	return nullptr;
}

void UInventoryComponent::RemoveItemFromMainInventory(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MainInventorySlot.Num())
		return;

	ABaseGameMode* GameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	int32 mainInvCollNum = GameMode->MainInvCollNum;

	int32 indexInItemsMap = MainInventorySlot[SlotIndex].ItemPosIndex;
	FItemDT* ItemDT = MainInventoryItem.Find(indexInItemsMap);
	if (ItemDT)
	{
		for (int32 Hor = 0; Hor < ItemDT->GetItemHorizontalSize(); ++Hor)
		{
			for (int32 Wert = 0; Wert < ItemDT->GetItemVerticalSize(); ++Wert)
			{
				int32 SlotIndexForRemove = indexInItemsMap + Hor + Wert * mainInvCollNum;
				MainInventorySlot[SlotIndexForRemove].ItemPosIndex = -1;
			}
		}
	}

	MainInventoryItem.Remove(indexInItemsMap);
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




void UInventoryComponent::AddItemToMainInventoryArray(AUnit* _Unit, const FItemDT* ItemDT, 
														int32 ToSlotIndex, int32& MainInvSlotsNum)
{
	// ** Add Item to Map-Array
	MainInventoryItem.Add(ToSlotIndex, *ItemDT);

	// ** Add Item to Slot-Array
	bool isCanAddNewSlots = true;
	AssignItemIndexesToMainInvSlots(_Unit, ItemDT, ToSlotIndex, MainInvSlotsNum, isCanAddNewSlots);
}


void UInventoryComponent::AssignItemIndexesToMainInvSlots(AUnit* _Unit, const FItemDT* ItemDT, 
							int32 FirstSlotIndex, int32& MainInvSlotsNum, bool IsCanAddNewSlots, bool IsItemErase)
{
	int32 horizontalSize = ItemDT->GetItemHorizontalSize();
	int32 verticalSize = ItemDT->GetItemVerticalSize();

	int32 mainInvCollNum = _Unit->GetMainInvCollNum();

	int32 newIndexSet = (IsItemErase ? -1 : FirstSlotIndex);

	// ** All item slots
	for (int32 Hor = 0; Hor < horizontalSize; ++Hor)
		for (int32 Wert = 0; Wert < verticalSize; ++Wert)
		{
			int32 ChangingSlotIndex = FirstSlotIndex + Hor + Wert * mainInvCollNum;

			if (IsCanAddNewSlots && ChangingSlotIndex >= MainInvSlotsNum)
			{
				// ** add 2 slot-rows to mainInventory  (if need)
				AddSlotsRowToMainInventor(mainInvCollNum);
				AddSlotsRowToMainInventor(mainInvCollNum);
				MainInvSlotsNum = MainInventorySlot.Num();
			}

			// ** MainInventorySlot[ChangingSlotIndex].CurrSlotIndex = ChangingSlotIndex;
			MainInventorySlot[ChangingSlotIndex].ItemPosIndex = newIndexSet;
		}
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

bool UInventoryComponent::AddStackableItemInMainInv(FItemDT* _FromItemDT, FItemDT* _ToItemDT)
{
	int32 FreeGapeToAddStack = _ToItemDT->CountMax - _ToItemDT->Count;

	if (FreeGapeToAddStack > 0)
		// ** Add to stack (contain full)
		if (_FromItemDT->Count <= FreeGapeToAddStack)
		{
			_ToItemDT->Count += _FromItemDT->Count;
			return true;
		}

		// ** Has a rest. Add to other stack or... new slot
		else
		{
			_ToItemDT->Count = _ToItemDT->CountMax;
			_FromItemDT->Count -= FreeGapeToAddStack;

			//TryAddItemToMainInventory(_FromItemDT, -1, nullptr, false);
			return false;
		}

	return false;
}


// ****************************************************************************************************	
// ***************************************    Global_Inventory    *************************************

void UInventoryComponent::AddItemToGlobalInventory(FItemDT* ItemDT, int32 ToSlotIndex)
{
	if (!ItemDT)
		return;

	if (GlobalInvItemSlot.Num() <= ToSlotIndex)
	{
		// ** Add to next new index
		ToSlotIndex = -1;  
	}

	FItemDT newItemDT = (*ItemDT);

	// ** Add to existing Stack
	if (ToSlotIndex == -1)
		for (int32 i = 0; i < GlobalInvItemSlot.Num(); ++i)
		{
			if (AddStackableItemInGlobalInv(&newItemDT, i, ToSlotIndex))
				return;
		}
	
	// ** App-End
	if (ToSlotIndex < 0)
	{
		GlobalInvItemSlot.Add(newItemDT);
	}
	// ** Add to index (betwean items)
	else
	{
		int32 nextSlotIndex = -1;
		if (AddStackableItemInGlobalInv(&newItemDT, ToSlotIndex, nextSlotIndex))
			return;
		
		GlobalInvItemSlot.Insert(newItemDT, ToSlotIndex);
	}
}



bool UInventoryComponent::IsGlobalInventorySlotEmpty(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= GlobalInvItemSlot.Num())
		return true;

	return GlobalInvItemSlot[SlotIndex].IsSlotEmpty();
}

FItemDT* UInventoryComponent::GetItemRefFromGlobalInventory(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= GlobalInvItemSlot.Num())
		return nullptr;

	if (false == GlobalInvItemSlot[SlotIndex].IsSlotEmpty())
	{
		return &GlobalInvItemSlot[SlotIndex];
	}

	return nullptr;
}

void UInventoryComponent::RemoveItemFromGlobalInventory(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= GlobalInvItemSlot.Num())
		return;

	if (false == GlobalInvItemSlot[SlotIndex].IsSlotEmpty())
	{
		GlobalInvItemSlot.RemoveAt(SlotIndex);
	}
}




bool UInventoryComponent::AddStackableItemInGlobalInv(FItemDT* _ItemDT, int32 _SlotIndex, int32 _NextSlotIndex)
{
	if (GlobalInvItemSlot[_SlotIndex] == *_ItemDT)
		if (GlobalInvItemSlot[_SlotIndex].IsItemStackable())
		{
			int32 FreeGapeToAddStack = GlobalInvItemSlot[_SlotIndex].CountMax - GlobalInvItemSlot[_SlotIndex].Count;

			if (FreeGapeToAddStack > 0)
				// ** Add to stack (contain full)
				if (_ItemDT->Count <= FreeGapeToAddStack)
				{
					GlobalInvItemSlot[_SlotIndex].Count += _ItemDT->Count;
					return true;
				}

				// ** Has a rest. Add to other stack or... new slot
				else
				{
					GlobalInvItemSlot[_SlotIndex].Count = GlobalInvItemSlot[_SlotIndex].CountMax;
					_ItemDT->Count -= FreeGapeToAddStack;

					AddItemToGlobalInventory(_ItemDT, _NextSlotIndex);
					return true; 
				}
		}
	return false;
}