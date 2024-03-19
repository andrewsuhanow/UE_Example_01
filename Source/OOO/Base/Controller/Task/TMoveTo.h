
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "Struct/TaskData.h"

#include "Enum/TacticalMoveType.h"

#include "../../Unit/Enum/UnitPose.h"

#include "TMoveTo.generated.h"



UENUM()
enum class EDrawPathType : uint8
{
	none = 0,
	EndPoint,
	FullPath,
	FullPathPoint,


	MAX
};





UCLASS()
class OOO_API UTMoveTo : public UTask
{
	GENERATED_BODY()

public:

	UTMoveTo();

	UFUNCTION()		void InitPathMarker(class AUnitAI* _OwnerAI);

public:


	UPROPERTY()	 class AWorldPathMarker* PathMarker;

	UPROPERTY()	 ETacticalMoveType TacticalMoveType;

	UPROPERTY()	 AUnit* TargetUnit = nullptr;
	UPROPERTY()	 AActor* TargetActor = nullptr;
	UPROPERTY()	 AActor* FocusingActor = nullptr;
	UPROPERTY()	 FVector GoalLocation;
	UPROPERTY()	 FVector LastTargetLocation;
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

	// ** Path
	UPROPERTY()	 EDrawPathType DrawPathType = EDrawPathType::none;
	UPROPERTY()	 bool IsPathMarkersGenerated = false;
	UPROPERTY()	 TArray<FVector> Path;		// ** first point is Self-Position,  first point is Loal-Location
	UPROPERTY()	 FVector NextMiddlePathPoint;
	UPROPERTY()	 int32 NextMiddlePathindex = -1;
	UPROPERTY()	 int32 PathPointsMum = -1;

public:

	UPROPERTY()	 AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _OwnerAI) override;

	virtual void ResetTask(class AUnitAI* _OwnerAI) override;

	virtual bool IdentifyTask(class AUnitAI* _OwnerAI) override;

	UPROPERTY()		FTimerHandle TH_Move;
	UFUNCTION()		void MoveActorPerformance();
	UFUNCTION()		void MovePointPerformance();
	// ** bit pause in moving (after move) for smoth betvean move-Task
	UFUNCTION()		void TaskComplitDelay(class AUnitAI* _OwnerAI);
	UFUNCTION()		void WaitingAfterStop();

	// ** Path
	UFUNCTION()		bool GenerateNavPath(class AUnitAI* _OwnerAI,
		bool _UseSpecialPoint = false, FVector _GoalPoint = FVector(0.f, 0.f, 0.f));
	UFUNCTION()		void DrawNavPathMarker(class AUnitAI* _OwnerAI);// , bool _IsDrawFullPath = false);
	UFUNCTION()		bool IsNavPathGenerate(class AUnitAI* _OwnerAI);
	UFUNCTION()		void HideNavPathMarkers(class AUnitAI* _OwnerAI);
	UFUNCTION()		bool GetNextMiddlePathPoint();
	


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



