
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticObject.generated.h"

UCLASS()
class OOO_API AStaticObject : public AActor
{
	GENERATED_BODY()
	

public:

	AStaticObject();


public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UStaticMeshComponent*> StaticMashComp;


protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
