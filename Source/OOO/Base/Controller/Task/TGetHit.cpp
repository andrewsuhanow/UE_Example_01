

//#include "Task/TGetHit.h"
#include "TGetHit.h"

#include "../UnitAI.h"


UTGetHit::UTGetHit()
{
	TaskType = ETaskType::GetHit;
}


void UTGetHit::StartTask(AUnitAI* _OwnerAI)
{
/*	StopDistance = _OwnerAI->GetUnitStopDistance();
	if (StopDistance < FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _OwnerAI->GetCurrTargetLocation()))
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
*/
}


void UTGetHit::ContinueTask(AUnitAI* _OwnerAI)
{
	// **
	if (StopDistance < FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _OwnerAI->GetCurrTargetLocation()))
	{
		TaskPerformance(_OwnerAI);
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTGetHit::TaskPerformance(AUnitAI* _OwnerAI)
{
/*	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	bool bStopOnOverlap = false;
	bool bUsePathfinding = true;
	bool bDebugProjectile = false;	
	bool isStrafe = false;
	_OwnerAI->MoveToLocation(_OwnerAI->CurrTaskDTBuffer.Last().Location, 0 + 30.f - 30, bStopOnOverlap, bUsePathfinding, bDebugProjectile, isStrafe);

	// ** Start MoveTick()
	GetWorld()->GetTimerManager().SetTimer(TH_Move, this, &ThisClass::MoveTick, 0.1f, false);
	*/
}


void UTGetHit::MoveTick()
{
/*	//if (! TURN_BASE)
	{
		float dist = FVector::Distance(OwnerAI->GetCurrSelfLocation(), OwnerAI->GetCurrTargetLocation());
		if (StopDistance > dist)
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
	*/
}


void UTGetHit::TaskComplit(AUnitAI* _OwnerAI)
{

	_OwnerAI->UnitStopMove();
	///++++++++++++ GetCurrentPoseSpeed		/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	_OwnerAI->SetUnitMoveSpeed(250);		/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	Super::TaskComplit(_OwnerAI);
}


void UTGetHit::BreakTask(AUnitAI* _OwnerAI)
{

	_OwnerAI->UnitStopMove();
	///++++++++++++ GetCurrentPoseSpeed		/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	_OwnerAI->SetUnitMoveSpeed(250);		/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	GetWorld()->GetTimerManager().ClearTimer(TH_Move);

	Super::BreakTask(_OwnerAI);
}


