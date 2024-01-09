
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

#include "../Base/Controller/Task/Enum/TacticalMoveType.h"
#include "../Base/Unit/Enum/UnitPose.h"

#include "TaskDEBUG.generated.h"


UCLASS()
class OOO_API ATaskDEBUG : public ADefaultPawn
{
	GENERATED_BODY()
	

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void Shift_Left_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void Shift_Left_Release();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void SpaceBar_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input") 				void SpaceBar_Release();


public:
	// ** Select Unit
	UPROPERTY()		class ABaseGameMode* GameMod;
	UPROPERTY()		class ABaseGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class AUnit* SelectTestUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		TArray<FTaskData> StoreQueueTaskDTCopy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		TArray<FTaskData> CurrTaskDTBufferCopy;
	UPROPERTY()																			float sh = 0;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_1();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_2();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_3();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_4();
	UFUNCTION() 																		void SelctUn_Performance(FName _SelectUnitName);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_1 = FName("Un1");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_2 = FName("Un2");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_3 = FName("Un5_DrawWpn");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_4 = FName("Un4_CheckPoint");

public:
	// ** Move to Point
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveTo_1_SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveTo_2_ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveTo_3_ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveTo_4_ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_MoveToPointName") 		void MoveTo_5_ADD();
	UFUNCTION()																				void MoveTo_Performance(FName _Point_MoveTo,
																												bool _bPoint_IsRotateTo,
																												bool _bAddMoreOneTask);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool IsDrawMoveGoalRay = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_1_MoveTo = FName("wpL_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_1_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_2_MoveTo = FName("wpL_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_2_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_3_MoveTo = FName("wpL_02");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_3_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_4_MoveTo = FName("wpL_03");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_4_IsRotateTo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		FName Point_5_MoveTo = FName("Un2");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_MoveToPointName")		bool Point_5_IsRotateTo = false;

public:
	// ** Rotate to Point
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateToPoint_1________SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateToPoint_2________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateToPoint_3________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateToPoint_4________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateToPoint_5________ADD();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate") 		void RotateAngle________SET();
	UFUNCTION()										void RotateToPoint_Performance(FName _Point_MoveTo,	bool _bAddMoreOneTask);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Rotate")			void SetDefaultRotate();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FRotator DefaultRotate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FName Point_1_RotateTo = FName("wpL_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FName Point_2_RotateTo = FName("wpL_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FName Point_3_RotateTo = FName("wpL_02");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FName Point_4_RotateTo = FName("wpL_03");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		FName Point_5_RotateTo = FName("wpL_04");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		float RotateAngle = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		float RotateSide = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		EUnitPose RotateSpeed = EUnitPose::Run;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Rotate")		bool DrawDebugRotate = false;

public:
	// ** Attack
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetTargetRotationToAttacker();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void Attack______SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void Attack______ADD();
	UFUNCTION()										void Attack_Performance(FName _UnitForAttackName, bool _bAddMoreOneTask);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		FName UnitForAttackName = FName("Un3");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		float TargetRotateDependTarget_Degres = 90;
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetSelectAttackIndex();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		int32 SelectAttackIndex = -1;
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Attack") 		void SetPermanentAttackIndex();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		int32 PermanentAttackIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool isDrawWeaponTRACE_DebugLine = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool isDrawWeaponHIT_DebugSphere = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Attack")		bool isPrintingHitingActor_DebugLOG = true;

	// ** Parrir / Block / Dodge / GetHit
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_005_Reaction") 		void Parrir();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_005_Reaction") 		void Block();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_005_Reaction") 		void Dodge();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_005_Reaction") 		void GetHit();

public:
	// ** Tactical Move
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_006_Tactical_Move") 	void Tactical_Move();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_006_Tactical_Move")	ETacticalMoveType TacticMoveType = ETacticalMoveType::SimpleMoveToPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_006_Tactical_Move")	float StopDistance = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_006_Tactical_Move")	FName TargetName = FName("wpL_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_006_Tactical_Move")	FName FocusActorName = FName("Un3");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_006_Tactical_Move")	EUnitPose UnitPose = EUnitPose::Run;


public:
	// ** Theck the Point
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_007_TheckThePoint") 	void TheckThePoint_1();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_007_TheckThePoint") 	void TheckThePoint_2();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_007_TheckThePoint") 	void TheckThePoint_3();
	UFUNCTION()										void TheckThePoint_Performance(FName _Point_ToCheck);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_007_TheckThePoint")	void SetDefaultPosition();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_007_TheckThePoint")	FName Point_1_ToCheck = FName("wpCheck_01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_007_TheckThePoint")	FName Point_2_ToCheck = FName("wpCheck_02");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_007_TheckThePoint")	FName Point_3_ToCheck = FName("wpCheck_03");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_007_TheckThePoint")	EUnitPose CheckBySpeed = EUnitPose::RelaxMove;

public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_099_DayTime") 		void AddHour_To_GameTime();
	UFUNCTION() 																	void InitDailyBehaviorDT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_099_DayTime")		int32 TimeCountToAdd = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_099_DayTime")	int32 GameTimePresent = -789;




	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	TArray<FTaskData> StoreQueueTaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreAITaskDT;
	//UPROPERTY(VisibleAnywhere, Category = "OOO_003_CurrTaskParamVision")					
	//	FTaskData StoreDominantTaskDT;

public:

	ATaskDEBUG();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
