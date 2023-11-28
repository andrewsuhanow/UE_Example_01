
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Enum/TurnBaseGameState.h"

#include "BaseGameState.generated.h"


UCLASS()
class OOO_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseGameMode* BGameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseHUD* HUD;

	UFUNCTION()		
		void SetDefaultGameParam(class ABaseGameMode* _GameMode, class ABaseHUD* _HUD);


public:

	// ****************************    Game Play    ********************************

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_GamePlay")
		TArray<AUnit*> SelectedUnits;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_GamePlay")
		int32 SelectedUnitsNum = 0;

	UFUNCTION(BlueprintCallable, Category = "OOO_GamePlay")
		void SelectOneUnit(AUnit* _NewUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO_GamePlay")
		int32 AddToSelectedUnits(AUnit* _NewUnit);
	UFUNCTION(BlueprintCallable, Category = "OOO_GamePlay")
		int32 DeselectUnit(AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO_GamePlay")
		void DeselectAllUnits();
	UFUNCTION(BlueprintCallable, Category = "OOO_GamePlay")
		int32 GetUnitGroupNum();

public:


	// ****************************    Turn Base Game State    ********************************
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		ETurnBaseGameState TurnBaseGameState = ETurnBaseGameState::RealTime;			// ** RealTime,  Pause,  TurnBase,

	DECLARE_MULTICAST_DELEGATE_OneParam(F_TurnBaseGmStateSender, ETurnBaseGameState);
	F_TurnBaseGmStateSender TurnBaseGmStateSender;

	UFUNCTION(BlueprintCallable)
		void SetNewTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState);

};