
#pragma once

#include "CoreMinimal.h"

#include "../Item/WorldItem.h"
#include "../Item/Struct/ItemDT.h"
#include "../Inventory/Enum/SlotType.h"

#include "AmunitionItem.generated.h"


UCLASS()
class OOO_API AAmunitionItem : public AWorldItem
{
	GENERATED_BODY()
	


public:

	// ** Equip slot type for Weapon/Armor identity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Amunition")
		ESlotType EquipSlotTypeFix = ESlotType::none;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Weapon")
		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;


public:

/* (-------------------------------)
	virtual bool EquipAmunitionByItemDT(const FItemDT* _ItemDT);

	virtual bool EquipWeaponByItemDT(const FItemDT* _ItemDT) { return false; };
*/

	// ** Attach and SetPosition
	UFUNCTION(BlueprintCallable, Category = "OOO!_Amunition")
		virtual void AttachToUnitOnSocket(class AUnit* _Owner, FName Socket = FName("none"), bool IsArmor = false);// {}; // ** =0


	// ** Assign Mesh to Item 
	virtual void SetMesh(UObject* MeshPrimitive) override;


	virtual void SetVisibility(bool IsVisibility) override;

};
