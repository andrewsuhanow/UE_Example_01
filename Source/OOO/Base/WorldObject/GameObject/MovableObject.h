
#pragma once

#include "CoreMinimal.h"
#include "StaticObject.h"
#include "MovableObject.generated.h"

UCLASS()
class OOO_API AMovableObject : public AStaticObject
{
	GENERATED_BODY()
	
public:	
	AMovableObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
