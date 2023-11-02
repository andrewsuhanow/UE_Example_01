

//#include "../Base/BaseGameState.h"
#include "BaseGameState.h"


#include "../Base/BaseGameMode.h"
#include "../HUD/BaseHUD.h"



void ABaseGameState::SetDefaultGameParam(ABaseGameMode* _GameMode, ABaseHUD* _HUD)
{
	BGameMode = _GameMode;
	HUD = _HUD;
}





void ABaseGameState::SetNewTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState)
{
	TurnBaseGmStateSender.Broadcast( TurnBaseGameState = _TurnBaseGameState );		//  RealTime,  Pause,  TurnBase
}