
// #include "Base/Inventory/Widget/W_Screen.h"

#include "W_Screen.h"

#include "../../Unit/Base/Unit.h"

#include "../BaseHUD.h"

#include "../../Inventory/InventoryComponent.h"

/*


#include "W_Inventory_Cell_DROP.h"
#include "Inventory.h"
#include "W_Slot.h"
#include "Enum/EInvCell_Type.h"
//#include "../gr_TEST_Inventory/Inventory.h"
//#include "../gr_TEST_Inventory/Enum/EInvCell_Type.h"

//#include "../gr_TEST_Item/BaseItem.h"
#include "../gr_TEST_Item/Amunition.h"
*/

//---------------------------------------

#include "Components/Button.h"
/*
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"

#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

*/


//#include "../gr_TEST_AbilityComponent/AbilityDataAsset.h"

#include "Blueprint/WidgetBlueprintLibrary.h"   // UWidgetBlueprintLibrary::DetectDragIfPressed

//-----#include "Blueprint/WidgetTree.h"

#include "ScreenParts/W_Inventory.h"
#include "ScreenParts/W_GlobalInventory.h"
#include "ScreenParts/W_EquipPanel.h"
#include "ScreenParts/W_PerkPanel.h"
#include "ScreenParts/W_FastPanel.h"
#include "ScreenParts/W_HealthPanel.h"
#include "ScreenParts/W_WeaponPanel.h"
#include "ScreenParts/W_WeaponAttacksPanel.h"
#include "ScreenParts/W_TaskQueuePanel.h"
#include "ScreenParts/W_PosePanel.h"
#include "ScreenParts/W_AIPanel.h"
#include "ScreenParts/W_GroupPanel.h"
#include "ScreenParts/W_Map.h"
#include "ScreenParts/W_MenuPanel.h"


void UW_Screen::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UW_Screen::NativeConstruct()
{
	Super::NativeConstruct();


	InventorView->SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
	LootView->SetVisibility(ESlateVisibility::Collapsed);  					

	EquipPanelView->SetVisibility(ESlateVisibility::Collapsed);  			
	LootEquipPanelView->SetVisibility(ESlateVisibility::Collapsed);  		

	GlobalInventoryView->SetVisibility(ESlateVisibility::Collapsed);  		

	PerkPanelView->SetVisibility(ESlateVisibility::Collapsed);  			

	FastPanelView->SetVisibility(ESlateVisibility::Hidden);  				

	WeaponPanelView->SetVisibility(ESlateVisibility::Hidden);  				

	AttacksWpnPanelView->SetVisibility(ESlateVisibility::Hidden);

	TaskQueuePanelView->SetVisibility(ESlateVisibility::Hidden);  			



	//CCCCCCCC->SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
	

	//InvertorButton->OnReleased.AddDynamic(this, &ThisClass::ShowInventory);
	//EquipPanelButton->OnReleased.AddDynamic(this, &ThisClass::ShowEquipPanel);
}

void UW_Screen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}




void UW_Screen::ShowInventory(UInventoryComponent* _InventorObj, ABaseHUD* _HUD)
{
	InventorView->ShowInventory(_InventorObj);
}
void UW_Screen::ShowLoot(UInventoryComponent* _LootInventorObj, ABaseGameMode* _GameMode, ABaseHUD* _HUD)
{
	LootView->ShowInventory(_LootInventorObj);
}

void UW_Screen::ShowGlobalInventory(UInventoryComponent* _InventorObj, ABaseHUD* _HUD)
{
	GlobalInventoryView->ShowInventory(_InventorObj);
}

void UW_Screen::ShowEquipPanel(AUnit* _Unit, ABaseHUD* _HUD)
{
	EquipPanelView->ShowEquipPanel(_Unit);
}
void UW_Screen::ShowLootEquipPanel(AUnit* _LootUnit, ABaseHUD* _HUD)
{
	EquipPanelView->ShowEquipPanel(_LootUnit);
}


void UW_Screen::ShowFastPanel(AUnit* _FastPanelUnit, ABaseHUD* _HUD)
{
	FastPanelView->ShowFastPanel(_FastPanelUnit);
	_HUD->IsFastPanelShown = true;
}


