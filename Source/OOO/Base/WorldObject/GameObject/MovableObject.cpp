

// #include "Base/WorldObject/GameObject/MovableObject.h"
#include "MovableObject.h"

AMovableObject::AMovableObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMovableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

