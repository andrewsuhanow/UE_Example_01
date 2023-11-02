
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	

	UPROPERTY(BlueprintReadOnly, Category = "OOO")
		class AUnit* UnitOwner;

public:	


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")		
		TArray<class AWeaponWorldItem*> EquipSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 SelectedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsWeaponActive = false;


	//UFUNCTION(BlueprintCallable)
	//	void InitWeapons(AUnit* _Owner);


		
};
