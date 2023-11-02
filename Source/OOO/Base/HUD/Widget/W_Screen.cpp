
// #include "Base/Inventory/Widget/W_Screen.h"

#include "W_Screen.h"

#include "../../Unit/Base/Unit.h"

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
/*
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"

#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
*/


//#include "../gr_TEST_AbilityComponent/AbilityDataAsset.h"

#include "Blueprint/WidgetBlueprintLibrary.h"   // UWidgetBlueprintLibrary::DetectDragIfPressed

//-----#include "Blueprint/WidgetTree.h"

#include "ScreenParts/W_Inventory.h"
#include "ScreenParts/W_EquipPanel.h"
#include "ScreenParts/W_PerkPanel.h"
#include "ScreenParts/W_FastPanel.h"
#include "ScreenParts/W_HealthPanel.h"
#include "ScreenParts/W_WpnChangePanel.h"
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

}

void UW_Screen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}




void UW_Screen::ShowInventory(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	InventorView->ShowInventory(_Unit, _GameMode);
}
void UW_Screen::ShowLoot(AUnit* _LootUnit, ABaseGameMode* _GameMode)
{
	LootView->ShowInventory(_LootUnit, _GameMode);
}

void UW_Screen::ShowEquipPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowLootEquipPanel(AUnit* _LootUnit)
{

}
void UW_Screen::ShowFastPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowPerkPanel(AUnit* _Unit)
{

}

void UW_Screen::ShowWpnAttackPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowHealthPanel(AUnit* _Unit)
{

}
void UW_Screen::ShowWpnChangePanel(AUnit* _Unit)
{

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


   