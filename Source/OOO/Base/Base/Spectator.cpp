

//#include "../Base/Spectator.h"
#include "Spectator.h"

ASpectator::ASpectator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpectator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

