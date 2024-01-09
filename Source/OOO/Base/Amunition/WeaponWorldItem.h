
#pragma once





#include "CoreMinimal.h"
#include "AmunitionItem.h"

#include "../Controller/Task/Enum/TacticalMoveStepLogic.h"

#include "WeaponWorldItem.generated.h"


UCLASS(hidecategories = "OOO")
class OOO_API AWeaponWorldItem : public AAmunitionItem
{
	GENERATED_BODY()


public:

	AWeaponWorldItem();

public:

	// **  Weapon attack index 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 PermanentAttacIndex = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 SelectedAttacIndex = -1;
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		int32 GetSelectedAttackIndex();
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool IsAttackIndexCorrect(int32 Index);
	TArray<ETacticalMoveStepLogic>* GetCurrTacticalMoveSteps();
/*
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Weapon")
		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

public:

	// ** Assign Mesh to Item 
	virtual void SetMesh(UObject* MeshPrimitive) override;

	// ** Attach on Socket
	virtual void AttachToUnitOnSocket(class AUnit* _Owner, FName Socket = FName("none")) override;

	virtual void SetVisibility(bool IsVisibility) override;
*/
public:

	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool IcCanEquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType = ESlotType::none);
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool EquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType = ESlotType::none);

	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool IsCanEquipItemOnIndex(const FItemDT& _Item, int32 _Index);
	UFUNCTION(BlueprintCallable, Category = "OOO_Weapon")
		bool EquipItemOnIndex(const FItemDT& _Item, int32 _Index);

public:

	
};
