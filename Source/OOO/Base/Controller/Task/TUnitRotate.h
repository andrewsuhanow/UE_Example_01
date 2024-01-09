
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "../../Unit/Enum/UnitPose.h"

#include "TUnitRotate.generated.h"


/*
UENUM()
enum class ETaskRotSpeed : uint8
{
	RelaxRotate,
	FastRotate,
	InstantlyRotate,
};
*/


UCLASS()
class OOO_API UTUnitRotate : public UTask
{
	GENERATED_BODY()

public:

	UTUnitRotate();

public:

	UPROPERTY()  	float RotateSpeed = 0.f;
	UPROPERTY()		EUnitPose TaskRotSpeed = EUnitPose::none;
	// ** Rotate to point
	UPROPERTY()		FVector GoalPoint;
	// ** Rotate side
	UPROPERTY()		float Angle;		// 7777777777777777777
	UPROPERTY()		int32 RotateSide;    

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual void ResetTask(class AUnitAI* _OwnerAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Rotate;
	UFUNCTION()			void RotateTick();

	void GetAngleRotateToPoint(class AUnitAI* _OwnerAI, FVector _GoalPoint, float &_AngleRef, int32 &_SideRef);
	void GenerateGoalPoint(class AUnitAI* _OwnerAI, float _Angle, int32 _Side, FVector &_GoalPointRef);




	// ** ---------------------  Static func  ------------------------

public:


	UFUNCTION()
		static void SetRotateData_ToPoint(FTaskData& _TaskData, AActor* _TargetActor, 
			FVector _GoalPoint, EUnitPose _Pose = EUnitPose::none);
/*
	UFUNCTION()
		static void SetRotateData_FastRotToPoint(FTaskData& _TaskData, AActor* _TargetActor, FVector _GoalPoint);

	UFUNCTION()
		static void SetRotateData_InstantlyRotToPoint(FTaskData& _TaskData, AActor* _TargetActor, FVector _GoalPoint);
*/
	UFUNCTION()
		static void SetRotateData_OnAngle(FTaskData& _TaskData, AActor* _TargetActor, float 
			_Angle, int32 _Side, EUnitPose _Pose = EUnitPose::none);
/*
	UFUNCTION()
		static void SetRotateData_FastRotOnAngle(FTaskData& _TaskData, AActor* _TargetActor, float _Angle, int32 _Side);

	UFUNCTION()
		static void SetRotateData_InstantlyRotOnAngle(FTaskData& _TaskData, AActor* _TargetActor, float _Angle, int32 _Side);
*/

};



