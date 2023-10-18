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

	UFUNCTION()		void Init();	// ** Start from "UnitOwner"


public:

	UPROPERTY()		class AUnit* UnitOwner;


public:

	UPROPERTY()		TArray<FDailyBhvrData> DailyBhvrTaskDT;
	UPROPERTY()		class UTask* DailyBhvrTaskRef;

	UPROPERTY()		TArray<FTaskData> StoreQueueTaskDT;		// ** Stored General	TaskDT-Array 

	UPROPERTY()		FTaskData StoreGeneralTaskDT;			// ** Stored General	TaskDT 
	UPROPERTY()		FTaskData StoreAITaskDT;				// ** Stored AI			TaskDT 
	UPROPERTY()		FTaskData StoreDominantTaskDT;			// ** Stored Dominant	TaskDT 		

	//UPROPERTY()		FTaskData MainTaskDT;					// ** Using Parrent Task		
	//UPROPERTY()		FTaskData PartTaskDT;					// ** Using Child Task

	//UPROPERTY()		FTaskData CurrTaskDT;					// ** Current Task
	UPROPERTY()		TArray<FTaskData> CurrTaskDTBuffer;
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
	UFUNCTION()		void OnFinishAnim()
	UFUNCTION()		void OnBreakAnim()
	UFUNCTION()		void OnAnimNotify()
	UFUNCTION()		void OnX()
	UFUNCTION()		void OnX()
	UFUNCTION()		void OnX()
	UFUNCTION()		void OnX()
	UFUNCTION()		void OnTaskFinish()
	UFUNCTION()		void OnTaskInterupt()
*/



public:

// **  ************************   Core_Action  ************************


	UFUNCTION()		void MoveToPoint();
	UFUNCTION()		void MoveToUnit();
	UFUNCTION()		void Rotate();
/*	UFUNCTION()		void PlayAnimate();	
	UFUNCTION()		void Wait();
*/


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
	UFUNCTION()		void	SetSelfRotation(FRotator rot);
	UFUNCTION()		FVector GetUnitRightVector();
	UFUNCTION()		FVector GetUnitForwardVector();

	UFUNCTION()		void	SetUnitRotateSpeed(uint8 _RotSpeedIndex);	// ** 0, 1, 2, 3
	UFUNCTION()		void	SetUnitMoveSpeed(float _Speed);
	UFUNCTION()		void	UnitStopMove();

public:

// **  ************************   Target_Operation  ************************

	UFUNCTION()		FVector GetCurrTargetLocation();
	

// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************
public:

	//--------------void AddTaskMovePointTEST(ETaskType _TaskType, FVector _Location, bool _IsRotateByPoint, FRotator _Rotation);

};
