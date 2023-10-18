

//#include "Task/TRotateToPointNormal.h"
#include "TRotateToPointNormal.h"

#include "../UnitAI.h"

#include "Kismet/KismetMathLibrary.h"

UTRotateToPointNormal::UTRotateToPointNormal()
{
	TaskType = ETaskType::RotateToPointNormal;
}


void UTRotateToPointNormal::StartTask(AUnitAI* _OwnerAI)
{
	
	switch (TaskType)
	{
		// ** fast 
	case ETaskType::RotateToPointFast:
		_OwnerAI->SetUnitRotateSpeed(3);
		break;
		// ** normal
	case ETaskType::RotateToPointNormal:
		_OwnerAI->SetUnitRotateSpeed(2);		
		break;
		// ** slow
	case ETaskType::RotateToPointSlow:
		_OwnerAI->SetUnitRotateSpeed(1);
		break;
	}



	FVector dir = (_OwnerAI->GetCurrTargetLocation() - _OwnerAI->GetCurrSelfLocation()).GetSafeNormal();
	float DeltaRotate = GetAngleRotateToPoint(_OwnerAI, dir);
	if (FMath::Abs(DeltaRotate) > 0.01f)
	{
		TaskPerformance(_OwnerAI);
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTRotateToPointNormal::ContinueTask(AUnitAI* _OwnerAI)
{
	FVector dir = (_OwnerAI->GetCurrTargetLocation() - _OwnerAI->GetCurrSelfLocation()).GetSafeNormal();
	float DeltaRotate = GetAngleRotateToPoint(_OwnerAI, dir);
	if (FMath::Abs(DeltaRotate) > 0.01f)
	{
		TaskPerformance(_OwnerAI);
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTRotateToPointNormal::TaskPerformance(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	// **
	FVector dir = (_OwnerAI->GetCurrTargetLocation() - _OwnerAI->GetCurrSelfLocation()).GetSafeNormal();

	float DeltaRotate = GetAngleRotateToPoint(_OwnerAI, dir);
	if (FMath::Abs(DeltaRotate) > 0.01f)
	{

		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateTick, 0.1f, false);

		return;
	}
}


void UTRotateToPointNormal::RotateTick()
{

	float mRotateSpeed = 2;  //7777777777777777777777777777@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	FRotator RotateSelf = OwnerAI->GetCurrSelfRotation();
	FRotator rotateToTarget;

	rotateToTarget = UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), OwnerAI->GetCurrTargetLocation());

	rotateToTarget.Roll = RotateSelf.Roll;
	rotateToTarget.Pitch = RotateSelf.Pitch;

	FVector vectorToTarget = UKismetMathLibrary::Conv_RotatorToVector(rotateToTarget);
	// ** float DeltaRotate = GetAngleRotateToPoint(PawnOwner, rotateToTarget);
	float DeltaRotate = GetAngleRotateToPoint(OwnerAI, vectorToTarget);

	// ** Stop Rotate
//++++++++++++++++++++++++++++++++++++++++++++++++++
/*
	if (FMath::Abs(DeltaRotate) < 0.01f)
	{
												// ** TEST
												{
													UE_LOG(LogTemp, Warning, TEXT("Unit: '%s'....................(Rotate  Stop)...........................: %f "), *PawnOwner->GetName(), ActionPoints);
												}

		if (ControllerOwner->CheckUnitState()) return;   // ** BehaviorComp->ResetActionState();

												if (IsDrawDebugHelper)
												{
													//UE_LOG(LogTemp, Warning, TEXT("(ACTION)  	Unit: '%s'	  ___ROTATE STOP___	  Round time left: %f "), *PawnOwner->GetName(), ActionPoints);
												}
		GetWorld()->GetTimerManager().ClearTimer(TH_Rotate);
		ControllerOwner->UpdateRoundDelay(GetWorld()->GetDeltaSeconds());
		return;
	}

	// ** Rotate
	else
	{
												// ** TEST
												{
													UE_LOG(LogTemp, Warning, TEXT("Unit: '%s'.....................(Rotate...)...........................: %f "), *PawnOwner->GetName(), ActionPoints);
												}

		FRotator newRotator = FMath::RInterpTo(RotateSelf, rotateToTarget, GetWorld()->GetDeltaSeconds(), mRotateSpeed);

		PawnOwner->SetActorRotation(newRotator, ETeleportType::TeleportPhysics);
		// 77777777 !!!!!!!!!!!!! 777777777777   ContinueTaskDelay(GetWorld()->GetDeltaSeconds());
		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateAction, GetWorld()->GetDeltaSeconds(), false);
	}
*/

// **************    "RIGHT" Rotate    **************
	if (DeltaRotate > 0.01f)
	{
		//++++++++@@@@@@@@@@@@@@@@@@@@+++++++++ ControllerOwner->SetRotateSpeed(-mRotateSpeed);   AnimInstanceAnimate
		FRotator newRotator = FMath::RInterpTo(RotateSelf, rotateToTarget, GetWorld()->GetDeltaSeconds(), mRotateSpeed * 2.5f);

		OwnerAI->SetSelfRotation(newRotator);
		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateTick, GetWorld()->GetDeltaSeconds(), false);
	}

	// **************    "LEFT" Rotate    **************
	else if (DeltaRotate < -0.01f)
	{

		//+++++++++@@@@@@@@@@@@@@@@@@++++++++ ControllerOwner->SetRotateSpeed(mRotateSpeed);   AnimInstanceAnimate
		FRotator newRotator = FMath::RInterpTo(RotateSelf, rotateToTarget, GetWorld()->GetDeltaSeconds(), mRotateSpeed * 2.5f);

		OwnerAI->SetSelfRotation(newRotator);
		GetWorld()->GetTimerManager().SetTimer(TH_Rotate, this, &ThisClass::RotateTick, GetWorld()->GetDeltaSeconds(), false);
	}

	// **************    "STOP" Rotate    **************
	else
	{
		// ** STOR Rotate
		
		GetWorld()->GetTimerManager().ClearTimer(TH_Rotate);
		TaskComplit(OwnerAI);

		//++++++++@@@@@@@@@@@@@@+++++++++ ControllerOwner->SetRotateSpeed(0.f);   AnimInstanceAnimate

		return;
	}


}


