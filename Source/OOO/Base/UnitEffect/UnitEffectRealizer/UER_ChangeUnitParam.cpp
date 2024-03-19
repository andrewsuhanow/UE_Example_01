

// #include "Base/UnitEffect/UnitEffectRealizer/UER_ChangeUnitParam.h"

#include "UER_ChangeUnitParam.h"

#include "../../UnitState/Enum/UnitParam.h"

#include "../../Unit/Base/Unit.h"




UUER_ChangeUnitParam::UUER_ChangeUnitParam()
{
	HELPER__UnitEffectParamDescription.Add(FString("Requitr: UnitParamModifier[0]"));
	HELPER__UnitEffectParamDescription.Add(FString("Requitr: Effect Image"));
}



bool UUER_ChangeUnitParam::InitEffect(FUnitEffectSlotDT& _UnitEffectSlotDT, AUnit* _UnitOwner)
{

	if (_UnitEffectSlotDT.UnitParamModifier.Num() > 0)
	{
		_UnitEffectSlotDT.FullRoundDuration = _UnitEffectSlotDT.UnitParamModifier[0].ModifierType;
		_UnitEffectSlotDT.IsFirstTime = true;
		return ContinueEffect(_UnitEffectSlotDT, _UnitOwner);;
	}

	return false; 
}


bool UUER_ChangeUnitParam::ContinueEffect(FUnitEffectSlotDT& _UnitEffectSlotDT, AUnit* _UnitOwner)
{


	if (_UnitEffectSlotDT.UnitParamModifier.Num() > 0)
	{
		int32 durationTime = _UnitEffectSlotDT.UnitParamModifier[0].ModifierType;

		// ** Performance
		{
			EUnitParam paramType = _UnitEffectSlotDT.UnitParamModifier[0].UnitParam;

			// ** Set param value
			if (_UnitEffectSlotDT.UnitParamModifier[0].IsParamSet)
				_UnitOwner->SetParam(paramType, _UnitEffectSlotDT.UnitParamModifier[0].Value);
			// ** Mod param value
			else
				_UnitOwner->ModParam(paramType, _UnitEffectSlotDT.UnitParamModifier[0].Value);

			_UnitOwner->UpdateParameterPanel_HUD();
		}


		// ** if Duration effect (checking Round-time)
		if (durationTime >= 0 && !_UnitEffectSlotDT.IsFirstTime)
		{
			--(_UnitEffectSlotDT.UnitParamModifier[0].ModifierType);
			--durationTime;
		}
		else if(durationTime == ONCE)
		{
			return false;
		}
		else if (_UnitEffectSlotDT.IsFirstTime)
		{
			if (_UnitEffectSlotDT.UnitParamModifier[0].UnitParam == EUnitParam::HP)
			{
				float potentialChangHP = 
					_UnitOwner->GetParam(EUnitParam::HP) + 
					_UnitEffectSlotDT.UnitParamModifier[0].Value * durationTime;
				_UnitOwner->SetParam(EUnitParam::PotentialHP, potentialChangHP);
			}
		}

		_UnitEffectSlotDT.IsFirstTime = false;

		// ** Finish
		{
			if (durationTime == 0 && _UnitEffectSlotDT.FullRoundDuration > 0)
				FinishEffect(_UnitEffectSlotDT, _UnitOwner);
		}
		return true;
	}

	return false;
}
//SetUnitParamByType(EUnitParam _Param, float _Val);


void UUER_ChangeUnitParam::FinishEffect(FUnitEffectSlotDT& _UnitEffectSlotDT, AUnit* _UnitOwner)
{
	_UnitOwner->RermoveUnitEffect(_UnitEffectSlotDT);
}



void UUER_ChangeUnitParam::CancelEffect(FUnitEffectSlotDT& _UnitEffectSlotDT, AUnit* _UnitOwner)
{
	_UnitOwner->RermoveUnitEffect(_UnitEffectSlotDT);
}




