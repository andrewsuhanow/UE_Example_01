﻿


// **********************
// **********************   NEED  Refactoring  (now unit move to Location(only) or to ActorTargetLocation)
// **********************
// **********************	Need  Tracing the UnitTargert and stop before UnitTargert on dist
// **********************

// ** #include "Base/Controller/Task/TMoveTo.h"

#include "TMoveTo.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"

#include "../../WorldMarker/WorldPathMarker.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"







UTMoveTo::UTMoveTo()
{
	TaskType = ETaskType::MoveTo;

}

void UTMoveTo::InitPathMarker(AUnitAI* _OwnerAI)
{
	PathMarker = GetWorld()->SpawnActor<AWorldPathMarker>();
	PathMarker->AttachToActor(_OwnerAI->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform);
	PathMarker->SetActorLocation(_OwnerAI->GetPawn()->GetActorLocation());
}

void UTMoveTo::StartTask(AUnitAI* _OwnerAI)
{
	ContinueTask(_OwnerAI);
}


void UTMoveTo::ContinueTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	// ** 
	if (!IdentifyTask(_OwnerAI))
	{
		TaskComplit(_OwnerAI);
		return;
	}
	else
	{
		if (TargetActor)
			GoalLocation = TargetActor->GetActorLocation();
	}
	

	// ** pose
	if (NewPose != EUnitPose::none)
		_OwnerAI->UnitOwner->SetPose(NewPose);

	// **  Speed
	if(NewSpeed != -1.f)
		_OwnerAI->SetUnitMoveSpeed(NewSpeed);

	// ** Focus
	if (bFixRotOnTarget && FocusingActor)
		_OwnerAI->SetFocus(FocusingActor);


	// ** Move Performance
	float currDistToTarget = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), GoalLocation);
	if (StopDistance < currDistToTarget)
	{
		MoveActorPerformance();

/*		if (TargetActor)
		{
			MoveActorPerformance();
		}
		else
		{
			//MovePointPerformance();
		}
*/
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTMoveTo::MovePointPerformance()
{
	//OwnerAI->MoveToLocation(GoalLocation, stopDist, bStopOnOverlap, bUsePathfinding, bDebugProjectile, сanStrafeMove);

	float dist = FVector::Distance(OwnerAI->GetCurrSelfLocation(), GoalLocation);
	if (StopDistance > dist)
	{
		TaskComplitDelay(OwnerAI);
		return;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MovePointPerformance, 0.001f * dist, false); // ** GetWorld()->GetDeltaSeconds() * 0.1f
	}
}




void UTMoveTo::MoveActorPerformance()
{
	
	// ** first generate or update
	if (!IsNavPathGenerate(OwnerAI))
	{
		GenerateNavPath(OwnerAI);
	}

	// ** if something wrong
	if (!IsNavPathGenerate(OwnerAI) || PathPointsMum <= 1)
	{
		TaskComplit(OwnerAI);
		return;
	}

	// ** Check Target moving
	if (TargetUnit)
	{
		float deltaTargetLocation = FVector::Distance(LastTargetLocation, TargetUnit->GetActorLocation());
		if (deltaTargetLocation > TargetUnit->GetUnitCapsuleRadius())
		{
			IsPathMarkersGenerated = false;
			MoveActorPerformance();
			return;
		}
	}



	
	// ** Total finish   (dist to final goal-point)
	float dist = FVector::Distance(OwnerAI->GetCurrSelfLocation(), GoalLocation);
	if (StopDistance > dist)
	{
		TaskComplitDelay(OwnerAI);
		return;
	}


	// ** path segment finish
	dist = FVector::Distance(OwnerAI->GetCurrSelfLocation(), NextMiddlePathPoint);
	if (StopDistance > dist)
	{
		// ** if Path has next point
		if (NextMiddlePathindex < PathPointsMum - 1) 
		{
			bool сanStrafeMove = false;	// ** 77777
			bool bDebugProjectile = false;
			bool bAllowPartialPath = true;
			float stopDist = 0;
			
			++NextMiddlePathindex;
			NextMiddlePathPoint = Path[NextMiddlePathindex];

			///OwnerAI->MoveToActor(TargetActor, stopDist, bStopOnOverlap, bUsePathfinding, bCanStrafeMove, nullptr, bAllowPartialPath);
			OwnerAI->MoveToLocation(NextMiddlePathPoint, stopDist, bStopOnOverlap, bUsePathfinding, bDebugProjectile, сanStrafeMove);
			GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MoveActorPerformance, 0.001f * dist, false);
		}	
		else
		{
			TaskComplitDelay(OwnerAI);
			return;
		}
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MoveActorPerformance, 0.001f * dist, false);
	}


	// ** Draw path or not
	DrawNavPathMarker(OwnerAI);
}


