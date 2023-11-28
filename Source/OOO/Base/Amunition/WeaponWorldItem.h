
#pragma once





#include "CoreMinimal.h"
#include "AmunitionItem.h"

#include "WeaponWorldItem.generated.h"


UCLASS(hidecategories = "OOO")
class OOO_API AWeaponWorldItem : public AAmunitionItem
{
	GENERATED_BODY()


public:

	AWeaponWorldItem();

public:

	// ** Slot-Weapon Parameter 
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!_Weapon")
	//	TSubclassOf<class UWeaponDT> WeaponDT_Class;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Weapon")
		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
public:

	// ** Assign Mesh to Item 
	virtual void SetMesh(UObject* MeshPrimitive) override;

	// ** Attach on Socket
	virtual void AttachToUnitOnSocket(class AUnit* _Owner, FName Socket = FName("none")) override;

	virtual void SetVisibility(bool IsVisibility) override;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool IcCanEquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType = ESlotType::none);
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool EquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType = ESlotType::none);

	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool IcCanEquipItemOnIndex(const FItemDT& _Item, int32 _Index);
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool EquipItemOnIndex(const FItemDT& _Item, int32 _Index);

public:

	
};
