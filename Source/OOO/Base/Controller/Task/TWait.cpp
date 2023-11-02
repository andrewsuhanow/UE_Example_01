

//#include "Task/TWait.h"
#include "TWait.h"

#include "../UnitAI.h"



UTWait::UTWait()
{
	TaskType = ETaskType::Wait;
}


void UTWait::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	if (_OwnerAI->CurrTaskDTBuffer.Num() > 0)
	{
		TimeLeft = _OwnerAI->CurrTaskDTBuffer.Last().Param1;

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