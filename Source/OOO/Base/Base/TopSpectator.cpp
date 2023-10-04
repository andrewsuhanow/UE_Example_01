

//#include "Base/Base/TopSpectator.h"
#include "TopSpectator.h"

ATopSpectator::ATopSpectator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATopSpectator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATopSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATopSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

