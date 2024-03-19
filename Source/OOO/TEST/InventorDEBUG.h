
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"

#include "../Base/Controller/Task/Struct/TaskData.h"		// ** SetUnitTask()  ->  AI
#include "../Base/Controller/Task/Enum/TaskType.h"			// ** SetUnitTask()  ->  AI



#include "GameFramework/PlayerInput.h"						// ** FInputActionKeyMapping

#include "../Base/Base/Enum/TurnBaseGameState.h"

#include "../Base/Item/Struct/ItemDT.h"
//#include "../Base/Ability/Enum/AbilityLogic.h"

#include "InventorDEBUG.generated.h"


UCLASS()
class OOO_API AInventorDEBUG : public ADefaultPawn
{
	GENERATED_BODY()
	

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void Shift_Left_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void Shift_Left_Release();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void SpaceBar_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void SpaceBar_Release();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class ABaseGameMode* GameMod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class ABaseGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class AUnit* SelectTestUnit;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelectUnit_1();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelectUnit_2();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelectUnit_3();
	UFUNCTION() 																		void SelectUnit_Performance(FName _SelectUnitName);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_1 = FName("Un1");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_2 = FName("Un2");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_3 = FName("Un3");




public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_1_Total")			void InitTestInvertorItems();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			TArray<FName> ItemsToAdd;
																							TArray<TSharedPtr<FItemDT>> ItemsToAddRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			int32 AddToSlotIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			int32 AddItemIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			bool IsForseAdd = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			EAbilityLogic AbilityToAdd;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_2_Main")			void OpenMainInvertory();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_2_Main")			void AddItemToInventory();	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_2_Main")		TSubclassOf<class AWorldItem> InventorWorldItem = nullptr;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_3_Global")	 		void OpenGlobalInvertory();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_3_Global")	 		void AddItemToGlobalInventory();
//																							TArray<TSharedPtr<FItemDT>> GlobalItemsDT;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void OpenEquipPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void AddItemToEquipPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void SetEquipPanelSet();
//																							TSharedPtr<FItemDT> EquipItemsDT1;
//																							TSharedPtr<FItemDT> EquipItemsDT2;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_5_Ability")		void AddAbility();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_5_Ability")		void ShowPerkPanel();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Ability")		TArray <FName> AbiilityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Ability")		TArray< TSubclassOf<class UAbilityDT> > AbilityClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Ability")					TArray<EAbilityType> Ability;
	

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void ShowFastPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void AddItemToFastPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void AddAbilityToFastPanel();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_6_FastPanel")		int32 SlotIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_6_FastPanel")		int32 AbilityIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_6_FastPanel")		TArray <FName> AbiilityAddToFastPanel;
//																							TArray<TSharedPtr<FItemDT>> FastPanelItemsDT;






	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	TArray<FTaskData> StoreQueueTaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreAITaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreDominantTaskDT;

public:

	AInventorDEBUG();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
