

//#include "../AW_HelperActor/WayPoint.h"
#include "WayPoint.h"

#include "Components/CapsuleComponent.h"


AWayPoint::AWayPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;
	

	HelperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HelperMesh"));
	HelperMesh->SetCollisionProfileName(TEXT("NoCollision"));
	HelperMesh->SetupAttachment(Root);
}


void AWayPoint::BeginPlay()
{
	Super::BeginPlay();
}

/*
void AWayPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	bool bNonColliding = true;
	bool bIncludeFromChildActors = true;	
	//GetComponentsBoundingCylinder(CollisionWidth, CollisionHeight, bNonColliding, bIncludeFromChildActors);

	Tags.Add(WayPointName);
}
*/




void AWayPoint::AddSpectatorUnit(AActor* _NewSpectatorUnit)
{
	SpectatorUnits.Add(_NewSpectatorUnit);
}

void AWayPoint::RemoveSpectatorUnit(AActor* _SpectatorUnit)
{
	SpectatorUnits.Remove(_SpectatorUnit);
}

void AWayPoint::RecheckSpectatorUnit()
{
	for (int32 i = 0; i < SpectatorUnits.Num(); ++i)
	{
		if (SpectatorUnits[i] == nullptr || SpectatorUnits[i]->IsPendingKill())
		{
			SpectatorUnits.RemoveAt(i);
			--i;
		}
	}
}






/*
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

*/