
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class OOO_API AWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWayPoint();

protected:

	virtual void BeginPlay() override;


public:

	UPROPERTY()
		USceneComponent* Root;

	// ** Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		UStaticMeshComponent* Mesh = nullptr;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		FName WayPointName = FName("none");									// ** TAG

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float CollisionWidth = 150.f;

};
