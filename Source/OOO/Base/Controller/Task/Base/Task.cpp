

// ** #include "Base/Controller/Task/Base/Task.h"
#include "Task.h"

#include "../../UnitAI.h"




// (-----------------------------)
/*
void UTask::SetDataGoalLocation(FTaskData& _TaskData, FVector _GoalLocation)
{
	while (_TaskData.Location.Num() < 1)
	{
		_TaskData.Location.Add(FVector(0.f, 0.f, 0.f));
	}
	_TaskData.Location[0] = _GoalLocation;
}
*/





void UTask::OnFinishAnimation(AUnitAI* _OwnerAI, UAnimMontage* FinishedAnimMontage, bool _bInterrupted)
{
	_OwnerAI->UpdateLogic();
}


void UTask::TaskComplit(AUnitAI* _OwnerAI)
{
	int32 buferTaskNum = _OwnerAI->TasksBuffer.Num();

	// ** finish child-Task (if has) 
	if (buferTaskNum >= 2)
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     SubTask complit"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->TasksBuffer.RemoveAt(buferTaskNum - 1);
		_OwnerAI->CurrTaskRef = _OwnerAI->TasksBuffer.Last().TaskRef;
		GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);
	}

	// ** if it's User-Queue-Task has just done (Player Comand)
	else
	if (buferTaskNum == 1 && 
		_OwnerAI->TasksBuffer.Last().TaskCauser == ETaskCauser::FractionTask)
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     Task complit"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------
			
		if (_OwnerAI->FractionQueueTaskDT.Num() > 0)
			_OwnerAI->FractionQueueTaskDT.RemoveAt(0);	
		_OwnerAI->TasksBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;
		GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);
	}

	// ** finish Other-Task (AIComand, DominantComand, DailyTask)
	else
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     Task complit"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->TasksBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;
		GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);
	}

	return;

}



void UTask::BreakTask(AUnitAI* _OwnerAI)
{

	// ** if player Task => delete from Queue
	if (_OwnerAI->TasksBuffer.Last().TaskCauser == ETaskCauser::FractionTask &&
		_OwnerAI->FractionQueueTaskDT.Num() > 0)
	{
		_OwnerAI->FractionQueueTaskDT.RemoveAt(0);
	}

	// ** Reset Task-Buffer
	_OwnerAI->TasksBuffer.Reset();
	_OwnerAI->CurrTaskRef = nullptr;
	GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);



/*

	int32 buferTaskNum = _OwnerAI->TasksBuffer.Num();

	// ** finish child-Task (if has) 
	if (buferTaskNum >= 2)
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>    Break Sub-Task"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->TasksBuffer.RemoveAt(buferTaskNum - 1);
		_OwnerAI->CurrTaskRef = _OwnerAI->TasksBuffer.Last().TaskRef;
		_OwnerAI->CurrTaskRef->BreakTask(_OwnerAI);
		// ** _OwnerAI->UpdateLogic();
		return;
	}
	

	// ** if it's User-Queue-Task has just beak (Player Comand)
	else
	if (buferTaskNum == 1 && 
		_OwnerAI->TasksBuffer.Last().TaskCauser == ETaskCauser::FractionTask)
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     Task complit"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		//---777---if (_OwnerAI->FractionQueueTaskDT.Num() > 0)			// ** @@@@@@@@@@@@@@@@@@@@@@@  Dont delete First-Queue-Task when last task brakes
		//---777---	_OwnerAI->FractionQueueTaskDT.RemoveAt(0);
		_OwnerAI->TasksBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;
		GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);
	}

	// ** Brake Other-Task (AIComand, DominantComand, DailyTask)
	else
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>    Break Task"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->TasksBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;

		GetWorld()->GetTimerManager().SetTimer(_OwnerAI->TH_UpdateLogic, _OwnerAI, &AUnitAI::UpdateLogic, GetWorld()->GetDeltaSeconds(), false);
	}
*/
}


