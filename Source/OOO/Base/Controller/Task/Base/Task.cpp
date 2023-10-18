

//#include "Base/Controller/Task/Base/Task.h"
#include "Task.h"

#include "../../UnitAI.h"


bool UTask::FinishChildTask(class AUnitAI* _OwnerAI)
{
	if (_OwnerAI->CurrTaskDTBuffer.Last().TaskStatus == ETaskStatus::ChildTask)
	{
		// ** Continue ParentTask if it exist
		int32 PerformanceTaskNum = _OwnerAI->CurrTaskDTBuffer.Num();
		if (PerformanceTaskNum > 1)
		{
			_OwnerAI->CurrTaskDTBuffer.RemoveAt(PerformanceTaskNum - 1);
			_OwnerAI->CurrTaskRef = _OwnerAI->CurrTaskDTBuffer[PerformanceTaskNum - 2].TaskRef;
			_OwnerAI->CurrTaskRef->ContinueTask(_OwnerAI);
		}
		else
		{
			// @@@@@@@@@@@@@@@@@@@@@@  ERROR   Stop All Unit TASKs
		}
		return true;
	}
	else
		return false;
}

bool UTask::FinishGeneralTask(class AUnitAI* _OwnerAI)
{
	if (_OwnerAI->CurrTaskDTBuffer.Last().TaskStatus == ETaskStatus::GeneralComand)
	{
		// ** Delete stored TaskElement from Queue
		if (_OwnerAI->StoreQueueTaskDT.Num() > 0)
			_OwnerAI->StoreQueueTaskDT.RemoveAt(0);
		_OwnerAI->CurrTaskDTBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;

		return true;

		// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
	}
	else
		return false;
}

bool UTask::FinishDominantAITask(class AUnitAI* _OwnerAI)
{
	if (_OwnerAI->CurrTaskDTBuffer.Last().TaskStatus == ETaskStatus::AIComand ||
		_OwnerAI->CurrTaskDTBuffer.Last().TaskStatus == ETaskStatus::DominantComand)
	{
		_OwnerAI->CurrTaskDTBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;

		return true;
	}
	return false;
}
