
// #include "Base/HUD/ScreenPart/W_FastPanel.h"

#include "W_FastPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
#include "../../../Ability/AbilityComponent.h"
#include "../../../Ability/AbilityDT.h"
//-----#include "../../../Inventory/InventoryComponent.h"

#include "../../../Unit/Struct/FastPanelSlot.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/HorizontalBox.h"
//#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"


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


void UW_FastPanel::HideFastPanel()
{
	SetVisibility(ESlateVisibility::Hidden);  				// ** Visible,  Hidden,  Collapsed
}



/*
void UW_FastPanel::SelectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent)
{
	if (_SlotIndex < 0 || _SlotIndex >= SlotObj.Num())
		return;

	if (_IsPermanent)
	{
		SlotObj[_SlotIndex]->PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SlotObj[_SlotIndex]->MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}



void UW_FastPanel::DeselectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent)
{
	if (_SlotIndex < 0 || _SlotIndex >= SlotObj.Num())
		return;

	if (_IsPermanent)
	{
		SlotObj[_SlotIndex]->PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		SlotObj[_SlotIndex]->MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}
}
*/



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

		int32 itemoOrAbilityIndexInContainer = _FastPanelUnit->FastPanelSlots[i].IndexInContainer;
		FName abilityName = _FastPanelUnit->FastPanelSlots[i].AbilityName;

		// ** Slot empty
		if (itemoOrAbilityIndexInContainer == -1)
		{
			/// ** Image = nullptr;
			indexInContainer = -1;
			SlotObj[i]->SetItemCount(0, 0, 0);	// ** Set slot-text (hide text)
			SlotObj[i]->SetBarProgress(0.f);
		}
		else if (itemoOrAbilityIndexInContainer < 0)
		{
			return;
		}
		// ** its Ability
		else if (abilityName != FName("none"))
		{
			TArray<FAbilityList>& AbilityList = _FastPanelUnit->Ability->UnitAbilityList;

			if (itemoOrAbilityIndexInContainer >= AbilityList.Num())
				return;

			TSubclassOf<UAbilityDT>& abilityClass = AbilityList[itemoOrAbilityIndexInContainer].Ability_class;
			if (abilityClass)
			{
				UAbilityDT* abilityCDO = abilityClass->GetDefaultObject<UAbilityDT>();
				if (abilityCDO)
				{
					Image = abilityCDO->GetImage();
					indexInContainer = i;
					SlotObj[i]->SetItemCount(0, 0, 0);
					SlotObj[i]->SetBarProgress(0.f);
				}
			}
		}

		// ** its Item 
		else
		{
			FItemDT* itemDT = _FastPanelUnit->FastPanelItem.Find(itemoOrAbilityIndexInContainer);
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

		SlotObj[i]->SetBarProgress(0.f);

		SlotObj[i]->PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		SlotObj[i]->MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));

		if (indexInContainer > unitFastPanelSlotNum)
			break;
	}

	if (_FastPanelUnit->ContainerOfHoldingPermanent == ESlotType::fast_panel &&
		_FastPanelUnit->PermanentHoldingAbility >= 0)
		SlotObj[_FastPanelUnit->PermanentHoldingAbility]->
		PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	if (_FastPanelUnit->ContainerOfHoldingInstance == ESlotType::fast_panel &&
		_FastPanelUnit->InstantHoldingAbility >= 0)
		SlotObj[_FastPanelUnit->InstantHoldingAbility]->
		MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
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