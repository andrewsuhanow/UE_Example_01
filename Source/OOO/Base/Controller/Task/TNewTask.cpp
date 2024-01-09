

//#include "Task/TNewTask.h"
#include "TNewTask.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"


UTNewTask::UTNewTask()
{
	TaskType = ETaskType::CheckPoint;

	// ** FTaskData::Param1[0]  -  Waiting time
}


void UTNewTask::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;


}


void UTNewTask::ContinueTask(AUnitAI* _OwnerAI)
{

}




void UTNewTask::TaskComplit(AUnitAI* _OwnerAI)
{


	Super::TaskComplit(_OwnerAI);
}


void UTNewTask::BreakTask(AUnitAI* _OwnerAI)
{


	Super::BreakTask(_OwnerAI);
}




bool UTNewTask::IdentifyTask(AUnitAI* _OwnerAI)
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
void UTNewTask::SetTaskData_WaitParam(FTaskData& _TaskData, AUnit* _SelfUnit, float _Time)
{
	_TaskData.FloatParam.Add(_Time);
}
*/