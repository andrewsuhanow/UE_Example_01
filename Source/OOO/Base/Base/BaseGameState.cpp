

//#include "Base/Base/BaseGameState.h"
#include "BaseGameState.h"


#include "BaseGameMode.h"
#include "Spectator.h"
#include "../HUD/BaseHUD.h"

#include "../Unit/Base/Unit.h"



void ABaseGameState::SetDefaultGameParam(ABaseGameMode* _GameMode, 
	ABaseHUD* _HUD, ASpectator* _Spectator)
{
	BGameMode = _GameMode;
	HUD = _HUD;
	Spectator = _Spectator;
}




// ****************************    Game Play    ********************************


void ABaseGameState::SelectOneUnit(AUnit* _NewUnit) 
{
	DeselectAllUnits();
	AddToSelectedUnits(_NewUnit);
}

int32 ABaseGameState::AddToSelectedUnits(AUnit* _NewUnit)
{
	SelectedUnits.Add(_NewUnit);
	++SelectedUnitsNum;

	_NewUnit->SelectUnit();

	return GetCountOfSelectUnits();
}

int32 ABaseGameState::DeselectUnit(AUnit* _Unit)
{
	if (SelectedUnits.Contains(_Unit))
	{
		SelectedUnits.Remove(_Unit);
		--SelectedUnitsNum;

		_Unit->DeselectUnit();
	}
	return GetCountOfSelectUnits();
}

void ABaseGameState::DeselectAllUnits()
{
	for (int32 i = 0; i < SelectedUnits.Num(); ++i)
	{
		SelectedUnits[i]->DeselectUnit();
	}
	SelectedUnits.Reset();
	SelectedUnitsNum = 0;
}

int32 ABaseGameState::GetCountOfSelectUnits()
{
	return SelectedUnitsNum;
}

AUnit* ABaseGameState::GetSelectedUnit(int32 _Num)
{
	if (_Num < 0)
		return nullptr;
	if (_Num  >= GetCountOfSelectUnits())
		return nullptr;

	return SelectedUnits[_Num];
}


void ABaseGameState::SelectUnitMouseFocused(AUnit* _Unit)
{
	if (MouseFocusedUnit)
	{
		MouseFocusedUnit->SetUnitMouseFocused(false);
		MouseFocusedUnit = nullptr;
	}

	if (_Unit)
	{
		_Unit->SetUnitMouseFocused(true);
		MouseFocusedUnit = _Unit;
	}
}

// ****************************    Turn_Base_Game_State    ********************************

void ABaseGameState::SetNewTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState)
{
	TurnBaseGmStateSender.Broadcast( TurnBaseGameState = _TurnBaseGameState );		//  RealTime,  Pause,  TurnBase
}

bool ABaseGameState::IsRealTimeMode() const
{
	return (TurnBaseGameState == ETurnBaseGameState::RealTime) ? true : false;
}
bool ABaseGameState::IsTurnBaseMode() const
{
	return (TurnBaseGameState == ETurnBaseGameState::TurnBase) ? true : false;
}
bool ABaseGameState::IsPauseMode() const
{
	return (TurnBaseGameState == ETurnBaseGameState::Pause) ? true : false;
}

// ****************************    Possesing_Game_State    ********************************

void ABaseGameState::SetPossesingGameState(EPossesingGameState _PossesingGameState)
{
	PossesingGameState = _PossesingGameState;
}

EPossesingGameState ABaseGameState::GetPossesingGameState() const
{
	return PossesingGameState;
}