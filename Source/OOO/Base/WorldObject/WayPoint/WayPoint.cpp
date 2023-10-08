

//#include "../AW_HelperActor/WayPoint.h"
#include "WayPoint.h"

#include "Components/CapsuleComponent.h"


AWayPoint::AWayPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetupAttachment(Root);
}


void AWayPoint::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(WayPointName);
}

