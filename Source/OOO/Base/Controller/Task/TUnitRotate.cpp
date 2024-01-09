

// #include "Base/Controller/Task/TUnitRotate.h"
#include "TUnitRotate.h"

#include "../../Unit/Base/Unit.h"
#include "../UnitAI.h"

#include "Kismet/KismetMathLibrary.h"

UTUnitRotate::UTUnitRotate()
{
	TaskType = ETaskType::Rotate;
}


void UTUnitRotate::StartTask(AUnitAI* _OwnerAI)
{

	IdentifyTask(_OwnerAI);

	// ** Case: rotate to point
	if (RotateSide == 0)
		GetAngleRotateToPoint(_OwnerAI, GoalPoint, Angle, RotateSide);	
	else
		GenerateGoalPoint(_OwnerAI, Angle, RotateSide, GoalPoint);


	if (TaskRotSpeed == EUnitPose::none)
		RotateSpeed = _OwnerAI->UnitOwner->GetRotateSpeedFromPose(_OwnerAI->UnitOwner->GetCurrUnitPose());
	else
		RotateSpeed = _OwnerAI->UnitOwner->GetRotateSpeedFromPose(TaskRotSpeed);


	_OwnerAI->UnitOwner->SetRotateSpeedFromVal(RotateSide * RotateSpeed);


	ContinueTask(_OwnerAI);
}


void UTUnitRotate::ContinueTask(AUnitAI* _OwnerAI)
{

	OwnerAI = _OwnerAI;

	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_Rotate))
	{
		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateTick, GetWorld()->GetDeltaSeconds(), false);
	}


}



void UTUnitRotate::RotateTick()
{

	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), GoalPoint);
	FRotator selfRotator = OwnerAI->GetCurrSelfRotation();
	selfRotator.Normalize();
	float rotDist = FMath::Abs((selfRotator.Yaw - newRotator.Yaw));
	FRotator deltaRotate = FMath::RInterpTo(OwnerAI->GetCurrSelfRotation(), newRotator, GetWorld()->GetDeltaSeconds(), RotateSpeed / rotDist);
	
	deltaRotate.Pitch = 0.f;
	deltaRotate.Roll = 0.f;
	OwnerAI->SetSelfRotation(deltaRotate);

	if (rotDist > 0.3f)
	{
		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateTick, GetWorld()->GetDeltaSeconds(), false);
	}
	else
	{
		TaskComplit(OwnerAI);
		UE_LOG(LogTemp, Warning, TEXT("____!!!!!!!!!!!!!!!!!!!!!!!!_____Rotate_FINISH__"), );
	}

}


void UTUnitRotate::TaskComplit(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::TaskComplit(_OwnerAI);
}


void UTUnitRotate::BreakTask(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::BreakTask(_OwnerAI);
}


void UTUnitRotate::ResetTask(class AUnitAI* _OwnerAI)
{

	RotateSide = 0;
	RotateSpeed = 0.f;
	Angle = 0.f;		

	_OwnerAI->UnitOwner->SetRotateSpeedFromVal(0.f);

	TaskRotSpeed = EUnitPose::none;
	GetWorld()->GetTimerManager().ClearTimer(TH_Rotate);
}


void UTUnitRotate::GetAngleRotateToPoint(class AUnitAI* _OwnerAI, FVector _GoalPoint, float &_AngleRef, int32 &_SideRef)
{

	float resultAngleInRadians = 0.0f;
	FVector selfPoint = _OwnerAI->GetCurrSelfLocation();
	FVector goalPoint = _GoalPoint;
	goalPoint.Z = selfPoint.Z;
	FVector firstVector = (goalPoint - selfPoint).GetSafeNormal(1.f);;	
	FVector secondVector = _OwnerAI->GetUnitForwardVector();

	FVector crossProduct = FVector::CrossProduct(firstVector, secondVector);
	float dotProduct = FVector::DotProduct(firstVector, secondVector);

	// ** Around Z-Axis
	if (crossProduct.Z > 0)
	{
		_SideRef = -1;
		_AngleRef = FMath::Abs(FMath::RadiansToDegrees(acosf(dotProduct)));
	}
	else
	{
		_SideRef = 1;
		_AngleRef = FMath::Abs(FMath::RadiansToDegrees(-1.f * acosf(dotProduct)));
	}

	if (Angle == 180.f)
		Angle = 179.9f;

}

void UTUnitRotate::GenerateGoalPoint(AUnitAI* _OwnerAI, float _Angle, int32 _Side, FVector& _GoalPointRef)
{
	_GoalPointRef = _OwnerAI->GetCurrSelfLocation() + 
		FRotator(0.f, _Angle * _Side, 0.f).
		RotateVector(_OwnerAI->GetUnitForwardVector()) * _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 3.f;
}


bool UTUnitRotate::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Uint8Param.Num() < 1)
		return false;

	// ** Speed (from PoseLocomotion) (uint8)
	TaskRotSpeed = EUnitPose(task.Uint8Param[0]);
	

	if (task.Vector3dParam.Num() >= 1)
	{
		GoalPoint = task.Vector3dParam[0];
		Angle = -1.f;		// ** No "Rotate to Ange"
		RotateSide = 0;		// ** No "Rotate to Ange"
	}
	else if(task.Int32Param.Num() >= 1 &&
			task.FloatParam.Num() >= 1)
	{
		RotateSide = task.Int32Param[0];

		Angle = FMath::Abs(task.FloatParam[0]);
		if (Angle == 180.f)
			Angle = 179.9f;
	}
	else
	{
		return false;
	}
	return true;
}




// ** ----------------  Static func  ---------------




void UTUnitRotate::SetRotateData_ToPoint(FTaskData& _TaskData, AActor* _TargetActor, FVector _GoalPoint, EUnitPose _Pose)
{
	// ** TaskRotSpeed (uint8 index = 1)
	if (_Pose != EUnitPose::none)
		_TaskData.Uint8Param.Add(uint8(_Pose));
	else
		_TaskData.Uint8Param.Add(uint8(EUnitPose::none));

	// ** GoalPoint
	_TaskData.Vector3dParam.Add(_GoalPoint);	
}



void UTUnitRotate::SetRotateData_OnAngle(FTaskData& _TaskData, AActor* _TargetActor, float _Angle, int32 _Side, EUnitPose _Pose)
{
	// ** TaskRotSpeed (uint8 index = 1)
	if (_Pose != EUnitPose::none)
		_TaskData.Uint8Param.Add(uint8(_Pose));
	else
		_TaskData.Uint8Param.Add(uint8(EUnitPose::none));

	// ** Angle & Rotate-Side
	_TaskData.Int32Param.Add(_Side);
	_TaskData.FloatParam.Add(_Angle);							
}
