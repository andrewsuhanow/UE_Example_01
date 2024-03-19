
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"


UCLASS()
class OOO_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	






public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseGameMode* BGameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseGameState* BGameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ASpectator* Spectator;

	UFUNCTION()		bool Init(TSubclassOf<class UW_Screen> W_Screen_Class);
	UFUNCTION()		void SetDefaultGameParam(class ABaseGameMode* _GameMode, 
		class ABaseGameState* _GameState, class ASpectator* _Spectator);

public:

// *************************   W_Screen   ****************************

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class UW_Screen* Screen;
	
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowInventory(class UInventoryComponent* _Inventor);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowLoot(class UInventoryComponent* _Inventor, class ABaseGameMode* _GameMode);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowGlobalInventory(class UInventoryComponent* _Inventor);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowEquipPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowLootEquipPanel(class AUnit* _LootUnit);

	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowFastPanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideFastPanel();
	//--777--UFUNCTION(BlueprintCallable, Category = "OOO")		void SelectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent);
	//--777--UFUNCTION(BlueprintCallable, Category = "OOO")		void DeselectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent);

	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowPerkPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowHealthPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowWpnChangePanel(class AUnit* _Unit,
																			int32& _WeaponSlotIndex,
																			ESlotType& _WeaponSlotType,
																			UTexture2D*& _WeaponSlotTexture);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideWpnChangePanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void OpenChangeWeaponPanel(class AUnit* _Unit,
																			TArray<int32>& _WeaponSlotsIndex,
																			TArray<ESlotType>& _WeaponSlotsType,
																			TArray<UTexture2D*>& _WeaponSlotsTexture);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void CloseChangeWeaponPanel();



	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon, 
																				int32& _SelectIndex, int32& _PermanentIndex);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideAttacksWpnPanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")		void UpdateAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon,
																				int32& _SelectIndex, int32& _PermanentIndex);



	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowTaskQueuePanel(class AUnit* _Unit,
																			UTexture2D*& _CurrTaskIcon,
																			TArray<UTexture2D*>& _TasksIcon,
																			TArray<int32>& _TasksIndex);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideTaskQueuePanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")		void UpdateTaskQueuePanel(class AUnit* _Unit,
																			UTexture2D*& _CurrTaskIcon,
																			TArray<UTexture2D*>& _TasksIcon,
																			TArray<int32>& _TasksIndex);




	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowPosePanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowAIPanel(class AUnit* _LootUnit);

	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowGroupPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowMapPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowMenuPanel(class AUnit* _LootUnit);



	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowUnitEffectPanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideUnitEffectPanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")		void UpdateUnitEffectPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowTargetEffectPanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideTargetEffectPanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")		void UpdateTargetEffectPanel(class AUnit* _Unit);


	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowParameterPanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void HideParameterPanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")		void UpdateParameterPanel(class AUnit* _Unit);



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsInvertoryShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsLootInvertoryShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsGlobalInvertoryShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsEquipPanelShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsLootEquipPanelShown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsFastPanelShown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsPerkPanelShown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsWpnChangePanelShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsWpnChangePanelOpened = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsAttacksWpnPanelShown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsTaskQueuePanelShowen = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsUnitEffectPanelhowen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsTargetEffectPanelShowen = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsParameterPanelShowen = false;

	// ** -------------------------------------------------------------------



	

};
