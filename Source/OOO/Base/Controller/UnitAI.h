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


#include "../Item/Struct/ItemDT.h"

#include "../Base/Enum/TurnBaseGameState.h"
#include "../Base/Enum/PossesingGameState.h"

#include "../Unit/Enum/UnitPose.h"

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


	UPROPERTY()		TArray<FTaskData> FractionQueueTaskDT;	// ** Stored General	TaskDT-Array (Task queue for screen draw) 
	//UPROPERTY()		TArray<FTaskData> StoreQueueTaskDT;		// ** Stored General	TaskDT-Array (Task queue for screen draw) 

	UPROPERTY()		FTaskData FractionTaskDT;			// ** Stored General	TaskDT 
	UPROPERTY()		FTaskData NpcTaskDT;				// ** Stored General	TaskDT 
	UPROPERTY()		FTaskData CriticalTaskDT;			// ** Stored General	TaskDT 

	//UPROPERTY()		FTaskData MainTaskDT;				// ** Using Parrent Task		
	//UPROPERTY()		FTaskData PartTaskDT;				// ** Using Child Task

	//UPROPERTY()		FTaskData CurrTaskDT;				// ** Current Task
	UPROPERTY()		TArray<FTaskData> TasksBuffer;	//----CurrTaskDTBuffer;		// ** for sub-Task Queue
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



public:

// **  ************************   Global_Operation  ************************


	UFUNCTION(Blueprintcallable, Category = "OOO_Gobal_Operation")
		int32 GetGameHour();	
	UFUNCTION(Blueprintcallable, Category = "OOO_Gobal_Operation")
		void OnNewGameHour(int32 iHour);

	UFUNCTION(Blueprintcallable, Category = "OOO_Gobal_Operation")
		EPossesingGameState GetPossesingGameState();
public:

// **  ************************   Misc_Operation  ************************


	UFUNCTION()		void SetTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData,
								ETaskCauser _TaskCauser = ETaskCauser::FractionTask,
								ETaskPriority _TaskPriority = ETaskPriority::Normal);

	UFUNCTION()		void UpdateLogic();
	UPROPERTY()		FTimerHandle TH_UpdateLogic;




public:

// **  ************************   Self_Operation  ************************

	UFUNCTION()		FVector GetCurrSelfLocation() const;
	UFUNCTION()		FRotator GetCurrSelfRotation();
	UFUNCTION()		void SetSelfRotation(FRotator rot);
	UFUNCTION()		FVector GetUnitRightVector();
	UFUNCTION()		FVector GetUnitForwardVector();

	UFUNCTION()		void SetUnitRotateSpeedByPose(EUnitPose _UnitPose);
	UFUNCTION()		void SetUnitMoveSpeed(float _Speed);
	UFUNCTION()		void UnitStopMove();

	UFUNCTION()		float GetUnitStopDistance();

	UFUNCTION()		bool IsUnitInGroup();
	UFUNCTION()		bool IsUnitSelected();

	UFUNCTION()		FName GetUnitGameName();

	UFUNCTION()		void PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime = 0.f);
	UFUNCTION()		void StopAnimate();

	UFUNCTION()		void GetTasksQueDataFromAI(UTexture2D*& _CurrTaskImage,
							TArray<UTexture2D*>& _TasksImage,
							TArray<int32>& _TasksIndex);
	// ** Weapon getters/setters
	UFUNCTION()		int32 IsWeaponActive();
	UFUNCTION()		bool ActivateWeapon();
	UFUNCTION()		bool UnactivateWeapon();
	UFUNCTION()		UAnimMontage* GetGameAnimation(EAnimationKey _AnimationKey);


	UFUNCTION()		class AWeaponWorldItem* GetCurrWeaponItem();

	//----------------------------------FItemDT* GetCurrWeaponData();

	UFUNCTION()		FTransform GetUnitSocketParam(FName _SocketName);

public:

// **  ************************   Target_Operation  ************************

	UFUNCTION()		FVector GetCurrTargetLocation();
	
	UFUNCTION()		float GetDistanceToTarget(AActor* _TargetActor, bool _WithMoveDistCorrector = false) const;



};
