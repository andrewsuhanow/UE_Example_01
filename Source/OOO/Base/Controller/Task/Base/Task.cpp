

//#include "Base/Controller/Task/Base/Task.h"
#include "Task.h"

#include "../../UnitAI.h"


void UTask::TaskComplit(class AUnitAI* _OwnerAI)
{
	int32 buferTaskNum = _OwnerAI->CurrTaskDTBuffer.Num();

	if (buferTaskNum >= 1)
	{

		// ** finish child-Task (if has) 
		if (buferTaskNum >= 2)
		{
			/// ** DEBUG for Select Unit
			if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
				UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     SubTask complit"), *_OwnerAI->GetUnitGameName().ToString());
			/// ** ---------------------

			_OwnerAI->CurrTaskDTBuffer.RemoveAt(buferTaskNum - 1);
			_OwnerAI->CurrTaskRef = _OwnerAI->CurrTaskDTBuffer.Last().TaskRef;
			_OwnerAI->CurrTaskRef->TaskComplit(_OwnerAI);
		}

		// ** finish General-Task (if its)
		else
		if (_OwnerAI->CurrTaskDTBuffer.Last().TaskStatus == ETaskStatus::GeneralComand)
		{
			/// ** DEBUG for Select Unit
			if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
				UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     Task complit"), *_OwnerAI->GetUnitGameName().ToString());
			/// ** ---------------------
			
			if (_OwnerAI->StoreQueueTaskDT.Num() > 0)
				_OwnerAI->StoreQueueTaskDT.RemoveAt(0);	
			_OwnerAI->CurrTaskDTBuffer.Reset();
			_OwnerAI->CurrTaskRef = nullptr;
			_OwnerAI->UpdateLogic();

			/// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
			/// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
			/// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
			/// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
			/// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Hide HUD icon
		}

		// ** finish Other-Task (AIComand, DominantComand, DailyTask)
		else
		{
			/// ** DEBUG for Select Unit
			if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
				UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>     Task complit"), *_OwnerAI->GetUnitGameName().ToString());
			/// ** ---------------------

			_OwnerAI->CurrTaskDTBuffer.Reset();
			_OwnerAI->CurrTaskRef = nullptr;
			_OwnerAI->UpdateLogic();		
		}

		return;
	}
}



void UTask::BreakTask(class AUnitAI* _OwnerAI)
{
	int32 buferTaskNum = _OwnerAI->CurrTaskDTBuffer.Num();
	if (buferTaskNum >= 2)
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>    Break Sub-Task"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->CurrTaskDTBuffer.RemoveAt(buferTaskNum - 1);
		_OwnerAI->CurrTaskRef = _OwnerAI->CurrTaskDTBuffer.Last().TaskRef;
		_OwnerAI->CurrTaskRef->BreakTask(_OwnerAI);
		return;
	}
	else
	{
		/// ** DEBUG for Select Unit
		if (_OwnerAI->IsUnitSelected() && !_OwnerAI->IsUnitInGroup())
			UE_LOG(LogTemp, Warning, TEXT(">>>>>>> Unit: %s >>>>>>>    Break Task"), *_OwnerAI->GetUnitGameName().ToString());
		/// ** ---------------------

		_OwnerAI->CurrTaskDTBuffer.Reset();
		_OwnerAI->CurrTaskRef = nullptr;

		_OwnerAI->UpdateLogic();
	}
}


