// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameStateDEBUG.generated.h"

UCLASS()
class OOO_API AMyGameStateDEBUG : public AActor
{
	GENERATED_BODY()
	
public:	



	class ABaseGameState* GameState;



	UPROPERTY()
		bool DrawSelectUnit = true;







public:	
	AMyGameStateDEBUG();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
