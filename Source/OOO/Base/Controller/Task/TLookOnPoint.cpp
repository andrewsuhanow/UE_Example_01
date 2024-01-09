

//#include "Task/TLookOnPoint.h"
#include "TLookOnPoint.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"


UTLookOnPoint::UTLookOnPoint()
{
	TaskType = ETaskType::CheckPoint;

	// ** FTaskData::Param1[0]  -  Waiting time
}


void UTLookOnPoint::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;


}


void UTLookOnPoint::ContinueTask(AUnitAI* _OwnerAI)
{

}




void UTLookOnPoint::TaskComplit(AUnitAI* _OwnerAI)
{


	Super::TaskComplit(_OwnerAI);
}


void UTLookOnPoint::BreakTask(AUnitAI* _OwnerAI)
{


	Super::BreakTask(_OwnerAI);
}




bool UTLookOnPoint::IdentifyTask(AUnitAI* _OwnerAI)
{
/*
	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.FloatParam.Num() == 0)
		return false;
*/

	return true;
}


// ** ----------------  Static func  ---------------

/*
void UTLookOnPoint::SetTaskData_WaitParam(FTaskData& _TaskData, AUnit* _SelfUnit, float _Time)
{
	_TaskData.FloatParam.Add(_Time);
}
*/




















////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////




/*


// **     LOOK TO POINT
void UBaseBehavior::Action_LookToPoint(AUnitAI* _Controller, APawn* _Pawn, FVector _Location)
{

	if (IsPlayingAnimation())
	{
		____TEST_LOG____SELF____BT("......UBaseBehavior:::(Behavior-Loop)__UPDATE___Delay................0000000012..........-30-...");
		ContinueTaskDelay(1.f);
		return;
	}


	if (_Controller) { ControllerOwner = _Controller; ____TEST_LOG____SELF____BT("...........###########........Behavior::Action_LookToPoint()........."); }

	// ** Rotate

		SetCurrTarget(nullptr);
		_Controller->ClearFocus(EAIFocusPriority::Gameplay);

		_Controller->ActionParallelSTATE_TMP = EActionState::none;
		_Controller->ActionSTATE_TMP = EActionState::ChackingPoint_SimpleLook;

		GetWorld()->GetTimerManager().ClearTimer(TH_BehaviorLoop);


		SetCurrTargetLocation(_Location);
		FVector selfPosition = _Pawn->GetActorLocation();
		FVector dir = (_Location - selfPosition).GetSafeNormal();
		NormalRotateToPoint(dir);


		//++mCheckingPointAction;
		++mCheckingPointAction = 0;
}

bool UBaseBehavior::Action_LookToPoint_Continue(AUnitAI* _Controller, APawn* _Pawn)
{
	// ** Wait
	if (mCheckingPointAction == 0)
	{
		++mCheckingPointAction;
		GetWorld()->GetTimerManager().SetTimer(_Controller->TH_CheckThePointDelay, _Controller, &AUnitAI::Comand_LookToPoint_Continue, RoundTime, false);
	}
	// ** Look Side
	else if (mCheckingPointAction == 1)
	{
		++mCheckingPointAction;
		FVector LookingPoint = _Pawn->GetActorLocation() + _Pawn->GetActorRightVector() * (GetCapsuleRadius_Self() + 100.f);
		SetCurrTargetLocation(LookingPoint);
		//bool a1_TEMP;
		//-------NormalRotateToPoint(GetCurrTargetLocation(a1_TEMP));
		//FVector selfPosition = _Pawn->GetActorLocation();
		//FVector dir = selfPosition + (GetCurrTargetLocation(a1_TEMP) - selfPosition).GetSafeNormal() * 200.f;
		FVector dir = _Pawn->GetActorRightVector();
		NormalRotateToPoint(dir);
	}
	// ** Wait
	else if (mCheckingPointAction == 2)
	{
		++mCheckingPointAction;
		GetWorld()->GetTimerManager().SetTimer(_Controller->TH_CheckThePointDelay, _Controller, &AUnitAI::Comand_LookToPoint_Continue, RoundTime, false);
	}
	// ** Look Back
	else if (mCheckingPointAction == 3)
	{
		++mCheckingPointAction;
		FVector LookingPoint = _Pawn->GetActorLocation() + (-1.f) * _Pawn->GetActorForwardVector() * (GetCapsuleRadius_Self() + 100.f);
		SetCurrTargetLocation(LookingPoint);
		//bool a1_TEMP;
		//---------NormalRotateToPoint(GetCurrTargetLocation(a1_TEMP));
		//FVector selfPosition = _Pawn->GetActorLocation();
		//FVector dir = selfPosition + (GetCurrTargetLocation(a1_TEMP) - selfPosition).GetSafeNormal() * 200.f;
		//NormalRotateToPoint(dir);
		FVector dir = _Pawn->GetActorForwardVector() * (-1);
		NormalRotateToPoint(dir);

	}
	// ** Wait
	else if (mCheckingPointAction == 4)
	{
		++mCheckingPointAction;
		GetWorld()->GetTimerManager().SetTimer(_Controller->TH_CheckThePointDelay, _Controller, &AUnitAI::Comand_LookToPoint_Continue, RoundTime, false);
	}
	else if (mCheckingPointAction == 5)
	{
		____TEST_LOG____SELF____BT("...........###########...Behavior::Action_LookToPoint_Continue()...............(RESET Action)........");

		mCheckingPointAction = 0;
		//+++++++++++++++++++++++++++++++++++++++++_Controller->ResetActionState();
		if (GetCurrTarget() == nullptr)
			_Controller->RemoveStimuls();
		//_Controller->UpdateRoundDelay(GetWorld()->GetDeltaSeconds());
		_Controller->ActionSTATE_TMP = EActionState::DoDailyBehavior;
		_Controller->ActionParallelSTATE_TMP = EActionState::none;

		return true; // ** Action finish
	}

	return false; // ** Action continue
}


*/