void UTMoveTo::TaskComplitDelay(AUnitAI* _OwnerAI)
{
	GetWorld()->GetTimerManager().ClearTimer(TH_Move);

	if (IsNeedWaitingAfterStop) /// ** Bit waiting after Stop
		GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::WaitingAfterStop,
			15.0f * GetWorld()->GetDeltaSeconds(), false);
	else
		TaskComplit(OwnerAI);
}

void UTMoveTo::WaitingAfterStop()
{
	TaskComplit(OwnerAI);
}



void UTMoveTo::TaskComplit(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::TaskComplit(_OwnerAI);
}



void UTMoveTo::BreakTask(AUnitAI* _OwnerAI)
{
	
	ResetTask(_OwnerAI);

	Super::BreakTask(_OwnerAI);
}



void UTMoveTo::ResetTask(AUnitAI* _OwnerAI)
{
	GetWorld()->GetTimerManager().ClearTimer(TH_Move);

	_OwnerAI->UnitStopMove();
	_OwnerAI->ClearFocus(EAIFocusPriority::Gameplay);

	TargetUnit = nullptr;
	TargetActor = nullptr;
	StopDistance = 0.f;

	// ** Last pose
	if (LastPose != EUnitPose::none)
		_OwnerAI->UnitOwner->SetPose(LastPose);

	LastPose = EUnitPose::none;
	NewPose = EUnitPose::none;

	_OwnerAI->UnitOwner->bUseControllerRotationYaw = true;

	// ** Last Speed
	if (NewSpeed != -1.f)
		_OwnerAI->SetUnitMoveSpeed(LastSpeed);


	// ** Path
	HideNavPathMarkers(_OwnerAI);
	DrawPathType = EDrawPathType::none;
	IsPathMarkersGenerated = false;
	PathPointsMum = -1;
	NextMiddlePathindex = -1;
}


//  --------------------------------------------------------------


bool UTMoveTo::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Uint8Param.Num() < 3)
		return false;

	ETacticalMoveType tacticalMoveType = ETacticalMoveType(task.Uint8Param[0]);

	
	// ** Stop distance (float)
	StopDistance = task.FloatParam[0] + _OwnerAI->UnitOwner->StopDistance;

	// ** new pose (uint8)
	NewPose = EUnitPose(task.Uint8Param[1]);
	if (NewPose != EUnitPose::none)
	{
		LastPose = _OwnerAI->UnitOwner->GetCurrUnitPose();
	}

	// ** bit wait after move
	IsNeedWaitingAfterStop = bool(task.Uint8Param[2]);

	// ** 
	bUsePathfinding = true;


	switch (tacticalMoveType)
	{
		case ETacticalMoveType::SimpleMoveToPoint:

			if (task.Vector3dParam.Num() == 0)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = true; // ** bCanStrafeMove = false;
			bStopOnOverlap = false;
			bFixRotOnTarget = false;

			GoalLocation = task.Vector3dParam[0];		// ** GoalPoint
			break;

		case ETacticalMoveType::MoveToPointWithUnitFocus:
		{

			if (task.Vector3dParam.Num() == 0)
				return false;
			if (task.Actor.Num() == 0)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = true; // ** bCanStrafeMove = false;
			bStopOnOverlap = false;
			bFixRotOnTarget = true;						// ** Focus on target

			GoalLocation = task.Vector3dParam[0];		// ** GoalPoint

			// ** Focusing actor
			FocusingActor = task.Actor[0];
			AUnit* checkFocusingOnUnit = Cast<AUnit>(TargetActor);
			if (checkFocusingOnUnit) TargetUnit = checkFocusingOnUnit;
			break;
		}
		case ETacticalMoveType::MoveToPointWithRotateFix:

			if (task.Vector3dParam.Num() == 0)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = false; // ** bCanStrafeMove = false;	// ** Strafe move
			bStopOnOverlap = false;
			bFixRotOnTarget = false;

			GoalLocation = task.Vector3dParam[0];		// ** GoalPoint
			break;




		case ETacticalMoveType::SimpleMoveToActor:
		{

			if (task.Actor.Num() == 0)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = true; // ** bCanStrafeMove = false;
			bStopOnOverlap = true;
			bFixRotOnTarget = false;

			// ** Target actor
			TargetActor = task.Actor[0];
			AUnit* checkTargetOnUnit = Cast<AUnit>(TargetActor);
			if (checkTargetOnUnit)	TargetUnit = checkTargetOnUnit;
			break;
		}
		case ETacticalMoveType::MoveToActorWithUnitFocus:
		{
			if (task.Actor.Num() < 2)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = true; // ** bCanStrafeMove = false;
			bStopOnOverlap = true;
			bFixRotOnTarget = true;						// ** Focus on target

			// ** Target actor
			TargetActor = task.Actor[0];
			AUnit* checkTargetOnUnit = Cast<AUnit>(TargetActor);
			if (checkTargetOnUnit)	TargetUnit = checkTargetOnUnit;

			// ** Focusing actor
			FocusingActor = task.Actor[1];
			AUnit* checkFocusingOnUnit = Cast<AUnit>(FocusingActor);
			if (checkFocusingOnUnit) FocusingActor = checkFocusingOnUnit;
			break;
		}
		case ETacticalMoveType::MoveToActorWithRotateFix:
		{
			if (task.Actor.Num() == 0)
				return false;

			_OwnerAI->UnitOwner->bUseControllerRotationYaw = false; // ** bCanStrafeMove = false;	// ** Strafe move
			bStopOnOverlap = true;
			bFixRotOnTarget = false;

			// ** Target actor
			TargetActor = task.Actor[0];
			AUnit* checkTargetOnUnit = Cast<AUnit>(TargetActor);
			if (checkTargetOnUnit)	TargetUnit = checkTargetOnUnit;
			break;
		}
	}

	return true;
}




