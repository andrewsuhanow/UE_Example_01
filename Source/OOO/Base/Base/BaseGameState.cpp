

//#include "../Base/BaseGameState.h"
#include "BaseGameState.h"


#include "BaseGameMode.h"
#include "../HUD/BaseHUD.h"

#include "../Unit/Base/Unit.h"



void ABaseGameState::SetDefaultGameParam(ABaseGameMode* _GameMode, ABaseHUD* _HUD)
{
	BGameMode = _GameMode;
	HUD = _HUD;
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

	return GetUnitGroupNum();
}

int32 ABaseGameState::DeselectUnit(AUnit* _Unit)
{
	if (SelectedUnits.Contains(_Unit))
	{
		SelectedUnits.Remove(_Unit);
		--SelectedUnitsNum;

		_Unit->DeselectUnit();
	}
	return GetUnitGroupNum();
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

int32 ABaseGameState::GetUnitGroupNum()
{
	return SelectedUnitsNum;
}



// ****************************    Turn_Base_Game_State    ********************************

void ABaseGameState::SetNewTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState)
{
	TurnBaseGmStateSender.Broadcast( TurnBaseGameState = _TurnBaseGameState );		//  RealTime,  Pause,  TurnBase
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