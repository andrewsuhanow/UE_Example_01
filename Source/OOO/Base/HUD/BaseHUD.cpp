

// #include "Base/HUD/SpectatorHUD.h"
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



void ABaseHUD::ShowInventory(UInventoryComponent* _Inventor, ABaseGameMode* _GameMode)
{
	Screen->ShowInventory(_Inventor, _GameMode);
}

void ABaseHUD::ShowLoot(UInventoryComponent* _LootInventor, ABaseGameMode* _GameMode)
{
	Screen->ShowLoot(_LootInventor, _GameMode);
}

void ABaseHUD::ShowEquipPanel(AUnit* _Unit)
{
	Screen->ShowEquipPanel(_Unit);
}
void ABaseHUD::ShowLootEquipPanel(AUnit* _Unit)
{
	Screen->ShowLootEquipPanel(_Unit);
}
void ABaseHUD::ShowFastPanel(AUnit* _Unit)
{
	Screen->ShowFastPanel(_Unit);
}
void ABaseHUD::ShowPerkPanel(AUnit* _Unit)
{
	Screen->ShowPerkPanel(_Unit);
}

void ABaseHUD::ShowWpnAttackPanel(AUnit* _Unit)
{
	Screen->ShowWpnAttackPanel(_Unit);
}
void ABaseHUD::ShowHealthPanel(AUnit* _Unit)
{
	Screen->ShowHealthPanel(_Unit);
}
void ABaseHUD::ShowWpnChangePanel(AUnit* _Unit)
{
	Screen->ShowWpnChangePanel(_Unit);
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
