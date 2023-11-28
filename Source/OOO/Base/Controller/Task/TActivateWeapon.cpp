

//#include "Task/TActivateWeapon.h"
#include "TActivateWeapon.h"

#include "../UnitAI.h"


UTActivateWeapon::UTActivateWeapon()
{
	TaskType = ETaskType::ActivateWeapon;
}


void UTActivateWeapon::StartTask(AUnitAI* _OwnerAI)
{
	OwnerAI = _OwnerAI;

	UAnimMontage* animate = nullptr;

	if (_OwnerAI->IsWeaponActive())
	{
		animate = _OwnerAI->GetGameAnimation(EAnimationKey::equip);
	}
	else
	{
		animate = _OwnerAI->GetGameAnimation(EAnimationKey::unequip);
	}

	if (animate)
	{
		bool isPlayTOP = true;
		float fromTime = 0.f;
		_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);
	}

	//TaskComplit(_OwnerAI);
}


void UTActivateWeapon::ContinueTask(AUnitAI* _OwnerAI)
{
	// ** first-half equip animation finish (Take or Push weapon)

	bool isOk = false;

	if (_OwnerAI->IsWeaponActive() == -1)
	{
		isOk = _OwnerAI->ActivateWeapon();
	}
	else
	{
		isOk = _OwnerAI->UnactivateWeapon();
	}

	if(isOk)
	{
		TaskComplit(_OwnerAI);

		// ** Continue animate
	}
}



void UTActivateWeapon::TaskComplit(AUnitAI* _OwnerAI)
{
	Super::TaskComplit(_OwnerAI);
}


void UTActivateWeapon::BreakTask(AUnitAI* _OwnerAI)
{
	Super::BreakTask(_OwnerAI);
}