void UTRotateToPointNormal::TaskComplit(AUnitAI* _OwnerAI)
{

	_OwnerAI->SetUnitRotateSpeed(0);


	if (FinishChildTask(_OwnerAI))
	{
		return;
	}
	else
	{
		if (!FinishGeneralTask(_OwnerAI))
			FinishDominantAITask(_OwnerAI);
	}
	_OwnerAI->UpdateLogic();
}


void UTRotateToPointNormal::BreakTask(AUnitAI* _OwnerAI)
{

	_OwnerAI->SetUnitRotateSpeed(0);


	GetWorld()->GetTimerManager().ClearTimer(TH_Rotate);

	_OwnerAI->CurrTaskDTBuffer.Reset();
	_OwnerAI->CurrTaskRef = nullptr;

	_OwnerAI->UpdateLogic();
}





float UTRotateToPointNormal::GetAngleRotateToPoint(class AUnitAI* _OwnerAI, FVector _VectorToTarget)
{
	/// +++++++  FVector Vector_ToTarget = UKismetMathLibrary::Conv_RotatorToVector(_RotToTarget);

	// ** Target Right: +0  
	// ** Target  Left: -0
	FVector SelfRightVec = _OwnerAI->GetUnitRightVector();
	float  Side = FVector::DotProduct(SelfRightVec.GetSafeNormal(), _VectorToTarget);

	FVector SelfForwardVec = _OwnerAI->GetUnitForwardVector(); /// UKismetMathLibrary::Conv_RotatorToVector(_SelfPawn->GetActorRotation()); //
	float  rotate = FVector::DotProduct(SelfForwardVec.GetSafeNormal(), _VectorToTarget);

	float result = 0;

	// *********  On Back  *********
	if (rotate < 0)
	{
		if (Side >= 0)
			result = 1.f - rotate;
		else
			result = -1.f * (1.f - rotate);
	}
	// *********  On Front  *********
	else
	{
		// ** Right
		if (Side >= 0)
			result = 1.f - rotate;
		else
			result = -1.f * (1.f - rotate);
	}
	///FRotator DeltaRotate = FRotator::MakeFromEuler(_SelfRot.Euler() - _RotToTarget.Euler());
	///if (DeltaRotate.Yaw < -180.f) DeltaRotate.Yaw = 360 + DeltaRotate.Yaw;
	///if (DeltaRotate.Yaw > 180.f) DeltaRotate.Yaw = -360 + DeltaRotate.Yaw;
	///return DeltaRotate;
	return result;
}