// --------   static function  --------


bool UTMoveTo::SetMoveData_MoveToPoint(FTaskData& _TaskData, AUnit* _SelfUnit, FVector _TargetPoint,
	float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if (!_SelfUnit)
		return false;

	// ** New pose  (uint8 index = 0)
	_TaskData.Uint8Param.Add(uint8(ETacticalMoveType::SimpleMoveToPoint));

	// ** Goal point (vector index = 0)
	_TaskData.Vector3dParam.Add(_TargetPoint);										

	// ** Stop distance (float index = 0)
	_TaskData.FloatParam.Add(_StopDist);											

	// ** New pose  (uint8 index = 1)
	if (_Pose != EUnitPose::none)
		_TaskData.Uint8Param.Add(uint8(_Pose));
	else
		_TaskData.Uint8Param.Add(uint8(EUnitPose::none));

	// ** Is need wait after move  (uint8 index = 2)
	_TaskData.Uint8Param.Add(uint8(_IsWaitAfterMove));

	return true;
}


bool UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(FTaskData& _TaskData, AUnit* _SelfUnit,
	FVector _TargetPoint, AActor* _FocusingActor, float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if (!UTMoveTo::SetMoveData_MoveToPoint(_TaskData, _SelfUnit, _TargetPoint, 
		_StopDist, _Pose, _IsWaitAfterMove))
		return false;

	_TaskData.Uint8Param[0] = uint8(ETacticalMoveType::MoveToPointWithUnitFocus);

	// ** focusing actor
	_TaskData.Actor.Add(_FocusingActor);
	return true;
}

bool UTMoveTo::SetMoveData_MoveToPointWithRotateFix(FTaskData& _TaskData, AUnit* _SelfUnit,
	FVector _TargetPoint, float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if (!UTMoveTo::SetMoveData_MoveToPoint(_TaskData, _SelfUnit, _TargetPoint, 
		_StopDist, _Pose, _IsWaitAfterMove))
		return false;

	_TaskData.Uint8Param[0] = uint8(ETacticalMoveType::MoveToPointWithRotateFix);

	return true;
}












bool UTMoveTo::SetMoveData_MoveToActor(FTaskData& _TaskData, AUnit* _SelfUnit, AActor* _TargetActor,
	float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if (!_SelfUnit || !_TargetActor)
		return false;

	_TaskData.Uint8Param.Add(uint8(ETacticalMoveType::SimpleMoveToActor));

	// ** Stop distance  (float index = 0)
	_TaskData.FloatParam.Add(_StopDist);											

	// ** New pose  (uint8 index = 1)
	if (_Pose != EUnitPose::none)
		_TaskData.Uint8Param.Add(uint8(_Pose));
	else
		_TaskData.Uint8Param.Add(uint8(EUnitPose::none));

	// ** Is need wait after move  (uint8 index = 2)
	_TaskData.Uint8Param.Add(uint8(_IsWaitAfterMove));

	// ** Actor to move  (AActor/AUnit index = 0)
	_TaskData.Actor.Add(_TargetActor);

	return true;
}


