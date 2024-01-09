
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"



#include "W_Screen.generated.h"

/*
class UVerticalBox;  //#include "Components/VerticalBox.h"
class UHorizontalBox;  //#include "Components/HorizontalBox.h"
class UScrollBox;
class USizeBox;
class UBorder;
class UCanvasPanel;		// #include "Components/CanvasPanel.h"
class UButton;    // #include "Components/Button.h"
//class UUniformGridPanel;  // #include "Components/UniformGridPanel.h"
*/


UCLASS()
class OOO_API UW_Screen : public UUserWidget
{
	GENERATED_BODY()
	
 


public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;


	     
public:

// *************************    Init    ***************************

	UFUNCTION()		void ShowInventory(class UInventoryComponent* _InventorObj, class ABaseHUD* _HUD);
	UFUNCTION()		void ShowLoot(class UInventoryComponent* _LootInventorObj, ABaseGameMode* _GameMode, class ABaseHUD* _HUD);
	UFUNCTION()		void ShowGlobalInventory(class UInventoryComponent* _InventorObj, class ABaseHUD* _HUD);
	UFUNCTION()		void ShowEquipPanel(class AUnit* _LootUnit, class ABaseHUD* _HUD);
	UFUNCTION()		void ShowLootEquipPanel(class AUnit* _LootUnit, class ABaseHUD* _HUD);

	UFUNCTION()		void ShowFastPanel(class AUnit* _FastPanelUnit, class ABaseHUD* _HUD);

	UFUNCTION()		void ShowPerkPanel(class AUnit* _Unit, class ABaseGameMode* _GameMode, class ABaseHUD* _HUD);

	UFUNCTION()		void ShowHealthPanel(class AUnit* _LootUnit);


	UFUNCTION()		void ShowWpnChangePanel(class AUnit* _Unit,
											int32& _WeaponSlotIndex,
											ESlotType& _WeaponSlotType,
											UTexture2D*& _WeaponSlotTexture);
	UFUNCTION()		void HideWpnChangePanel();
	UFUNCTION()		void OpenWpnChangePanel(class AUnit* _Unit,
											TArray<int32>& _WeaponSlotsIndex,
											TArray<ESlotType>& _WeaponSlotsType,
											TArray<UTexture2D*>& _WeaponSlotsTexture);
	UFUNCTION()		void CloseWpnChangePanel();


	UFUNCTION()		void ShowAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon,
											int32& _SelectIndex, int32& _PermanentIndex);
	UFUNCTION()		void HideAttacksWpnPanel();
	UFUNCTION()		void UpdateAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon,
											int32& _SelectIndex, int32& _PermanentIndex);


	UFUNCTION()		void ShowTaskQueuePanel(class AUnit* _Unit,
											UTexture2D*& _CurrTaskIcon,
											TArray<UTexture2D*>& _TasksIcon,
											TArray<int32>& _TasksIndex);
	UFUNCTION()		void HideTaskQueuePanel();
	UFUNCTION()		void UpdateTaskQueuePanel(class AUnit* _Unit,
											UTexture2D*& _CurrTaskIcon,
											TArray<UTexture2D*>& _TasksIcon,
											TArray<int32>& _TasksIndex);



	UFUNCTION()		void ShowPosePanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowAIPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowGroupPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowMapPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowMenuPanel(class AUnit* _LootUnit);



	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_Inventory* InventorView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_Inventory* LootView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_GlobalInventory* GlobalInventoryView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_EquipPanel* EquipPanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_EquipPanel* LootEquipPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_FastPanel* FastPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_PerkPanel* PerkPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_WeaponPanel* WeaponPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_WeaponAttacksPanel* AttacksWpnPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_TaskQueuePanel* TaskQueuePanelView;


	// ---------------------------


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UButton* InvertorButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UButton* EquipPanelButton;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_PerkPanel* PerkPanelView;

	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_FastPanel* WpnAttackPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_HealthPanel* HealthPanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_WpnChangePanel* WpnChangePanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_PosePanel* PosePanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_AIPanel* AIPanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_GroupPanel* GroupPanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_Map* MapView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_MenuPanel* MenuPanelView;
*/







};
