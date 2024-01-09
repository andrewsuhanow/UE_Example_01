

//#include "Task/TBlock.h"
#include "TBlock.h"

#include "../../Unit/Base/Unit.h"
#include "../UnitAI.h"

#include "Kismet/KismetMathLibrary.h"

UTBlock::UTBlock()
{
	TaskType = ETaskType::Block;
}


void UTBlock::StartTask(AUnitAI* _OwnerAI)
{

	OwnerAI = _OwnerAI;

// (++++++++++++++++++++++++++++++)
/*
	// ** rotate to agressor
	if (_OwnerAI->CurrTaskDTBuffer.Last().TargetUnit)
	{
		FRotator rotatorToTarget = UKismetMathLibrary::FindLookAtRotation(
			_OwnerAI->UnitOwner->GetActorLocation(),							// ** Self
			_OwnerAI->CurrTaskDTBuffer.Last().TargetUnit->GetActorLocation());	// ** Target
		rotatorToTarget.Pitch = 0.f;
		rotatorToTarget.Roll = 0.f;
		_OwnerAI->UnitOwner->SetActorRotation(rotatorToTarget, ETeleportType::TeleportPhysics);
	}
*/

	// ** @@@@@@@@@@@@@@@@@@@@@@@@@ Blok--Parameter
	TimeLength = 8.f;  // ** @@@@@@@@@@@@@@@@@@@@@@@@@ Blok--Parameter
	// ** @@@@@@@@@@@@@@@@@@@@@@@@@ Blok--Parameter

	TaskPerformance(_OwnerAI);

	TaskComplit(_OwnerAI);
}





void UTBlock::TaskPerformance(AUnitAI* _OwnerAI)
{
	if (!Animate)
		Animate = _OwnerAI->GetGameAnimation(EAnimationKey::block);

	// ** Start Animate
	if (Animate)
	{
		bool isPlayTOP = true;
		float fromTime = 0.f;
		_OwnerAI->PlayAnimate(Animate, isPlayTOP, fromTime);

		IsUsingAnimate = true;

		GetWorld()->GetTimerManager().SetTimer(TH_Block, this, &ThisClass::BlockHolding, GetWorld()->GetDeltaSeconds(), false);
		return;
	}


	// ** Task finish
	IsUsingAnimate = false;
	GetWorld()->GetTimerManager().ClearTimer(TH_Block);

}




void UTBlock::BlockHolding()
{

	// ** if finish task-Time => STOP
	if (TimeLength < 0.f)
	{
		OwnerAI->StopAnimate();
		IsUsingAnimate = false;
		GetWorld()->GetTimerManager().ClearTimer(TH_Block);
		return;
	}


	UAnimMontage* CurrMontage = OwnerAI->UnitOwner->GetCurrentMontage();

	// ** use Animate again
	if (CurrMontage == nullptr)
	{
		TaskPerformance(OwnerAI);
		return;
	}

	// ** if use other Task(vs animate) => STOP
	else if (CurrMontage != Animate)
	{
		IsUsingAnimate = false;
		GetWorld()->GetTimerManager().ClearTimer(TH_Block);
		return;
	}

	// ** Task continue
	TimeLength -= GetWorld()->GetDeltaSeconds();

	GetWorld()->GetTimerManager().SetTimer(TH_Block, this, &ThisClass::BlockHolding, GetWorld()->GetDeltaSeconds(), false);
}

/*
void UTBlock::TaskComplit(AUnitAI* _OwnerAI)
{
	Super::TaskComplit(_OwnerAI);
}


void UTBlock::BreakTask(AUnitAI* _OwnerAI)
{
	Super::BreakTask(_OwnerAI);
}
*/