void UW_Screen::ShowPerkPanel(AUnit* _Unit, ABaseGameMode* _GameMode, ABaseHUD* _HUD)
{
	PerkPanelView->ShowPerkPanel(_Unit, _GameMode);
}


void UW_Screen::ShowHealthPanel(AUnit* _Unit)
{

}


void UW_Screen::ShowWpnChangePanel(AUnit* _Unit,
	int32& _WeaponSlotIndex,
	ESlotType& _WeaponSlotType,
	UTexture2D*& _WeaponSlotTexture)
{
	WeaponPanelView->ShowWeaponPanel(_Unit, _WeaponSlotIndex,
		_WeaponSlotType, _WeaponSlotTexture);
}

void UW_Screen::HideWpnChangePanel()
{
	WeaponPanelView->SetVisibility(ESlateVisibility::Hidden);  		// ** Visible,  Hidden,  Collapsed
}

void UW_Screen::OpenWpnChangePanel(class AUnit* _Unit,
	TArray<int32>& _WeaponSlotsIndex,
	TArray<ESlotType>& _WeaponSlotsType,
	TArray<UTexture2D*>& _WeaponSlotsTexture)
{
	WeaponPanelView->OpenWpnChangePanel(_Unit, _WeaponSlotsIndex,
		 _WeaponSlotsType, _WeaponSlotsTexture);
}

void UW_Screen::CloseWpnChangePanel()
{
	WeaponPanelView->CloseWpnChangePanel();
}





void UW_Screen::ShowAttacksWpnPanel(AUnit* _Unit, 
	TArray<UTexture2D*>& _AttackIcon, int32& _SelectIndex, int32& _PermanentIndex)
{
	AttacksWpnPanelView->ShowAttacksWpnPanel(_Unit, _AttackIcon, 
		_SelectIndex, _PermanentIndex);
}

void UW_Screen::HideAttacksWpnPanel()
{
	AttacksWpnPanelView->HideAttacksWpnPanel();
}

void UW_Screen::UpdateAttacksWpnPanel(AUnit* _Unit, 
	TArray<UTexture2D*>& _AttackIcon, int32& _SelectIndex, int32& _PermanentIndex)
{
	AttacksWpnPanelView->UpdateAttacksWpnPanel(_Unit, _AttackIcon, 
		_SelectIndex, _PermanentIndex);
}




void UW_Screen::ShowTaskQueuePanel(AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
	TaskQueuePanelView->ShowTaskQueuePanel(_Unit, _CurrTaskIcon,
		_TasksIcon, _TasksIndex);
}

void UW_Screen::HideTaskQueuePanel()
{
	TaskQueuePanelView->HideTaskQueuePanel();
}

void UW_Screen::UpdateTaskQueuePanel(AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
	TaskQueuePanelView->UpdateTaskQueuePanel(_Unit, _CurrTaskIcon,
		_TasksIcon, _TasksIndex);
}




void UW_Screen::ShowPosePanel(AUnit* _Unit)
{

}
void UW_Screen::ShowAIPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowGroupPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowMapPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowMenuPanel(AUnit* _Unit)
{

}








/*

void UW_Screen::DrawInventory(AUnit* _Unit)
{
	Update();
}
void UW_Screen::DrawLoot(AUnit* _LootUnit)
{

}
void UW_Screen::HideInventory(AUnit* _Unit)
{

}
void UW_Screen::HideLoot(AUnit* _Unit)
{

}

void UW_Screen::UpdateInventory(AUnit* _Unit)
{

}
void UW_Screen::UpdateGlobalInventory(AUnit* _Unit)
{

}
void UW_Screen::UpdateEquipPanel(AUnit* _Unit)
{

}
void UW_Screen::UpdateFastPanel(AUnit* _Unit)
{

}
void UW_Screen::UpdatePerkPanel(AUnit* _Unit)
{

}
void UW_Screen::UpdateWeaponPanel(AUnit* _Unit)
{

}

*/


   