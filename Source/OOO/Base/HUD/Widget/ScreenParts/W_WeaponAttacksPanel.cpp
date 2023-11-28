
// #include "Base/HUD/ScreenPart/W_WeaponAttacksPanel.h"

#include "W_WeaponAttacksPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
//--------------#include "../../../Inventory/InventoryComponent.h"

#include "../../../Ability/AbilityComponent.h"
#include "../../../Ability/Enum/AbilityType.h"
#include "../../../Ability/Struct/AbilityDT.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"


#include "Components/HorizontalBox.h" 
#include "Components/SizeBox.h"
#include "Components/Image.h"


void UW_WeaponAttacksPanel::NativePreConstruct()
{
	Super::NativePreConstruct();

	//WeaponPanelScroll->SetOrientation(EOrientation::Orient_Horizontal);

}



void UW_WeaponAttacksPanel::NativeConstruct()
{
	Super::NativeConstruct();

	WeaponAttacksPanelGorzBox->ClearChildren();
	SlotObj.Reset();
}


void UW_WeaponAttacksPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}







void UW_WeaponAttacksPanel::ShowWeaponAttacksPanel(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	UpdateWeaponAttacksPanel(_Unit, _GameMode);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}

void UW_WeaponAttacksPanel::HideWeaponAttacksPanel()
{
	SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
}



void UW_WeaponAttacksPanel::UpdateWeaponAttacksPanel(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	float slotSize = _GameMode->FastPanelSlotSize;
	int32 fastPanelSlotNum = _GameMode->FastPanelSlotNum;
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = _GameMode->MainInvertorySlotTexture;

/*
	// ** Set Total Global-Invertory size
	WeaponPanelSizeBox->bOverride_HeightOverride = 1;
	WeaponPanelSizeBox->SetHeightOverride(_GameMode->PerkPanelVerticalSize);
	WeaponPanelSizeBox->bOverride_WidthOverride = 1;
	WeaponPanelSizeBox->SetWidthOverride(slotSize);
*/

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
			AddCellToWeaponAttacksPanel(_GameMode, slotSize, SlotBackTexture);
			++SlotObjNum;
		}

		UTexture2D* Image = It.Value.GetImage();

		SlotObj[currentItemSlot]->SetSlotParam(currentItemSlot,
			Image, SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_attacks_panel);	// ** Its weapon-Slot

		SlotObj[currentItemSlot]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden

		++currentItemSlot;
	}

}


void UW_WeaponAttacksPanel::AddCellToWeaponAttacksPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_attacks_panel);		// ** Its weapon-Slot

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		WeaponAttacksPanelGorzBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}