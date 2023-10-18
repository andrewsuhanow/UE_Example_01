

//#include "Task/TMoveToPoint.h"
#include "TMoveToPoint.h"

#include "../UnitAI.h"


UTMoveToPoint::UTMoveToPoint()
{
	TaskType = ETaskType::MoveToPoint;
}


void UTMoveToPoint::StartTask(AUnitAI* _OwnerAI)
{
	if (FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _OwnerAI->GetCurrTargetLocation()) > 120.f)
	{

		switch (TaskType)
		{
		// ** fast 
		case ETaskType::FastMoveToPoint:
			_OwnerAI->SetUnitMoveSpeed(300);
			break;
		// ** normal (depend Pose)
		case ETaskType::MoveToPoint:
			//++++++++++++ GetCurrentPoseSpeed		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// ++++++++
			_OwnerAI->SetUnitMoveSpeed(250);		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			break;
		// ** slow
		case ETaskType::BattleSideMove:
			_OwnerAI->SetUnitMoveSpeed(200);
			break;
		// ** normal (constant not to Pose)
		case ETaskType::BattleRetreatMove:
			_OwnerAI->SetUnitMoveSpeed(250);
			break;
		}

		TaskPerformance(_OwnerAI);
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTMoveToPoint::ContinueTask(AUnitAI* _OwnerAI)
{
	// **
	if (FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _OwnerAI->GetCurrTargetLocation()) > 120.f)
	{
		TaskPerformance(_OwnerAI);
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTMoveToPoint::TaskPerformance(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	bool bStopOnOverlap = false;
	bool bUsePathfinding = true;
	bool bDebugProjectile = false;	
	bool isStrafe = false;
	_OwnerAI->MoveToLocation(_OwnerAI->CurrTaskDTBuffer.Last().Location, 0 + 30.f - 30, bStopOnOverlap, bUsePathfinding, bDebugProjectile, isStrafe);

	// ** Start MoveTick()
	GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MoveTick, 0.1f, false);
}


void UTMoveToPoint::MoveTick()
{
	//if (! TURN_BASE)
	{
		float dist = FVector::Distance(OwnerAI->GetCurrSelfLocation(), OwnerAI->GetCurrTargetLocation());
		if (dist < 120.f)
		{
			GetWorld()->GetTimerManager().ClearTimer(TH_Move);
			TaskComplit(OwnerAI);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MoveTick, 0.001f * dist, false);
		}

	}
	//else
	{

	}
}


void UTMoveToPoint::TaskComplit(AUnitAI* _OwnerAI)
{

	_OwnerAI->UnitStopMove();
	//++++++++++++ GetCurrentPoseSpeed		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	_OwnerAI->SetUnitMoveSpeed(250);		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	if (FinishChildTask(_OwnerAI))
	{
		return;
	}
	else
	{
		if(!FinishGeneralTask(_OwnerAI))
			FinishDominantAITask(_OwnerAI);
	}
	_OwnerAI->UpdateLogic();
}


void UTMoveToPoint::BreakTask(AUnitAI* _OwnerAI)
{
	_OwnerAI->UnitStopMove();
	//++++++++++++ GetCurrentPoseSpeed		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	_OwnerAI->SetUnitMoveSpeed(250);		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	GetWorld()->GetTimerManager().ClearTimer(TH_Move);

	_OwnerAI->CurrTaskDTBuffer.Reset();
	_OwnerAI->CurrTaskRef = nullptr;

	_OwnerAI->UpdateLogic();
}


