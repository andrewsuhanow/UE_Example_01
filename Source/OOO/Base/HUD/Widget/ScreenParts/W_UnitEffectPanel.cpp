
// #include "Base/HUD/ScreenPart/W_UnitEffectPanel.h"

#include "W_UnitEffectPanel.h"

//-----#include "../Slot/W_EffectSlot.h"
#include "../Slot/W_Slot.h"
//------------#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
//------#include "../../../Ability/AbilityComponent.h"
//------------#include "../../../Ability/AbilityDT.h"

#include "../../../UnitEffect/Struct/UnitEffectSlotDT.h"


//-----------#include "../../../Unit/Struct/FastPanelSlot.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"


void UW_UnitEffectPanel::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_UnitEffectPanel::NativeConstruct()
{
	Super::NativeConstruct();



	ScrollBox_EffectPanel->ClearChildren();
	SlotObj.Reset();
}


void UW_UnitEffectPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}







void  UW_UnitEffectPanel::ShowEffectPanel(AUnit* _Unit)
{
	//----------ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	UpdateEffectPanel(_Unit);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}


void UW_UnitEffectPanel::HideEffectPanel()
{
	SetVisibility(ESlateVisibility::Hidden);  				// ** Visible,  Hidden,  Collapsed
}








void UW_UnitEffectPanel::UpdateEffectPanel(AUnit* _Unit)
{

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->UnitEffectIconSize;
	int32 currEffectsNum = _Unit->CurrUnitEffectSlots.Num();
	int32 SlotObjNum = SlotObj.Num();
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = gameMode->MainInvertorySlotTexture;

	// ** Add new slot (if need)
	while(SlotObjNum < currEffectsNum)
	{
		AddCellToEffectPanel(gameMode, slotSize, SlotBackTexture);
		++SlotObjNum;
	}


	// ** Hide All

	for (int32 i = 0; i < SlotObjNum; ++i)
	{
		SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden	
	}


	// ** Unit->CurrUnitEffectSlots   // ** FUnitEffectSlotDT

	for (int32 i = 0; i < currEffectsNum; ++i)
	{

		SlotObj[i]->SelectUnit = _Unit;

		UTexture2D* Image = _Unit->CurrUnitEffectSlots[i].EffectImage;
		
		SlotObj[i]->SetSlotParam(i,
			Image, SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,					// ** dont Translation;
			ESlotType::unit_effect);// ** Its unit_effect


		SlotObj[i]->SetItemCount(0, 0, 0);
		

		if (_Unit->CurrUnitEffectSlots[i].FullRoundDuration == ONGOING)
		{
			SlotObj[i]->SetProgressVisibility(false);
		}
		else
		{
			SlotObj[i]->SetProgressVisibility(true);

			SlotObj[i]->SetBarProgress(
				_Unit->CurrUnitEffectSlots[i].UnitParamModifier[0].ModifierType,
				_Unit->CurrUnitEffectSlots[i].FullRoundDuration);
		}


		SlotObj[i]->SetVisibility(ESlateVisibility::Visible);

	}



/*
		UTexture2D* Image = nullptr;

		int32 itemIndexInMap = _Unit->FastPanelSlots[i].IndexInContainer;
		FName abilityName = _Unit->FastPanelSlots[i].AbilityName;

		// ** Slot empty
		if (itemIndexInMap == -1)
		{
			/// ** Image = nullptr;
			indexInContainer = -1;
			SlotObj[i]->SetItemCount(0, 0, 0);	// ** Set slot-text (hide text)
		}

		// ** its Ability
		else if (abilityName != FName("none"))
		{
			//FAbilityDT *abilRef = _Unit->Ability->Abilities.Find(abilType);
			UAbilityDT* abilityCDO = nullptr;
			TSubclassOf<UAbilityDT> *abilityClass = _Unit->Ability->Abilities.Find(abilityName);
			if (abilityClass)
			{
				abilityCDO = (*abilityClass)->GetDefaultObject<UAbilityDT>();
				if (abilityCDO)
				{
					Image = abilityCDO->GetImage();
					indexInContainer = i;
					SlotObj[i]->SetItemCount(0, 0, 0);	
				}
			}			
		}

		// ** its Item 
		else
		{
			FItemDT* itemDT = _Unit->FastPanelItem.Find(itemIndexInMap);
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

		SlotObj[i]->SelectUnit = _Unit;

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
*/
}





void UW_UnitEffectPanel::AddCellToEffectPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);
	

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;		
			ESlotType::unit_effect);

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		ScrollBox_EffectPanel->AddChild(NewSlot);
		SlotObj.Add(NewSlot);
	}
}