bool UTMoveTo::SetMoveData_MoveToActorWithUnitFocus(FTaskData& _TaskData, AUnit* _SelfUnit,
	AActor* _TargetActor, AActor* _FocusingActor, float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if (!UTMoveTo::SetMoveData_MoveToActor(_TaskData, _SelfUnit, _TargetActor,
		_StopDist, _Pose, _IsWaitAfterMove))
		return false;

	_TaskData.Uint8Param[0] = uint8(ETacticalMoveType::MoveToActorWithUnitFocus);

	if (!_FocusingActor)
		return false;
	// ** focusing actor (AActor/Unit index = 1)
	_TaskData.Actor.Add(_FocusingActor);

	return true;
}

bool UTMoveTo::SetMoveData_MoveToActorWithRotateFix(FTaskData& _TaskData, AUnit* _SelfUnit,
	AActor* _TargetActor, float _StopDist, EUnitPose _Pose, bool _IsWaitAfterMove)
{
	if(!UTMoveTo::SetMoveData_MoveToActor(_TaskData, _SelfUnit, _TargetActor, _StopDist, 
		_Pose, _IsWaitAfterMove))
		return false;

	_TaskData.Uint8Param[0] = uint8(ETacticalMoveType::MoveToActorWithRotateFix);

	return true;
}







// **********************     Path    **********************

bool UTMoveTo::GenerateNavPath(AUnitAI* _OwnerAI, bool _UseSpecialPoint, FVector _GoalPoint)
{

	if (TargetActor)
	{
		GoalLocation = TargetActor->GetActorLocation();
		LastTargetLocation = GoalLocation;
	}


	FVector goalPoint = GoalLocation;
	if(_UseSpecialPoint)
		goalPoint = _GoalPoint;


	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* path = NavSys->FindPathToLocationSynchronously(GetWorld(), 
		_OwnerAI->GetCurrSelfLocation(), goalPoint, nullptr);
	////////////////////path->PathPoints->GetPathLength()
	////////////////////	path->PathPoints->GetPathCost()
	////////////////////	path->PathPoints->IsPartial()


	if (path != nullptr)
	{
		int32 PathPointsCount = path->PathPoints.Num();
		if (PathPointsCount == 1)
			return false;

		// ** In Detail path
		if (_OwnerAI->IsTurnBaseMode())
		{
			// @@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@  Calcukate Cleat Path
			// @@@@@@@@@@@@@@@
		}
		// ** Soft path
		else
		{
			Path.Reset();
			for (int32 i = 0; i < PathPointsCount; ++i)
			{
				Path.Add(path->PathPoints[i]);
			}
		}

		PathPointsMum = Path.Num();
		IsPathMarkersGenerated = true;
		NextMiddlePathindex = 0;
		NextMiddlePathPoint = Path[NextMiddlePathindex];

		return IsPathMarkersGenerated;
	}

	PathPointsMum = -1;
	IsPathMarkersGenerated = false;

	return IsPathMarkersGenerated;
}


void UTMoveTo::DrawNavPathMarker(AUnitAI* _OwnerAI)//, bool _IsDrawFullPath)
{
	// ** Unit dont selected
	if (_OwnerAI->UnitOwner->GetIsUnitSelected() == false)
		return;



	if (_OwnerAI->IsTurnBaseMode())
	{
		// @@@@@@@@@@@@@@@
		// @@@@@@@@@@@@@@@
		DrawPathType = EDrawPathType::FullPathPoint;
	}

	// ** Rwal-Time
	else
	{
		// ** Single Unit
		if (_OwnerAI->UnitOwner->IsUnitInGroup() == false)
		{
			PathMarker->DrawPathLine(Path, this);
			DrawPathType = EDrawPathType::FullPath;
		}

		// ** Group Units
		else
		{
			// @@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@
			DrawPathType = EDrawPathType::EndPoint;
		}
	}




	
}

bool UTMoveTo::IsNavPathGenerate(AUnitAI* _OwnerAI)
{
	return IsPathMarkersGenerated;
}

void UTMoveTo::HideNavPathMarkers(AUnitAI* _OwnerAI)
{
	DrawPathType = EDrawPathType::none;
	PathMarker->StopDraw();
}

bool UTMoveTo::GetNextMiddlePathPoint()
{
	//Path

	return false;
}




















