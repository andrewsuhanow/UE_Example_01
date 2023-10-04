
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopSpectator.generated.h"

UCLASS()
class OOO_API ATopSpectator : public APawn
{
	GENERATED_BODY()

public:
	ATopSpectator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
