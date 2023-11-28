
// #include "Base/HUD/ScreenPart/W_EquipPanel.h"

#include "W_EquipPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
#include "../../../Amunition/WeaponComponent.h"
#include "../../../Amunition/WeaponWorldItem.h"
//------#include "../../../Inventory/InventoryComponent.h"

#include "../../../Item/Struct/ItemDT.h"
#include "../../../Amunition/WeaponDT.h"


#include "../../../Base/BaseGameMode.h"




#include "Components/Image.h"
#include "Components/SizeBox.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"













void UW_EquipPanel::NativePreConstruct()
{
	Super::NativePreConstruct();

	WeaponSlotsArray.Reset();







	
	WeaponSlotsArray.Add(contact_wpn_big_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_BigContactWpn);
	WeaponSlotsArray.Add(contact_wpn_small_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_SmallContactWpn);
	WeaponSlotsArray.Add(range_wpn_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_RangeWpn);
	WeaponSlotsArray.Add(pistol_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Pistol);

	for(int32 i = 0; i < WeaponSlotsArray.Num(); ++i)
		WeaponSlotsArray[i]->SetItemCount(0, 0, 0);

	ArmorSlotsArray.Add(cup_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Cup);
	ArmorSlotsArray.Add(armour_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Armor);
	ArmorSlotsArray.Add(clothes_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Clothes);
	ArmorSlotsArray.Add(collar_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Collar);
	ArmorSlotsArray.Add(braslet1_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Braslet);
	ArmorSlotsArray.Add(braslet2_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Braslet);
	ArmorSlotsArray.Add(ring1_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Ring);
	ArmorSlotsArray.Add(ring2_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Ring);
	ArmorSlotsArray.Add(ring3_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Ring);
	ArmorSlotsArray.Add(ring4_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_Ring);
	
	for (int32 i = 0; i < ArmorSlotsArray.Num(); ++i)
		ArmorSlotsArray[i]->SetItemCount(0, 0, 0);

	// ** WeaponSlotsArray.Add(heavy_gun_slot);
	// ** ArmorSlotsArray.Add(shield_slot);
	WeaponSlotsArray.Add(heavy_amunition_slot);
	ArmorSlotsArray.Add(heavy_amunition_slot);
	EquipSlotsDefaultTextureArray.Add(EquipPanelSlotTexture_HeavyStuff);
	heavy_amunition_slot->SetItemCount(0, 0, 0);



/*	heavy_amunition_slot->SzBox->bOverride_HeightOverride = 1;
	heavy_amunition_slot->SzBox->SetHeightOverride(heavy_amunition_slot->SlotWidth);
	heavy_amunition_slot->SzBox->bOverride_WidthOverride = 1;
	heavy_amunition_slot->SzBox->SetWidthOverride(heavy_amunition_slot->SlotWidth);
*/
	


	contact_wpn_big_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_BigContactWpn, false);
	contact_wpn_small_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_SmallContactWpn, false);
	range_wpn_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_RangeWpn, false);
	pistol_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Pistol, false);

	cup_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Cup, false);
	armour_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Armor, false);
	clothes_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Clothes, false);
	collar_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Collar, false);
	braslet1_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Braslet, false);
	braslet2_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Braslet, false);
	ring1_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Ring, false);
	ring2_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Ring, false);
	ring3_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Ring, false);
	ring4_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_Ring, false);

	heavy_amunition_slot->ImgItem->SetBrushFromTexture(EquipPanelSlotTexture_HeavyStuff, false);
}



void UW_EquipPanel::NativeConstruct()
{
	Super::NativeConstruct();


}


void UW_EquipPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}







void  UW_EquipPanel::ShowEquipPanel(class AUnit* _Unit)
{
	UpdateEquipPanel(_Unit);
	SetVisibility(ESlateVisibility::Visible);  			// ** Visible,  Hidden,  Collapsed
}


