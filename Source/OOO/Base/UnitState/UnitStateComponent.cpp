


// #include "Base/UnitState/UnitStateComponent.h"

#include "UnitStateComponent.h"

#include "../Unit/Base/Unit.h"

#include "../Base/BaseGameMode.h"



UUnitStateComponent::UUnitStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UUnitStateComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UUnitStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UUnitStateComponent::Init()
{
	AUnit* UnitOwner = Cast<AUnit>(GetOwner());

}




