
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"





UCLASS()
class OOO_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:

	AUnit();

protected:

	virtual void BeginPlay() override;

public:

	// ** "Game-Delay" at the BeginPlay() 
	UFUNCTION()		void Start();
	UPROPERTY()		FTimerHandle TH_Start;

	// **  AI Controller 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Set_Default_Controller")
		TSubclassOf<class AUnitAI> AIController_Class;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class AUnitAI* AI;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
