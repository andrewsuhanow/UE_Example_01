

//#include "Task/TWait.h"
#include "TWait.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"


UTWait::UTWait()
{
	TaskType = ETaskType::Wait;

	// ** FTaskData::Param1[0]  -  Waiting time
}


void UTWait::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	if (_OwnerAI->TasksBuffer.Num() > 0)
	{
		IdentifyTask(_OwnerAI);		// ** Waiting param
		
		if (TimeLeft > 0.f)
		{
			WaitTick();
		}
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
}


void UTWait::ContinueTask(AUnitAI* _OwnerAI)
{
	/*  (-------------------------)
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	if(TimeLeft > 0.f)
	{
		WaitTick();
	}
	else
	{
		TaskComplit(_OwnerAI);
	}
	*/
}


void UTWait::WaitTick()
{
	//if (! TURN_BASE)
	{
		if (TimeLeft > 0.f)
		{
			TimeLeft -= GetWorld()->GetDeltaSeconds();
			GetWorld()->GetTimerManager().SetTimer(TH_Wait, this, &ThisClass::WaitTick, GetWorld()->GetDeltaSeconds(), false);			
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TH_Wait);
			TaskComplit(OwnerAI);
		}

	}
	//else
	{

	}
}



void UTWait::TaskComplit(AUnitAI* _OwnerAI)
{
	GetWorld()->GetTimerManager().ClearTimer(TH_Wait);

	Super::TaskComplit(_OwnerAI);
}


void UTWait::BreakTask(AUnitAI* _OwnerAI)
{
	GetWorld()->GetTimerManager().ClearTimer(TH_Wait);

	Super::BreakTask(_OwnerAI);
}




bool UTWait::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.FloatParam.Num() == 0)
		return false;

	//---if(TimeLeft <= 0.f)
	TimeLeft = task.FloatParam[0];

	return true;
}


// ** ----------------  Static func  ---------------


void UTWait::SetTaskData_WaitParam(FTaskData& _TaskData, AUnit* _SelfUnit, float _Time)
{
	_TaskData.FloatParam.Add(_Time);
}