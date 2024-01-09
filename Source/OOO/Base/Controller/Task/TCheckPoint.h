
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "../../Unit/Enum/UnitPose.h"
//+++#include "Enum/TaskStep.h"

#include "TCheckPoint.generated.h"


UENUM()
enum class ETaskCaution : uint8
{
	none,
	Relax,
	Vigilant,	// ** Attentive
	Alert
};

UENUM(BlueprintType)
enum class ECheckPointStep : uint8						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   Do separt file
{
	none = 0,
	StartTask,

	//--7777--PartMove,

	RotateStep1,
	RotateStep2,
	RotateStep3,
	RotateStep4,
	RotateStep5,
	Finish,

	MAX
};



UCLASS()
class OOO_API UTCheckPoint : public UTask
{
	GENERATED_BODY()

public:

	UTCheckPoint();



public:

	UPROPERTY()
		ECheckPointStep TaskStep = ECheckPointStep::none;
	UPROPERTY()
		ETaskCaution TaskCaution = ETaskCaution::none;
	UPROPERTY()
		EUnitPose TaskSpeed = EUnitPose::none;
	UPROPERTY()
		FVector GoalPoint;

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual void ResetTask(class AUnitAI* _OwnerAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;

public:

	UFUNCTION()
		bool TryMoveToGoalPoint(class AUnitAI* _OwnerAI);
	UFUNCTION()
		bool CautionMoveToGoalPoint(class AUnitAI* _OwnerAI);
	UFUNCTION()
		bool TryLookToGoalPoint(class AUnitAI* _OwnerAI);
	UFUNCTION()
		void RotateOnAngle(class AUnitAI* _OwnerAI, float _Angle);
	UFUNCTION()
		void Wait(class AUnitAI* _OwnerAI, float _Time);


	// ** ---------------------  Static func  ------------------------
public:

	// ** No attention
	UFUNCTION()
		static void SetTaskData_RelaxCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint);

	// ** Shasing somebody
	UFUNCTION()
		static void SetTaskData_FastCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint);

	// ** Slow but Mindful
	UFUNCTION()
		static void SetTaskData_CautionCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint);
};



