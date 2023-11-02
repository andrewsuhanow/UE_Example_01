

//#include "Base/Amunition/WeaponComponent.h"
#include "WeaponComponent.h"

#include "WeaponWorldItem.h"

#include "../Unit/Base/Unit.h"

UWeaponComponent::UWeaponComponent()
{
		PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}







