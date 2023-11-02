

// #include "Base/Item/WorldItem.h"
#include "WorldItem.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