void UW_EquipPanel::UpdateEquipPanel(class AUnit* _Unit)
{

	// ** Get default param
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	UTexture2D* itemSlotTexture = nullptr;
	UTexture2D* mainInvertorySlotTexture = _Unit->MainInvertorySlotTexture;
	if (!mainInvertorySlotTexture)
		mainInvertorySlotTexture = gameMode->MainInvertorySlotTexture;



	// ** Weapon-Equip-Slot update



	/// ** hide all Weapon-Equip-Slot
	for (int32 i = 0; i < WeaponSlotsArray.Num(); ++i)
	{
		WeaponSlotsArray[i]->SetVisibility(ESlateVisibility::Collapsed);
		WeaponSlotsArray[i]->SelectorImage1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		//WeaponSlotsArray[si]->SelectorImage1->SetVisibility(ESlateVisibility::Hidden);
	}


	if (_Unit->WeaponComponent)
	{
		// ** find and assign New-Slot-Param
		int32 unitWeaponSlotsNum = _Unit->WeaponComponent->WeaponSlot.Num();
		for (int32 i = 0; i < unitWeaponSlotsNum; ++i)
		{
			// ** Get Current-Weapon-Slot (from Unit->WeaponComponent)
			AWeaponWorldItem* unitWeaponSlot = _Unit->WeaponComponent->WeaponSlot[i];

			int32 unitSlotIndex = -1;
			ESlotType toEquipSlotType = unitWeaponSlot->EquipSlotTypeFix;

			if (toEquipSlotType == ESlotType::hand_fight)
				continue;

			if (!unitWeaponSlot->ItemDT.IsSlotEmpty())// && unitWeaponSlot->ItemDT.WeaponDT)
			{				
				itemSlotTexture = unitWeaponSlot->ItemDT.GetOneSlotImage();
				unitSlotIndex = i;
			}


			// ** find matches W_slot wis Weapon and set
			SetEquipSlotParam(_Unit, toEquipSlotType, unitSlotIndex, mainInvertorySlotTexture, itemSlotTexture);
		}
	}


	// ** Armor-Equip-Slot update

	// --- @@@@@@
	// --- @@@@@@ ...
	// --- @@@@@@





	/// ** hide all Armor-Equip-Slot
	for (int32 i = 0; i < ArmorSlotsArray.Num(); ++i)
	{
		ArmorSlotsArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
}




void UW_EquipPanel::SetEquipSlotParam(class AUnit* _Unit, 
	ESlotType ToEquipSlotType, int32 unitSlotIndex,
	UTexture2D* _MainInvertorySlotTexture, 
	UTexture2D* _ItemSlotTexture)
{

	for (int32 si = 0; si < WeaponSlotsArray.Num(); ++si)
	{
		if (ToEquipSlotType == WeaponSlotsArray[si]->PanelTypeFix)
		{
			float theSaimSlotWidth = WeaponSlotsArray[si]->SlotWidth;
			float theSaimSlotHeight = WeaponSlotsArray[si]->SlotHeight;
			ESlotType dontChangeType = ESlotType::none;	// ** its EquipSlot here
			if (!_ItemSlotTexture)
				_MainInvertorySlotTexture = EquipSlotsDefaultTextureArray[si];

			WeaponSlotsArray[si]->SelectUnit = _Unit;

			WeaponSlotsArray[si]->SetSlotParam(unitSlotIndex,
				_ItemSlotTexture, _MainInvertorySlotTexture,
				theSaimSlotWidth, theSaimSlotHeight,
				theSaimSlotWidth, theSaimSlotHeight,
				0, 0,						// ** dont Translation;	
				dontChangeType);

			// ** set selected slot
			
			if (unitSlotIndex == _Unit->GetWeaponSlotSelected())
			{
				WeaponSlotsArray[si]->SelectorImage1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			}

			WeaponSlotsArray[si]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden
			return;
		}
	}
}



// -------------------------------
