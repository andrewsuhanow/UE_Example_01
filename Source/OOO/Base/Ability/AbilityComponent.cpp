

// #include "Base/Ability/AbilityComponent.h"
#include "AbilityComponent.h"

#include "../Base/BaseGameMode.h"



UAbilityComponent::UAbilityComponent()
{
		PrimaryComponentTick.bCanEverTick = false;
}



void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAbilityComponent::AddAbility(EAbilityType Ability)
{

	ABaseGameMode* GmMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (!GmMode)
		return;


	for (auto It : GmMode->GetGameAbilityArchive()->GetRowMap())
	{
		FAbilityDT* Row = reinterpret_cast<FAbilityDT*>(It.Value);
		if (Row->AbilityType == Ability)
		{
			AbilitySlot.Add(Ability, *Row);
			break;
		}
	}
}




