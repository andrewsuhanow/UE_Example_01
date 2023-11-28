// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Task/Struct/TaskData.h"
#include "Task/Struct/DailyBhvrData.h"

#include "Task/Enum/TaskType.h"
#include "Task/Enum/TaskPriority.h"

#include "Enum/UnitBehaviorLogic.h"
#include "Enum/UnitPositionLogik.h"
//#include "Enum/TaskInstigator.h"

#include "../Amunition/Enum/WeaponType.h"
#include "../Animation/Enum/AnimationKey.h"

#include "../Base/Enum/TurnBaseGameState.h"



#include "UnitAI.generated.h"






// ** AUnitAI
UCLASS()
class OOO_API AUnitAI : public AAIController
{
	GENERATED_BODY()

public:

	AUnitAI();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()		void Init(bool isStart = false);	// ** Start from "UnitOwner"


public:

	UPROPERTY()		class AUnit* UnitOwner;
	UPROPERTY()		class ABaseGameMode* GameMode;
	UPROPERTY()		class ABaseGameState* GameState;
	UPROPERTY()		class ABaseHUD* HUD;


public:
	
	// ** Daily-behavior Default Queue (init from Unit::DailyBhvrQueueClass)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")		
		TArray<FDailyBhvrData> DailyBhvrTaskDT;
	UPROPERTY()		int32 DailyBhvrTaskIndex = -1;			// ** Index in TaskObj


	UPROPERTY()		TArray<FTaskData> StoreQueueTaskDT;		// ** Stored General	TaskDT-Array (Task queue for screen draw) 

	UPROPERTY()		FTaskData StoreGeneralTaskDT;			// ** Stored General	TaskDT 
	UPROPERTY()		FTaskData StoreAITaskDT;				// ** Stored AI			TaskDT 
	UPROPERTY()		FTaskData StoreDominantTaskDT;			// ** Stored Dominant	TaskDT 		

	//UPROPERTY()		FTaskData MainTaskDT;				// ** Using Parrent Task		
	//UPROPERTY()		FTaskData PartTaskDT;				// ** Using Child Task

	//UPROPERTY()		FTaskData CurrTaskDT;				// ** Current Task
	UPROPERTY()		TArray<FTaskData> CurrTaskDTBuffer;		// ** for sub-Task Queue
	UPROPERTY()		class UTask* CurrTaskRef;

	UPROPERTY(VisibleAnywhere, Category = "OOO")
		TArray<UTask*> ActionTaskssObj;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<TSubclassOf<UTask>> AvailableTaskType;


	// ** DELEGATE_TO_HUD	(SET)
			// ** Pose
			// ** CurrAttack (selected)
			// ** CurrWeapon
			// ** CurrTask
			// ** CurrLogicBehavior
			// ** unitParam (health, mana)
			// ** DailyBehavior	(Create DB panel)
	// +++ EAI_BehaviorMovable
	// +++ EAI_BehaviorRecaction


public:

	// **  ************************   Unit AI Paramter  ************************

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_UnitAi_Parameter")
		float DefenceZone = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_UnitAi_Parameter")
		bool IsCanAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_UnitAi_Parameter")
		// ** AI,  Player,  PlayerOnly,  DailyBehavior
		EUnitBehaviorLogic BhvrLogic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_UnitAi_Parameter")
		// ** PointOnly,  PointRadius,  ShaseTarget,  ShaseTargetWithReturn
		EUnitPositionLogik PosLogik;

public:

	// **  ************************   EVENT  ************************

		//--------------virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	/*	UFUNCTION()		void OnStopRotate()
		UFUNCTION()		void OnStopWaiting()
		
		UFUNCTION()		void OnBreakAnim()
		UFUNCTION()		void OnAnimNotify()
		UFUNCTION()		void OnX()
		UFUNCTION()		void OnX()
		UFUNCTION()		void OnX()
		UFUNCTION()		void OnX()
		UFUNCTION()		void OnTaskFinish()
		UFUNCTION()		void OnTaskInterupt()
	*/		

	UFUNCTION()		void OnFinishAnimation(UAnimMontage* FinishedAnimMontage, bool _bInterrupted);

	// ** EVENT:    "CHange GameState"    (RealTime,  Pause,  TurnBase,)
	UFUNCTION()		void OnChangeTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState);

	UFUNCTION()		void OnAnimNotify(FString _NotifyName);


public:

// **  ************************   Core_Action  ************************


	UFUNCTION()		void MoveToPoint();
	UFUNCTION()		void MoveToUnit();
	UFUNCTION()		void Rotate();
/*	UFUNCTION()		void PlayAnimate();	
	UFUNCTION()		void Wait();
	// ** ...
	// ** ...
	// ** ...
*/



public:

// **  ************************   Global_Operation  ************************


	UFUNCTION(Blueprintcallable, Category = "OOO_GameTime")
		int32 GetGameHour();
	UFUNCTION(Blueprintcallable, Category = "OOO_GameTime")
		void OnNewGameHour(int32 iHour);

public:

// **  ************************   Misc_Operation  ************************


	UFUNCTION()		void SetTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData,
								ETaskInstigator _TaskInstigator = ETaskInstigator::General, 
								ETaskPriority _TaskPriority = ETaskPriority::Normal);

	UFUNCTION()		void UpdateLogic();





public:

// **  ************************   Self_Operation  ************************

	UFUNCTION()		FVector GetCurrSelfLocation();
	UFUNCTION()		FRotator GetCurrSelfRotation();
	UFUNCTION()		void SetSelfRotation(FRotator rot);
	UFUNCTION()		FVector GetUnitRightVector();
	UFUNCTION()		FVector GetUnitForwardVector();

	UFUNCTION()		void SetUnitRotateSpeed(uint8 _RotSpeedIndex);	// ** 0, 1, 2, 3
	UFUNCTION()		void SetUnitMoveSpeed(float _Speed);
	UFUNCTION()		void UnitStopMove();

	UFUNCTION()		float GetUnitStopDistance();

	UFUNCTION()		bool IsUnitInGroup();
	UFUNCTION()		bool IsUnitSelected();

	UFUNCTION()		FName GetUnitGameName();

	UFUNCTION()		void PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime = 0.f);

	UFUNCTION()		void GetTasksQueDataFromAI(UTexture2D*& _CurrTaskImage,
							TArray<UTexture2D*>& _TasksImage,
							TArray<int32>& _TasksIndex);
	// ** Weapon getters/setters
	UFUNCTION()		int32 IsWeaponActive();
	UFUNCTION()		bool ActivateWeapon();
	UFUNCTION()		bool UnactivateWeapon();
	UFUNCTION()		UAnimMontage* GetGameAnimation(EAnimationKey _AnimationKey);

public:

// **  ************************   Target_Operation  ************************

	UFUNCTION()		FVector GetCurrTargetLocation();
	

// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************
public:

	//--------------void AddTaskMovePointTEST(ETaskType _TaskType, FVector _Location, bool _IsRotateByPoint, FRotator _Rotation);

};
