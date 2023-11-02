
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

	UFUNCTION()		bool Init(TSubclassOf<class UW_Screen> W_Screen_Class);
	UFUNCTION()		void SetDefaultGameParam(class ABaseGameMode* _GameMode, class ABaseGameState* _GameState);

public:

// *************************   W_Screen   ****************************

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class UW_Screen* Screen;
	
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowInventory(class AUnit* _Unit, ABaseGameMode* _GameMode);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowLoot(class AUnit* _LootUnit, ABaseGameMode* _GameMode);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowEquipPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowLootEquipPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowFastPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowPerkPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowWpnAttackPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowHealthPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowWpnChangePanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowPosePanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowAIPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowGroupPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowMapPanel(class AUnit* _LootUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO")		void ShowMenuPanel(class AUnit* _LootUnit);

};
