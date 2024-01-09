
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "Struct/TaskData.h"

#include "Enum/TacticalMoveType.h"

#include "../../Unit/Enum/UnitPose.h"

#include "TMoveTo.generated.h"

UCLASS()
class OOO_API UTMoveTo : public UTask
{
	GENERATED_BODY()

public:

	UTMoveTo();

public:


	UPROPERTY()	 ETacticalMoveType TacticalMoveType;

	UPROPERTY()	 AUnit* TargetUnit = nullptr;
	UPROPERTY()	 AActor* TargetActor = nullptr;
	UPROPERTY()	 AActor* FocusingActor = nullptr;
	UPROPERTY()	 FVector GoalLocation;
	UPROPERTY()	 EUnitPose LastPose = EUnitPose::none;
	UPROPERTY()	 EUnitPose NewPose = EUnitPose::none;
	UPROPERTY()	 float StopDistance = 0.f;
	UPROPERTY()	 float LastSpeed = -1.f;
	UPROPERTY()	 float NewSpeed = -1.f;

	UPROPERTY()	 bool bFixRotOnTarget = false;	// ** SetFocus()

	UPROPERTY()	 bool bStopOnOverlap = false;
	UPROPERTY()	 bool bUsePathfinding = true;
	UPROPERTY()	 bool bCanStrafeMove = false;	// ** IsRotationFixing

	// ** bit pause in moving (after move) for smoth betvean move-Task
	UPROPERTY()	bool IsNeedWaitingAfterStop = false;

public:

	UPROPERTY()	 AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual void ResetTask(class AUnitAI* _OwnerAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Move;
	UFUNCTION()			void MoveActorPerformance();
	UFUNCTION()			void MovePointPerformance();
	// ** bit pause in moving (after move) for smoth betvean move-Task
	UFUNCTION()			void WaitingAfterStop();




	// -----------------------------   Static   -----------------------------


public:

	UFUNCTION()
		static bool SetMoveData_MoveToPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _TargetPoint,
			float _StopDist = 0.f, EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);
	UFUNCTION()
		static bool SetMoveData_MoveToActor(FTaskData& _TaskData, AUnit* _SelfUnit, AActor* _TargetActor,
			float _StopDist = 0.f, EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);
	UFUNCTION()
		static bool SetMoveData_MoveToPointWithUnitFocus(FTaskData& _TaskData, AUnit* _SelfUnit,
			FVector _TargetPoint, AActor* _FocusingActor, float _StopDist = 0.f, 
			EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);
	UFUNCTION()
		static bool SetMoveData_MoveToActorWithUnitFocus(FTaskData& _TaskData, AUnit* _SelfUnit,
			AActor* _TargetActor, AActor* _FocusingActor, float _StopDist = 0.f, 
			EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);

	UFUNCTION()
		static bool SetMoveData_MoveToActorWithRotateFix(FTaskData& _TaskData, AUnit* _SelfUnit,
			AActor* _TargetActor, float _StopDist = 0.f, 
			EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);
	UFUNCTION()
		static bool SetMoveData_MoveToPointWithRotateFix(FTaskData& _TaskData, AUnit* _SelfUnit,
			FVector _TargetPoint, float _StopDist = 0.f, 
			EUnitPose _Pose = EUnitPose::none, bool _IsWaitAfterMove = true);


};



