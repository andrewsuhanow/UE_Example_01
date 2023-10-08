// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAI.generated.h"


UCLASS()
class OOO_API AUnitAI : public AAIController
{
	GENERATED_BODY()

public:

	AUnitAI();

	
	UFUNCTION()		void Init();	// ** Start from "UnitOwner"


protected:

	class AUnit* UnitOwner;
};
