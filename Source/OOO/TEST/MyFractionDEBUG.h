
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

#include "MyFractionDEBUG.generated.h"


UENUM()
enum class ETacticalAttackTEST_CXXXXXXXXXXXXXXXX : uint8
{
	/*
		Distance to Target too close (in target front)

		=>> SelfUnit must fast move backward  (on Point = OptimalDistToTarget * 2.f + RND(0.f, 100.f))
		=>> or (if Target stand Backside) do next step to Attack
	*/
	TargetTooClose,
	TargetTooFar,

	/*
		Prepare RND-dist position betvean MaxAttack and TargetPos

		SuelUnit uust go Forward/Back to correct oprimal dist
	*/
	BeforeAttackCorrectDist,
	
	MAX
};

UENUM()
enum class ETacticalAttack_Side_FFFFFFFFFFFFFF : uint8
{
	Front,
	Front_Left,
	Front_Right,
	Back,
	Back_Left,
	Back_Right,

	MAX
};

UCLASS()
class OOO_API AMyFractionDEBUG : public ADefaultPawn
{
	GENERATED_BODY()
	

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

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void OpenEquipPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void AddItemToEquipPanel();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_4_Equip")			void SetEquipPanelSet();


public:
	// ** Attack
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetPrepare__________TEST();
	UFUNCTION() 																	void PrepareMarcer(FVector _EndPoint, AActor* _Target = nullptr);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void Attack______________SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void Attack______________ADD();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		FName UnitForAttackName = FName("Un3");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		class AUnit* UnitTarget;


	UFUNCTION()										void Attack_Performance(FName _UnitForAttackName, bool _bAddMoreOneTask);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		float TargetRotateDependTarget_Degres = 90;
	//UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetSelectAttackIndex();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		int32 SelectAttackIndex = -1;
	//UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetPermanentAttackIndex();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		int32 PermanentAttackIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		FVector EndPointTM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool IsDebugLine_TacticalMove = true;
	
	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool isDrawWeaponHIT_DebugSphere = true;
	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool isPrintingHitingActor_DebugLOG = true;


public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_Invertory_5_Total")			void InitTestInvertorItems();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Total")			TArray<FName> ItemsToAdd;
	TArray<TSharedPtr<FItemDT>> ItemsToAddRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Total")			int32 AddToSlotIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Total")			int32 AddItemIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Total")			bool IsForseAdd = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Invertory_5_Total")			EAbilityType AbilityToAdd;




public:

	AMyFractionDEBUG();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;



};
