

//#include "Task/TCheckPoint.h"
#include "TCheckPoint.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"

#include "TMoveTo.h"
#include "TWait.h"
#include "TUnitRotate.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"





UTCheckPoint::UTCheckPoint()
{
	TaskType = ETaskType::CheckPoint;
}


void UTCheckPoint::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	TaskStep = ECheckPointStep::StartTask;

	ContinueTask(_OwnerAI);
}


void UTCheckPoint::ContinueTask(AUnitAI* _OwnerAI)
{

	IdentifyTask(_OwnerAI);

	TaskSpeed = EUnitPose::Run;


	if (TaskCaution == ETaskCaution::Alert)
	{
		switch (TaskStep)
		{
		case ECheckPointStep::StartTask:// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			return;
		case ECheckPointStep::RotateStep1:// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			return;

			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   Alert  Move to point
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
	}

	else
	{
		if (TaskCaution == ETaskCaution::Relax)
			TaskSpeed = EUnitPose::RelaxMove;


		switch (TaskStep)
		{
		case ECheckPointStep::StartTask:
			
			TaskStep = ECheckPointStep::RotateStep1;

			// ** SubTask started "Rotate" (FirstRotate)
			if (TryLookToGoalPoint(_OwnerAI))
			{
				// ** empty here
			}   

		   // ** SubTask started "Move"
			else if (TryMoveToGoalPoint(_OwnerAI))
				TaskStep = ECheckPointStep::StartTask;

			// ** do next step
			else
				ContinueTask(_OwnerAI);

			return;


		case ECheckPointStep::RotateStep1:

			TaskStep = ECheckPointStep::RotateStep2;
			Wait(_OwnerAI, 3.f);
			return;

		case ECheckPointStep::RotateStep2:

			TaskStep = ECheckPointStep::RotateStep3;
			RotateOnAngle(_OwnerAI, 90.f);
			return;

		case ECheckPointStep::RotateStep3:

			TaskStep = ECheckPointStep::RotateStep4;
			Wait(_OwnerAI, 2.f);
			return;

		case ECheckPointStep::RotateStep4:

			TaskStep = ECheckPointStep::RotateStep5;
			RotateOnAngle(_OwnerAI, -180.f);
			return;

		case ECheckPointStep::RotateStep5:

			TaskStep = ECheckPointStep::Finish;
			Wait(_OwnerAI, 2.f);
			return;

		case ECheckPointStep::Finish:

			TaskComplit(_OwnerAI);

		}

	}

}

		


void UTCheckPoint::TaskComplit(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::TaskComplit(_OwnerAI);
}


void UTCheckPoint::BreakTask(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::BreakTask(_OwnerAI);
}


void UTCheckPoint::ResetTask(class AUnitAI* _OwnerAI)
{
	TaskStep = ECheckPointStep::none;
	TaskCaution = ETaskCaution::none;
	TaskSpeed = EUnitPose::none;
}





bool UTCheckPoint::TryMoveToGoalPoint(AUnitAI* _OwnerAI)
{
	// ** Move to GoalPoint  
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* path = NavSys->FindPathToLocationSynchronously(GetWorld(), _OwnerAI->GetCurrSelfLocation(), GoalPoint, NULL);

	int32 LastPointIndex = path->PathPoints.Num() - 1;
	if (LastPointIndex > 0) // ** its mean 2 point (1 - self position, 1 - Target Position)											
	{
		// ** Get point near the "GoalPoint"
		// ** (( if GoalPoint is nearby us but after obstacles =>> need find other GoalPoint near the original))
		FVector preLastPathPoint = path->PathPoints[LastPointIndex - 1];
		float stopDistance = _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 6.f;
		FVector ResultPointToStop = GoalPoint + (preLastPathPoint - GoalPoint).GetSafeNormal() * stopDistance;

		// ** Move to  point near the GoalPoint
		FTaskData SubTask;
		float stopDist = 0.f;
		UTMoveTo::SetMoveData_MoveToPoint(SubTask, _OwnerAI->UnitOwner, ResultPointToStop, stopDist, EUnitPose::RelaxMove);

		_OwnerAI->SetTask(false, ETaskType::MoveTo, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		UE_LOG(LogTemp, Warning, TEXT("Task::CheckPoint,    Start-SubTask:  Move To Point "));
		return true;
	}
	return false;
}

bool UTCheckPoint::CautionMoveToGoalPoint(AUnitAI* _OwnerAI)
{
	return true;
}

bool UTCheckPoint::TryLookToGoalPoint(AUnitAI* _OwnerAI)
{ 
	// ** GoalPoint too close
	FVector selfLocation = _OwnerAI->GetCurrSelfLocation();
	float distToPoint = FVector::Distance(selfLocation, GoalPoint);
	if (distToPoint < _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 10.f)
	{
		// ** is free vision (RayCast)
		FHitResult TraceHit;
		FCollisionQueryParams TraceParams(FName("Ray_Cast"), true, _OwnerAI->UnitOwner);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
		ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
		ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
		ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
		FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
		
		FRotator Rotation;
		FVector unitEyeLoc;
		_OwnerAI->GetPlayerViewPoint(unitEyeLoc, Rotation);
		GetWorld()->LineTraceSingleByObjectType(TraceHit, unitEyeLoc, GoalPoint, ObjectQueryParams, TraceParams);
		if (!TraceHit.bBlockingHit)
		{
			// ** Rotate-To-Point (is free vision)
			FTaskData SubTask;
			UTUnitRotate::SetRotateData_ToPoint(SubTask, _OwnerAI->UnitOwner, GoalPoint, EUnitPose::NormalMove);
			UE_LOG(LogTemp, Warning, TEXT("Task::CheckPoint,    Start-SubTask:  Rotate to point "));
			_OwnerAI->SetTask(false, ETaskType::Rotate, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
			return true; // ** do Rotate 
		}
	}
	return false; // ** need Move before
}


void UTCheckPoint::RotateOnAngle(AUnitAI* _OwnerAI, float _Angle)
{
	// ** Rotate-On-Angle 
	FTaskData SubTask;
	int32 sideToRotate = _Angle / FMath::Abs(_Angle);
	UTUnitRotate::SetRotateData_OnAngle(SubTask, _OwnerAI->UnitOwner, _Angle, sideToRotate, EUnitPose::NormalMove);
	UE_LOG(LogTemp, Warning, TEXT("Task::CheckPoint,    Start-SubTask:  Rotate on angle "));
	_OwnerAI->SetTask(false, ETaskType::Rotate, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
}


void UTCheckPoint::Wait(AUnitAI* _OwnerAI, float _Time)
{
	// ** Wait
	FTaskData SubTask;
	UTWait::SetTaskData_WaitParam(SubTask, _OwnerAI->UnitOwner, _Time);
	UE_LOG(LogTemp, Warning, TEXT("Task::CheckPoint,    Start-SubTask:  Wait  (_%f_)"), _Time);
	_OwnerAI->SetTask(false, ETaskType::Wait, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
}




bool UTCheckPoint::IdentifyTask(AUnitAI* _OwnerAI) 
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Uint8Param.Num() < 1)
		return false;
	if (task.Vector3dParam.Num() < 1)
		return false;
	
	TaskCaution = ETaskCaution(task.Uint8Param[0]);

	GoalPoint = task.Vector3dParam[0];

	return true;
}



// ** ----------------  Static func  ---------------



// ** No attention
void UTCheckPoint::SetTaskData_RelaxCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint)
{
	_TaskData.Uint8Param.Add(uint8(ETaskCaution::Relax));	// ** TaskCaution = Relax
	_TaskData.Vector3dParam.Add(_GoalPoint);				// ** GoalPoint
}


// ** Shasing somebody
void UTCheckPoint::SetTaskData_FastCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint)
{
	_TaskData.Uint8Param.Add(uint8(ETaskCaution::Vigilant));// ** TaskCaution = Vigilant
	_TaskData.Vector3dParam.Add(_GoalPoint);				// ** GoalPoint
}

// ** Slow but Mindful
void UTCheckPoint::SetTaskData_CautionCheckingPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _GoalPoint)
{
	_TaskData.Uint8Param.Add(uint8(ETaskCaution::Alert));	// ** TaskCaution = Alert
	_TaskData.Vector3dParam.Add(_GoalPoint);				// ** GoalPoint
}




