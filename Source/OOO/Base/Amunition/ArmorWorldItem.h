
#pragma once

#include "CoreMinimal.h"
#include "AmunitionItem.h"
#include "ArmorWorldItem.generated.h"


UCLASS(hidecategories = "OOO")
class OOO_API AArmorWorldItem : public AAmunitionItem
{
	GENERATED_BODY()

public:

		AArmorWorldItem();

/* (-------------------------------)
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Armor")
		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

public:

	// ** Assign Mesh to Item 
	virtual void SetMesh(UObject* MeshPrimitive) override;

	// ** Attach on Socket
	virtual void AttachToUnitOnSocket(class AUnit* _Owner, FName Socket = FName("none")) override;

	virtual void SetVisibility(bool IsVisibility) override;
	*/
};
