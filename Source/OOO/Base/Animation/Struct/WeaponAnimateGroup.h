

// #include "Base/Animation/Struct/FAnimationsGroup.h"

#pragma once

#include "../Enum/AnimationKey.h"
#include "../../Amunition/Enum/WeaponType.h"

#include "WeaponAnimateGroup.generated.h"






// ** GameMod -> TMap< UnitType, 
// **							TMap< WeaponType, 
// **											TMap< AnimationKey, 
// **															  Animations>>>






USTRUCT(Blueprintable, BlueprintType)
struct FAnimateGroup
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

public:

	// ** EquipAnim, UnequipAnim, Attack1, Attack2, LocomotionUse, ...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TMap<EAnimationKey, UAnimMontage*> Animation;
};



USTRUCT(Blueprintable, BlueprintType)
struct FWeaponAnimateGroup
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

public:

	// ** Sword, LongSword, Pike, Bow, Rifle, ...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TMap<EWeaponType, FAnimateGroup> WeaponGroupAnimation;
};