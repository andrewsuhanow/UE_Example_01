
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Struct/ItemDT.h"

#include "WorldItem.generated.h"

UCLASS()
class OOO_API AWorldItem : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		FItemDT ItemDT;

public:	

	AWorldItem();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
