
// #include "Base/HUD/ScreenPart/W_FastPanel.h"

#include "W_FastPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
#include "../../../Ability/AbilityComponent.h"
#include "../../../Ability/Struct/AbilityDT.h"
//-----#include "../../../Inventory/InventoryComponent.h"

#include "../../../Unit/Struct/FastPanelSlot.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/HorizontalBox.h"
//#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"


void UW_FastPanel::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_FastPanel::NativeConstruct()
{
	Super::NativeConstruct();



	FastPanelHorizontalBox->ClearChildren();
	SlotObj.Reset();
}


void UW_FastPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}







void  UW_FastPanel::ShowFastPanel(AUnit* _FastPanelUnit)
{
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	UpdateFastPanel(_FastPanelUnit);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}



void UW_FastPanel::UpdateFastPanel(AUnit* _FastPanelUnit)
{

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->FastPanelSlotSize;
	int32 fastPanelSlotMaxNum = gameMode->FastPanelSlotNum;
	int32 unitFastPanelSlotNum = _FastPanelUnit->FastPanelSlots.Num();
	int32 SlotObjNum = SlotObj.Num();
	UTexture2D* SlotBackTexture = _FastPanelUnit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = gameMode->MainInvertorySlotTexture;

	// ** Add new slot (if need)
	while(SlotObjNum < fastPanelSlotMaxNum)
	{
		AddCellToFastPanel(gameMode, slotSize, SlotBackTexture);
		++SlotObjNum;
	}

	// ** Assign Unit-MAP<i, ItemDT> to Slot
	int32 indexInContainer = -1;
	for (int32 i = 0; i < fastPanelSlotMaxNum; ++i)
	{
		
		if (indexInContainer >= unitFastPanelSlotNum)	// ** if too many in unit Fast-Panel-Item
			return;

		UTexture2D* Image = nullptr;

		int32 itemIndexInMap = _FastPanelUnit->FastPanelSlots[i].IndexInContainer;
		EAbilityType abilType = _FastPanelUnit->FastPanelSlots[i].AbilityType;

		// ** Slot empty
		if (itemIndexInMap == -1)
		{
			/// ** Image = nullptr;
			indexInContainer = -1;
			SlotObj[i]->SetItemCount(0, 0, 0);	// ** Set slot-text (hide text)
		}

		// ** its Ability
		else if (abilType != EAbilityType::none)
		{
			FAbilityDT *abilRef = _FastPanelUnit->Ability->Abilities.Find(abilType);
			if (abilRef)
			{
				Image = abilRef->GetImage();
				indexInContainer = i;
				SlotObj[i]->SetItemCount(0, 0, 0);	
			}
		}

		// ** its Item 
		else
		{
			FItemDT* itemDT = _FastPanelUnit->FastPanelItem.Find(itemIndexInMap);
			if (itemDT)
			{
				Image = itemDT->GetOneSlotImage();
				indexInContainer = i;
				// ** Set slot-text (item count)
				int32 itemCount = itemDT->Count;
				int32 itemMaxCount = itemDT->CountMax;
				SlotObj[i]->SetItemCount(itemCount, itemMaxCount, slotSize / 6.f);
			}
		}

		SlotObj[i]->SelectUnit = _FastPanelUnit;

		SlotObj[i]->SetSlotParam(indexInContainer,
			Image, SlotBackTexture,
			slotSize, slotSize, 
			slotSize, slotSize, 
			0, 0,					// ** dont Translation;
			ESlotType::fast_panel);	// ** Its Fast-Slot


		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	



		if (indexInContainer > unitFastPanelSlotNum)
			break;
	}

}





void UW_FastPanel::AddCellToFastPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;		
			ESlotType::fast_panel);

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		FastPanelHorizontalBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}