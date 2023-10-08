// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// ** ----------------------

#include "../Fraction/FractionSystem.h"

// ** ----------------------

#include "BaseGameMode.generated.h"


UCLASS()
class OOO_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:

	ABaseGameMode();

protected:

	virtual void BeginPlay() override;

public:

	// ** "Game-Delay" at the BeginPlay() 
	UFUNCTION()		void Start();
	UPROPERTY()		FTimerHandle TH_Start;


// ****************************************************************************************************	
// *******************************************    Fraction    *****************************************

public:

	// ** (Set in Editor)  FFractionUnit(Unit_A, Unit_B, AttitudeStatus)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Set_Fraction")
		TArray<FFractionUnit> FractionsAttitude;

	// ** Fraction component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Fraction")
		UFractionSystem* Fraction;

	UFUNCTION(Blueprintcallable, Category = "OOO_Fraction")
		EUnitAttitudeStatus GetFractionAttitude(uint8 A, uint8 B);
	
};
