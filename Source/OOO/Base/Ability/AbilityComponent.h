
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Struct/AbilityDT.h"

#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UAbilityComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
			TMap<EAbilityType, FAbilityDT> AbilitySlot;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddAbility(EAbilityType Ability);

};
