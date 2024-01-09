
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Item/Struct/ItemDT.h"

#include "ArmorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UArmorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UArmorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

public:

	UPROPERTY(BlueprintReadOnly, Category = "OOO")
		class AUnit* UnitOwner;



public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TArray<TSubclassOf<class AArmorWorldItem>> Armor_class;

public:

	// ** Armor class object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class AArmorWorldItem*> ArmorSlot;

public:

	UFUNCTION(BlueprintCallable)
		void InitArmor(class AUnit* _UnitOwner);

	bool EquipArmorByItemDT(const FItemDT* _ItemDT);

};
