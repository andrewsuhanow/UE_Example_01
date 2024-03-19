


// #include "Base/WorldObject/GameObject/StaticObject.h"
#include "StaticObject.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AStaticObject::AStaticObject()
{
	PrimaryActorTick.bCanEverTick = true;


	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockAll"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // QueryAndPhysics  // QueryOnly  // PhysicsOnly // NoCollision
	Collision->SetCollisionProfileName(TEXT("BlockAll"));  // "Pawn" // OverlapAll  // NoCollision
	Collision->SetBoxExtent(FVector(100.0f, 100.f, 100.f));
	Collision->SetEnableGravity(false);
	Collision->SetupAttachment(RootComponent);



}

void AStaticObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaticObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

