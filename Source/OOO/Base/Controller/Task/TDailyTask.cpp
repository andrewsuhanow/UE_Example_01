

//#include "Task/TDailyTask.h"
#include "TDailyTask.h"

#include "../UnitAI.h"

#include "Base/Task.h"
#include "TMoveTo.h"

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass


UTDailyTask::UTDailyTask()
{
	TaskType = ETaskType::DailyBehavior;
}



void UTDailyTask::ContinueTask(AUnitAI* _OwnerAI)
{

	bool isCurrTimeCorrect = CheckTaskTimeWithGlobalTime(_OwnerAI);
	if (!isCurrTimeCorrect)
		isCurrTimeCorrect = SetNextTaskData(_OwnerAI);

	if (!isCurrTimeCorrect)
	{
		BreakTask(_OwnerAI);
		return;
	}
	else
	{
		// ** if new TaskTada (new WayPoint), store it
		if (iCurrentDailyBhvrData != iLastCurrentDailyBhvrData)
		{
			InitNewDailyTaskData(_OwnerAI);
		}

		// ** Store first SubTask in AI
		if (_OwnerAI->TasksBuffer.Num() == 0)
		{
			FTaskData newTask;
			newTask.TaskCauser = ETaskCauser::none;							// ** New
			newTask.TaskPriority = ETaskPriority::Normal;
			newTask.TaskRef = _OwnerAI->CurrTaskRef;
			//+++++++++++++++++newTask.TaskDislocation1111 = ETaskDislocation::PointNoRotate;
			// ---77777777777777777--- newTask.Location = CurrTargetLocation;
			_OwnerAI->TasksBuffer.Add(newTask);
			//--777--_OwnerAI->SetTask(false, ETaskType::DailyBehavior, newTask, ETaskInstigator::AI, ETaskPriority::Normal);
		}
		
		// ** Check dist
		float dist = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), CurrTargetLocation);
		if (_OwnerAI->GetUnitStopDistance() < dist)
		{
			FTaskData SubMoveTask;
			float stopDist = 0.f;
			UTMoveTo::SetMoveData_MoveToPoint(SubMoveTask, _OwnerAI->UnitOwner, CurrTargetLocation, stopDist, EUnitPose::RelaxMove);
			UE_LOG(LogTemp, Warning, TEXT("Task::DailyBhvr,    Start-SubTask:  Move "));

			_OwnerAI->SetTask(false, ETaskType::MoveTo, SubMoveTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
			return;
		}
		//else
		{
			// ** Check rotate
		}
		// ** Do action

		//**** Finish Task (Transit move)

		//**** Spend time

		//**** Do Task (Weapon, Ability)
		
		//**** Play anim

		TaskComplit(_OwnerAI);
	}
}



void UTDailyTask::TaskComplit(AUnitAI* _OwnerAI)
{
	SetNextTaskData(_OwnerAI);

	Super::TaskComplit(_OwnerAI);
}


void UTDailyTask::BreakTask(AUnitAI* _OwnerAI)
{

	// ** if(UseGeneralStage)	// ** Animation
	// **	StopAnimation();

	Super::BreakTask(_OwnerAI);
}





bool UTDailyTask::SetNextTaskData(class AUnitAI* _OwnerAI)
{
	int32 dailyTaskNUM = _OwnerAI->DailyBhvrTaskDT.Num();
	for(int32 i = 0; i < dailyTaskNUM; ++i)
	{
		iLastCurrentDailyBhvrData = iCurrentDailyBhvrData;
		++iCurrentDailyBhvrData;

		// ** Start from the begin DeilyTask[X]
		if (iCurrentDailyBhvrData > dailyTaskNUM - 1)
		{
			iCurrentDailyBhvrData = 0;
			iLastCurrentDailyBhvrData = dailyTaskNUM - 1;
		}

		// ** Check correcting with Current-Time
		if (CheckTaskTimeWithGlobalTime(_OwnerAI))
		{
			return true;
		}
	}
	return false;
}

bool UTDailyTask::CheckTaskTimeWithGlobalTime(class AUnitAI* _OwnerAI)
{
	// ** No-One DailyTask
	if (_OwnerAI->DailyBhvrTaskDT.Num() == 0)
	{
		iCurrentDailyBhvrData = -1;
		return false;
	}
	else
	if (iCurrentDailyBhvrData < 0)
	{
		iCurrentDailyBhvrData = 0;
	}
	

	int32 currGameHour	= _OwnerAI->GetGameHour();
	int32 startTaskTime = _OwnerAI->DailyBhvrTaskDT[iCurrentDailyBhvrData].StartTime;
	int32 endTaskTime	= _OwnerAI->DailyBhvrTaskDT[iCurrentDailyBhvrData].EndTime;

	// ** (0....strt......@@......end....24,  0............................24)
	if (startTaskTime < endTaskTime)
	{
		if (startTaskTime <= currGameHour && endTaskTime > currGameHour)
		{
			return true;
		}
	}
	else
//	if (startTaskTime > endTaskTime)
	{
	// ** (0.............strt.............24,  0......@@....end............24)
		if (currGameHour >= 0 && currGameHour < endTaskTime)
		{
			return true;
		}

	// ** (0.............strt.......@@.....24,  0.........end..............24)
		else 
		if (currGameHour >= startTaskTime)
		{
			return true;
		}
	}
	return false;
}

bool UTDailyTask::InitNewDailyTaskData(class AUnitAI* _OwnerAI)
{

	// ** Stored DailyTask data
	TArray<AActor*> foundedActotr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _OwnerAI->DailyBhvrTaskDT[iCurrentDailyBhvrData].WayPointTag, foundedActotr);
	for (int32 i = 0; i < foundedActotr.Num(); i++)
	{
		CurrTargetActor = foundedActotr[i];
		CurrTargetLocation = foundedActotr[i]->GetActorLocation();
		CurrTargetDirectuin = foundedActotr[i]->GetActorRotation();
		//  !!!!!!! float CurrTargetWidth = -1;
		//  !!!!!!! float CurrTargetHeight = -1;

		// ** for dont init next time
		if (iLastCurrentDailyBhvrData == -1)
			iLastCurrentDailyBhvrData = iCurrentDailyBhvrData = 0;
		else
			iLastCurrentDailyBhvrData = iCurrentDailyBhvrData;

		return true;
	}
	return false;
}



void UTDailyTask::TaskResult(class AUnitAI* _OwnerAI)
{

}






