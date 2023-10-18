
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "../Controller/Task/Struct/TaskData.h"		// ** Unit->SetUnitTask()

#include "Spectator.generated.h"

UCLASS()
class OOO_API ASpectator : public APawn
{
	GENERATED_BODY()

public:
	ASpectator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
