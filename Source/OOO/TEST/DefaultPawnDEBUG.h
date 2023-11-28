
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"

#include "../Base/Controller/Task/Struct/TaskData.h"		// ** SetUnitTask()  ->  AI
#include "../Base/Controller/Task/Enum/TaskType.h"			// ** SetUnitTask()  ->  AI

#include "../Base/Ability/Enum/AbilityType.h"

#include "GameFramework/PlayerInput.h"						// ** FInputActionKeyMapping

#include "../Base/Base/Enum/TurnBaseGameState.h"

#include "../Base/Item/Struct/ItemDT.h"
#include "../Base/Ability/Enum/AbilityType.h"

#include "DefaultPawnDEBUG.generated.h"


UCLASS()
class OOO_API AAAADefaultPawnDEBUG : public ADefaultPawn
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

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveToPoint_1__________SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveToPoint_2__________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveToPoint_3__________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveToPoint_4__________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveToPoint_5__________ADD();
	UFUNCTION()																				void MoveToPoint_Performance(FName _Point_MoveTo,
	bool _bPoint_IsRotateTo,
	bool _bAddMoreOneTask);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_1_MoveTo = FName("wpL01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_1_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_2_MoveTo = FName("wpL01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_2_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_3_MoveTo = FName("wpL02");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_3_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_4_MoveTo = FName("wpL03");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_4_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_5_MoveTo = FName("wpL04");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_5_IsRotateTo = false;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_RotateToPointName") 		void RotateToPoint_1________SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_RotateToPointName") 		void RotateToPoint_2________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_RotateToPointName") 		void RotateToPoint_3________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_RotateToPointName") 		void RotateToPoint_4________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_RotateToPointName") 		void RotateToPoint_5________ADD();
	UFUNCTION()										void RotateToPoint_Performance(FName _Point_MoveTo,	bool _bAddMoreOneTask);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_RotateToPointName")		FName Point_1_RotateTo = FName("wpL01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_RotateToPointName")		FName Point_2_RotateTo = FName("wpL01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_RotateToPointName")		FName Point_3_RotateTo = FName("wpL02");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_RotateToPointName")		FName Point_4_RotateTo = FName("wpL03");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_RotateToPointName")		FName Point_5_RotateTo = FName("wpL04");



public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_1_Total")			void InitTestInvertorItems();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			TArray<FName> ItemsToAdd;
																							TArray<TSharedPtr<FItemDT>> ItemsToAddRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			int32 AddToSlotIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			int32 AddItemIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			bool IsForseAdd = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_1_Total")			EAbilityType AbilityToAdd;

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
//																							TSharedPtr<FItemDT> EquipItemsDT1;
//																							TSharedPtr<FItemDT> EquipItemsDT2;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_5_Ability")		void AddAbility();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_5_Ability")		void ShowPerkPanel();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Ability")					TArray<EAbilityType> Ability;
	

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void ShowFastPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void AddItemToFastPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_6_FastPanel")		void AddAbilityToFastPanel();
//																							TArray<TSharedPtr<FItemDT>> FastPanelItemsDT;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_003_DayTime") 		void AddHour_To_GameTime();
	UFUNCTION() 																	void InitDailyBehaviorDT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_003_DayTime")		int32 TimeCountToAdd = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_003_DayTime")	int32 GameTimePresent = -789;




	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	TArray<FTaskData> StoreQueueTaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreAITaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreDominantTaskDT;

public:

	AAAADefaultPawnDEBUG();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
