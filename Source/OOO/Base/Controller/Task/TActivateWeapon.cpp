

//#include "Task/TActivateWeapon.h"
#include "TActivateWeapon.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"


UTActivateWeapon::UTActivateWeapon()
{
	TaskType = ETaskType::ActivateWeapon;
}


void UTActivateWeapon::StartTask(AUnitAI* _OwnerAI)
{
	OwnerAI = _OwnerAI;

	IdentifyTask(_OwnerAI);

	UAnimMontage* animate = nullptr;

	if (!_OwnerAI->IsWeaponActive())
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
	else
		ContinueTask(_OwnerAI);
}


void UTActivateWeapon::ContinueTask(AUnitAI* _OwnerAI)
{
	TaskComplit(_OwnerAI);

	// ** Continue animate but task has Finish
}


void UTActivateWeapon::OnAnimationNotify(class AUnitAI* _OwnerAI, FString _NotifyName)
{

	// ** first-half equip animation finish (Take or Push weapon)
	if (!_OwnerAI->IsWeaponActive())
	{
		_OwnerAI->ActivateWeapon();
	}
	else
	{
		_OwnerAI->UnactivateWeapon();

		// ** if "Change weapon" when it activated
		if(NewWpnIndexForChange != -1)
		{
			if (_OwnerAI->UnitOwner->SetWeaponSlotSelected(NewWpnIndexForChange))
			{
				_OwnerAI->ActivateWeapon();

				UAnimMontage* animate = _OwnerAI->GetGameAnimation(EAnimationKey::equip);
				if (animate)
				{
					float fromTime = 0.f;

					for (int32 i = 0; i < animate->Notifies.Num(); i++)
					{
						if (animate->Notifies[i].NotifyName == FName("CanBeFinish"))
						{
							fromTime = animate->Notifies[i].GetTime();
							fromTime += 0.01f;
							break;
						}
					}
					bool isPlayTOP = true;
					_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);
				}
			}
		}
	}
	ContinueTask(_OwnerAI);
}


void UTActivateWeapon::TaskComplit(AUnitAI* _OwnerAI)
{

	NewWpnIndexForChange = -1;

	Super::TaskComplit(_OwnerAI);
}


void UTActivateWeapon::BreakTask(AUnitAI* _OwnerAI)
{

	NewWpnIndexForChange = -1;

	Super::BreakTask(_OwnerAI);
}


bool UTActivateWeapon::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Int32Param.Num() < 1)
		return false;

	// ** if not -1  =>  Equip new weapon after unequip last
	NewWpnIndexForChange = task.Int32Param[0];

	return  true;
}



// -----------------------------   Static   -----------------------------



void UTActivateWeapon::SetActivateWeaponTaskData_ChangeWpn(FTaskData& _TaskData, 
	AUnit* _SelfUnit, int32 _NewWeaponIndex)
{
	// ** Change weapon on New-Weapon-Slot-Index
	_TaskData.Int32Param.Add(_NewWeaponIndex);
}