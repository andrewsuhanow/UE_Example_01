
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







void UW_WeaponAttacksPanel::ShowAttacksWpnPanel(AUnit* _Unit, 
	TArray<UTexture2D*>& _AttackIcon, int32& _SelectIndex, int32& _PermanentIndex)
{
	UpdateAttacksWpnPanel(_Unit, _AttackIcon, _SelectIndex, _PermanentIndex);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}


void UW_WeaponAttacksPanel::HideAttacksWpnPanel()
{
	SetVisibility(ESlateVisibility::Collapsed);  			// ** Visible,  Hidden,  Collapsed
}



void UW_WeaponAttacksPanel::UpdateAttacksWpnPanel(AUnit* _Unit, 
	TArray<UTexture2D*>& _AttackIcon, int32& _SelectIndex, int32& _PermanentIndex)
{
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->FastPanelSlotSize;
	int32 weaponAttacksPanelSlotNum = gameMode->WeaponAttacksPanelSlotNum;
	int32 currWeaponAttacksNum = _AttackIcon.Num();
	UTexture2D* slotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!slotBackTexture)
		slotBackTexture = gameMode->MainInvertorySlotTexture;


	int32 SlotObjNum = SlotObj.Num();


	// ** Add new slot (if need)
	while (SlotObjNum < weaponAttacksPanelSlotNum)
	{
		AddCellToWeaponAttacksPanel(gameMode, slotSize, slotBackTexture);
		++SlotObjNum;
	}
	

	// ** Hide All Slot
	for (int32 i = 0; i < SlotObjNum; ++i)
	{
		SlotObj[i]->SetSlotParam(-1,	// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, slotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_attacks_panel);		
	}


	// ** Assign Unit-ItemDT to Slot
	int32 actualAttackNum = FMath::Min(weaponAttacksPanelSlotNum, currWeaponAttacksNum);
	for (int32 i = 0; i < actualAttackNum; ++i)
	{

		SlotObj[i]->SetSlotParam(i,		// ** link to attack-index 
			_AttackIcon[i], slotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_attacks_panel);		
	}

}



void UW_WeaponAttacksPanel::AddCellToWeaponAttacksPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* _SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, _SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_attacks_panel);		// ** Its weapon-Slot

		NewSlot->SetItemCount(0, 0, 0);	// ** Set slot-text (hide text)

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		WeaponAttacksPanelGorzBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}