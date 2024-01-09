
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FractionController.generated.h"

UCLASS()
class OOO_API AFractionController : public AActor
{
	GENERATED_BODY()
	
public:	
	AFractionController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_FractionController")
		int32 FractionIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_FractionController")
		TArray<class AUnit*> AllControlledUnits;

public:

	UFUNCTION()
		void RegisterUnit(class AUnit* _Unit);


};
