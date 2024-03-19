
// #include "Base/HUD/ScreenPart/W_PerkPanel.h"

#include "W_PerkPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"

#include "../../../Ability/AbilityComponent.h"

#include "../../../Ability/Struct/AbilityList.h"
#include "../../../Ability/AbilityDT.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"


#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"


void UW_PerkPanel::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_PerkPanel::NativeConstruct()
{
	Super::NativeConstruct();

	PerkPanelScroll->ClearChildren();
	SlotObj.Reset();

}


void UW_PerkPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}







void UW_PerkPanel::ShowPerkPanel(AUnit* _Unit)
{
	UpdatePerkPanel(_Unit);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}



void UW_PerkPanel::UpdatePerkPanel(AUnit* _Unit)
{

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->PerkPanelSlotSize;
	int32 slotsNumShownOnScreen = gameMode->PerkPanelVerticalSize / slotSize;
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = gameMode->MainInvertorySlotTexture;


	// ** Set Total Global-Invertory size
	PerkPanelSizeBox->bOverride_HeightOverride = 1;
	PerkPanelSizeBox->SetHeightOverride(gameMode->PerkPanelVerticalSize + slotSize / 5);
	PerkPanelSizeBox->bOverride_WidthOverride = 1;
	PerkPanelSizeBox->SetWidthOverride(slotSize + slotSize / 5);


	int32 SlotObjNum = SlotObj.Num();

	// ** Hide All Slot
	for (int32 i = 0; i < SlotObjNum; ++i)
	{
		SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
		SlotObj[i]->PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		SlotObj[i]->MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}


	// ** Assign Unit-Ability to Slot

	for(int32 i = 0; i < _Unit->Ability->UnitAbilityList.Num(); ++i)
	{
		FAbilityList& ability = _Unit->Ability->UnitAbilityList[i];

		if (i >= SlotObjNum)
		{
			AddCellToPerkPanel(gameMode, slotSize, SlotBackTexture);
			++SlotObjNum;
		}

		UAbilityDT* AbilityCDO = ability.Ability_class->GetDefaultObject<UAbilityDT>();

		UTexture2D* Image = AbilityCDO->GetImage();

		SlotObj[i]->SelectUnit = _Unit;

		SlotObj[i]->SetSlotParam(i,
			Image, SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			ESlotType::Perk_panel);		// ** Its Perk-Slot

		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden
	}


	// ** Holding slot selection
	if (_Unit->ContainerOfHoldingPermanent == ESlotType::Perk_panel &&
		_Unit->PermanentHoldingAbility >= 0)
		SlotObj[_Unit->PermanentHoldingAbility]->
			PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	if (_Unit->ContainerOfHoldingInstance == ESlotType::Perk_panel &&
		_Unit->InstantHoldingAbility >= 0)
		SlotObj[_Unit->InstantHoldingAbility]->
			MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));



}


void UW_PerkPanel::AddCellToPerkPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;
			ESlotType::Perk_panel);		// ** Its Perk-Slot

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		NewSlot->SetItemCount(0, 0, 0);	// ** Set slot-text (hide text)

		PerkPanelScroll->AddChild(NewSlot);
		SlotObj.Add(NewSlot);
	}
}