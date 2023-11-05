
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

	UFUNCTION()		void ShowInventory(class UInventoryComponent* _Inventor, class ABaseGameMode* _GameMode);
	UFUNCTION()		void ShowLoot(class UInventoryComponent* _Inventor, ABaseGameMode* _GameMode);
	UFUNCTION()		void ShowEquipPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowLootEquipPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowFastPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowPerkPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowWpnAttackPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowHealthPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowWpnChangePanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowPosePanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowAIPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowGroupPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowMapPanel(class AUnit* _LootUnit);
	UFUNCTION()		void ShowMenuPanel(class AUnit* _LootUnit);




	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_Inventory* InventorView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_Inventory* LootView;
 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_EquipPanel* EquipPanelView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_EquipPanel* LootEquipPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_PerkPanel* PerkPanelView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		class UW_FastPanel* FastPanelView;
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
