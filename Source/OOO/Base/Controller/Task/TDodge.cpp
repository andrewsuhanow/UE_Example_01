

//#include "Task/TDodge.h"
#include "TDodge.h"

#include "../UnitAI.h"


UTDodge::UTDodge()
{
	TaskType = ETaskType::Dodge;
}


void UTDodge::StartTask(AUnitAI* _OwnerAI)
{
	OwnerAI = _OwnerAI;

	UAnimMontage* animate = _OwnerAI->GetGameAnimation(EAnimationKey::dodge_bwd);
	if (animate)
	{
		bool isPlayTOP = false;
		float fromTime = 0.f;

		_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);

		IsUsingAnimate = true;
		return;
	}

	IsUsingAnimate = false;
	TaskComplit(_OwnerAI);
}



void UTDodge::ContinueTask(AUnitAI* _OwnerAI)
{
	TaskComplit(_OwnerAI);
}




void UTDodge::TaskComplit(AUnitAI* _OwnerAI)
{
	IsUsingAnimate = false;
	_OwnerAI->StopAnimate();

	Super::TaskComplit(_OwnerAI);
}


void UTDodge::BreakTask(AUnitAI* _OwnerAI)
{
	IsUsingAnimate = false;
	_OwnerAI->StopAnimate();
	
	Super::BreakTask(_OwnerAI);
}


