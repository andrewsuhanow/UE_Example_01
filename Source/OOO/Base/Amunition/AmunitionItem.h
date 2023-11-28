
#pragma once

#include "CoreMinimal.h"

#include "../Item/WorldItem.h"

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

	// ** Attach and SetPosition
	UFUNCTION(BlueprintCallable, Category = "OOO!_Amunition")
		virtual void AttachToUnitOnSocket(class AUnit* _Owner, FName Socket = FName("none")) {}; // ** =0



};
