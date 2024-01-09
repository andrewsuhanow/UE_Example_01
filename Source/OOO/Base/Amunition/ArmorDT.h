
#pragma once

// ** #include "Base/Amunition/ArmorDT.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

//-----------#include "Enum/WeaponType.h"
#include "../Inventory/Enum/SlotType.h"

#include "../Unit/Struct/PoseLocomotion.h"
//-------------#include "Enum/AttackHitCollisionType.h"
//--------------#include "Enum/UseDistanceType.h"

//--------------#include "../Controller/Task/Enum/TacticalMoveStepLogic.h"

//-------------#include "../Animation/Enum/AnimationKey.h"

#include "ArmorDT.generated.h"



/*
USTRUCT(BlueprintType, Blueprintable)
struct FAttakParam
{

	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()
		

public:


	//FAttakParam();


	// ** Button using Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		UTexture2D* ButtonImage;

	// ** if can Aiming  (it's "Field Od View" parameter)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float SnipeZoomFOV = -1.f;

	// ** if can Aiming  (it's "Field Od View" parameter)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float RollBackTime = -1.f;
	// ** Hit probability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float Accuracy = 0.f;



//	// ** AnimBlueprint for Character while this Weapon Using
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Param")
//		EWeaponType WeaponTypeAnimSet = EWeaponType::HandFight;


	// ** Speeds and pictures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		EAttackHitCollisionType AttackCollisionType = EAttackHitCollisionType::Simple;

	// ** RULE:   
	// ** [0] = MainAttack
	// ** [1] = AlternateAttack (Short version, if anim use in Attack-Series or after other anim)
	// ** [2] = MainAttack in place			//PrepateAttack	(Anim before "MainAttack" or before "AttackHolding")
	// ** [3] = AlternateAttack  in place   //AttackHolding	(Bow or magik aiming/focusing)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<EAnimationKey> AnimationKEY; // = EAnimationKey::none;

	EAnimationKey GetAnimKey_Attack();
	EAnimationKey GetAnimKey_AlternateAttack();

	EAnimationKey GetAnimKey_AttackInPlace();
	EAnimationKey GetAnimKey_AlternateAttackInPlace();
	//	EAnimationKey GetAnimKey_PrepateAttack();
	//	EAnimationKey GetAnimKey_AttackHolding();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		//	bool IsNeedClearVisible = true;
		EUseDistanceType UseDistanceType = EUseDistanceType::optimal_dist;

			// ** Actor stored all Effect-Parameter   (spawning when AnimNotify-trigger or Collision-Hit)
//++++			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
//++++				TSubclassOf<class ACastAndImpactEffect> Agent;

};

*/

// ** -------------------------------------------------------------------------------------------



UCLASS(Blueprintable, BlueprintType)
class OOO_API UArmorDT : public UObject
{
	GENERATED_BODY()


public:

	UArmorDT();

public:

	// ** Weapon-Type:   "Sword, LongSword, Axe, Bow, Hand-Fight,..... "       
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
//		EWeaponType WeaponType = EWeaponType::none;

	// ** "EquipSlot-Type" where this amunition can be placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		ESlotType AllowInventorySlotType = ESlotType::none;	// ** Melee, Gun, BigGun, pistol, ...

public:

	// ** Where Weapon Drawn, when EQUIP but it's Unactivated (on the Back or on the Belt)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		FName SocketUnactivated = FName("none");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		FName SocketActivated = FName("none");

public:

	// ** Move-Speeds, Rorate-Speeds and pictures (Mod)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<FPoseLocomotion> PoseLocomotionParamMOD;


public:

	// ** Attack behaviour/Parameter   (AnimMontage, ButtonImage, Distant, ActorCastAgent)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
//		TArray<FAttakParam> AttakParam;

};


