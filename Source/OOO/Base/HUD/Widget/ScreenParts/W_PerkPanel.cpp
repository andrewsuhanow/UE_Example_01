
// #include "Base/HUD/ScreenPart/W_PerkPanel.h"

#include "W_PerkPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
//--------------#include "../../../Inventory/InventoryComponent.h"

#include "../../../Ability/AbilityComponent.h"
#include "../../../Ability/Enum/AbilityType.h"
#include "../../../Ability/Struct/AbilityDT.h"

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







void UW_PerkPanel::ShowPerkPanel(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	UpdatePerkPanel(_Unit, _GameMode);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}



void UW_PerkPanel::UpdatePerkPanel(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	float slotSize = _GameMode->PerkPanelSlotSize;
	int32 slotsNumShownOnScreen = _GameMode->PerkPanelVerticalSize / slotSize;
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = _GameMode->MainInvertorySlotTexture;


	// ** Set Total Global-Invertory size
	PerkPanelSizeBox->bOverride_HeightOverride = 1;
	PerkPanelSizeBox->SetHeightOverride(_GameMode->PerkPanelVerticalSize);
	PerkPanelSizeBox->bOverride_WidthOverride = 1;
	PerkPanelSizeBox->SetWidthOverride(slotSize);


	int32 SlotObjNum = SlotObj.Num();

	// ** Hide All Slot
	for (int32 i = 0; i < SlotObjNum; ++i)
	{
		SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
	}


	// ** Assign Unit-ItemDT to Slot
	int32  currentItemSlot = 0;
	for (const auto& It : _Unit->Ability->Abilities)
	{
		// ** TMap<EAbilityType, FAbilityDT> Abilities;
		// ** It.Key = EAbilityType;
		// ** It.Value = FAbilityDT;

		if (currentItemSlot >= SlotObjNum)
		{
			AddCellToPerkPanel(_GameMode, slotSize, SlotBackTexture);
			++SlotObjNum;
		}

		UTexture2D* Image = It.Value.GetImage();

		SlotObj[currentItemSlot]->SetSlotParam(currentItemSlot,
			Image, SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			ESlotType::Perk_panel);	// ** Its Perk-Slot

		SlotObj[currentItemSlot]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden

		++currentItemSlot;
	}

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

		PerkPanelScroll->AddChild(NewSlot);
		SlotObj.Add(NewSlot);
	}
}