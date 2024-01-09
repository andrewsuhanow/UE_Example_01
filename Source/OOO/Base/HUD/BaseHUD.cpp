

// #include "Base/HUD/BaseHUD.h"
#include "BaseHUD.h"

#include "Widget/W_Screen.h"

#include "../Base/BaseGameMode.h"
#include "../Base/BaseGameState.h"

#include "../Inventory/InventoryComponent.h"

#include "Widget/ScreenParts/W_Inventory.h"
// .. 
// .. 
// .. 
// .. 
// .. 



void ABaseHUD::SetDefaultGameParam(ABaseGameMode* _GameMode, ABaseGameState* _GameState)
{
	BGameMode = _GameMode;
	BGameState = _GameState;
}



bool ABaseHUD::Init(TSubclassOf<UW_Screen> W_Screen_Class)
{
	// *************************   W_Scene   ****************************

	if (!W_Screen_Class)
	{
		return false;
	}

	Screen = CreateWidget<UW_Screen>(GetWorld(), W_Screen_Class);
	if (Screen)
	{
		Screen->AddToViewport();
		return true;
	}

	return false;
}



void ABaseHUD::ShowInventory(UInventoryComponent* _Inventor)
{
	Screen->ShowInventory(_Inventor, this);
	IsInvertoryShown = true;
}

void ABaseHUD::ShowLoot(UInventoryComponent* _LootInventor, ABaseGameMode* _GameMode)
{
	Screen->ShowLoot(_LootInventor, _GameMode, this);
	IsLootInvertoryShown = true;
}

void ABaseHUD::ShowGlobalInventory(UInventoryComponent* _Inventor)
{
	Screen->ShowGlobalInventory(_Inventor, this);
	IsGlobalInvertoryShown = true;
}

void ABaseHUD::ShowEquipPanel(AUnit* _Unit)
{
	Screen->ShowEquipPanel(_Unit, this);
	IsEquipPanelShown = true;
}
void ABaseHUD::ShowLootEquipPanel(AUnit* _Unit)
{
	Screen->ShowLootEquipPanel(_Unit, this);
	IsLootEquipPanelShown = true;
}
void ABaseHUD::ShowFastPanel(AUnit* _Unit)
{
	Screen->ShowFastPanel(_Unit, this);
}
void ABaseHUD::ShowPerkPanel(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	Screen->ShowPerkPanel(_Unit, _GameMode, this);
	IsPerkPanelShown = true;
}


void ABaseHUD::ShowHealthPanel(AUnit* _Unit)
{
	Screen->ShowHealthPanel(_Unit);
}



void ABaseHUD::ShowWpnChangePanel(AUnit* _Unit,
	int32& _WeaponSlotIndex,
	ESlotType& _WeaponSlotType,
	UTexture2D*& _WeaponSlotTexture)
{
	Screen->ShowWpnChangePanel(_Unit, _WeaponSlotIndex, 
		_WeaponSlotType, _WeaponSlotTexture);
	IsWpnChangePanelShown = true;
}
void ABaseHUD::HideWpnChangePanel(AUnit* _Unit)
{
	Screen->HideWpnChangePanel();
	IsWpnChangePanelShown = false;
}

void ABaseHUD::OpenChangeWeaponPanel(AUnit* _Unit,
	TArray<int32>& _WeaponSlotsIndex,
	TArray<ESlotType>& _WeaponSlotsType,
	TArray<UTexture2D*>& _WeaponSlotsTexture)
{
	Screen->OpenWpnChangePanel(_Unit, _WeaponSlotsIndex,
		_WeaponSlotsType, _WeaponSlotsTexture);

	IsWpnChangePanelOpened = true;
}

void ABaseHUD::CloseChangeWeaponPanel()
{

	Screen->CloseWpnChangePanel();
	IsWpnChangePanelOpened = false;
}



void ABaseHUD::ShowAttacksWpnPanel(AUnit* _Unit,
	TArray<UTexture2D*>& _AttackIcon, int32 &_SelectIndex, int32 &_PermanentIndex)
{
	Screen->ShowAttacksWpnPanel(_Unit, _AttackIcon, _SelectIndex, _PermanentIndex);

	IsAttacksWpnPanelShown = true;
}

void ABaseHUD::HideAttacksWpnPanel()
{
	Screen->HideAttacksWpnPanel();
	IsAttacksWpnPanelShown = false;
}

void ABaseHUD::UpdateAttacksWpnPanel(AUnit* _Unit, 
	TArray<UTexture2D*>& _AttackIcon, int32& _SelectIndex, int32& _PermanentIndex)
{
	Screen->UpdateAttacksWpnPanel(_Unit, _AttackIcon, _SelectIndex, _PermanentIndex);
}



void ABaseHUD::ShowTaskQueuePanel(AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
	Screen->ShowTaskQueuePanel(_Unit, _CurrTaskIcon, _TasksIcon, _TasksIndex);
	IsTaskQueuePanelShowen = true;
}
void ABaseHUD::HideTaskQueuePanel()
{
	Screen->HideTaskQueuePanel();
	IsTaskQueuePanelShowen = false;
}


void ABaseHUD::UpdateTaskQueuePanel(AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
	Screen->UpdateTaskQueuePanel(_Unit, _CurrTaskIcon,
		_TasksIcon, _TasksIndex);
}



void ABaseHUD::ShowPosePanel(AUnit* _Unit)
{
	Screen->ShowPosePanel(_Unit);
}
void ABaseHUD::ShowAIPanel(AUnit* _Unit)
{
	Screen->ShowAIPanel(_Unit);
}
void ABaseHUD::ShowGroupPanel(AUnit* _Unit)
{
	Screen->ShowGroupPanel(_Unit);
}
void ABaseHUD::ShowMapPanel(AUnit* _Unit)
{
	Screen->ShowMapPanel(_Unit);
}
void ABaseHUD::ShowMenuPanel(AUnit* _Unit)
{
	Screen->ShowMenuPanel(_Unit);
}



// ** -------------------------------------------------------------------



