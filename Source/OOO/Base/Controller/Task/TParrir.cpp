

//#include "Task/TParrir.h"
#include "TParrir.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"

#include "Kismet/KismetMathLibrary.h"


UTParrir::UTParrir()
{
	TaskType = ETaskType::Parrir;
}


void UTParrir::StartTask(AUnitAI* _OwnerAI)
{
	OwnerAI = _OwnerAI;

// (+++++++++++++++++++++++++)
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

	// ** Start Animate
	UAnimMontage* animate = _OwnerAI->GetGameAnimation(EAnimationKey::parrir);
	if (animate)
	{
		bool isPlayTOP = false;
		float fromTime = 0.f;

		_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);

		IsUsingAnimate = true;
		return;
	}

	/*
	dodge_lft,
	dodge_rt,
	dodge_fwd,
	dodge_bwd,
	*/

	// ** Task finish
	IsUsingAnimate = false;
	TaskComplit(_OwnerAI);
}



void UTParrir::OnAnimationNotify(AUnitAI* _OwnerAI, FString _NotifyName)
{
	if (_NotifyName == FString("CanBeFinish"))
	{
		// ** @@@@@@@
		// ** @@@@@@@
		// **				Calculate Freze controll after animation
		// **				
		fTimeLostControll = 0.4f; // **  (Power + Agil) / 100;
		// ** @@@@@@@
		// ** @@@@@@@

		GetWorld()->GetTimerManager().SetTimer(TH_Parrir, this, &ThisClass::ParrirTick, fTimeLostControll, false);
	}
}


void UTParrir::ParrirTick()
{
	GetWorld()->GetTimerManager().ClearTimer(TH_Parrir);

	TaskComplit(OwnerAI);
}





void UTParrir::ContinueTask(AUnitAI* _OwnerAI)
{

}



void UTParrir::TaskComplit(AUnitAI* _OwnerAI)
{
	Super::TaskComplit(_OwnerAI);
}


void UTParrir::BreakTask(AUnitAI* _OwnerAI)
{
	Super::BreakTask(_OwnerAI);
}


