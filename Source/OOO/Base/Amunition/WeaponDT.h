
#pragma once

//#include Base/Amunition/WeaponDT.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Enum/WeaponType.h"
#include "../Inventory/Enum/SlotType.h"

#include "../Unit/Struct/PoseLocomotion.h"

//------------#include "Srtuct/WeaponDT.h"


#include "WeaponDT.generated.h"



USTRUCT(BlueprintType, Blueprintable)
struct FAttachActionParam
{

	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()
		


	// ** Button using Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		UTexture2D* ButtonImage;

	// ** Can't Attack when Target Closer then...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float MinDist = 100.f;
	// ** Can't Attack when Target far then...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float MaxDist = 500.f;
	// ** Optimal distance for Fire (betwean Attack AI_Unit will shift to optimal distance)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float OptimalDist = 150.f;
	// ** if can Aiming  (it's "Field Od View" parameter)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float SnipeZoomFOV = -1.f;

	// ** if can Aiming  (it's "Field Od View" parameter)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float RollBackTime = 30.f;
	// ** Hit probability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float Accuracy = 70.f;



//	// ** AnimBlueprint for Character while this Weapon Using
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Param")
//		EWeaponType WeaponTypeAnimSet = EWeaponType::HandFight;


	// ** Speeds and pictures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_PoseLocomotion")
				TArray<struct FPoseLocomotion> PoseLocomotionParam;





			// ** Actor stored all Effect-Parameter   (spawning when AnimNotify-trigger or Collision-Hit)
//++++			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
//++++				TSubclassOf<class ACastAndImpactEffect> Agent;

};


UCLASS(Blueprintable, BlueprintType)
class OOO_API UWeaponDT : public UObject
{
	GENERATED_BODY()


public:

	// ** Slot-Weapon-Type:   "Sword, LongSword, Axe, Bow, Hand-Fight, "       
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		EWeaponType WeaponType = EWeaponType::Sword;

	// ** "EQUIP-Slot-Type" where this amunition can be placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		ESlotType AllowInventorySlotType = ESlotType::cup;	// ** Melee, Gun, BigGun, pistol, ...

	// ** Attack behaviour/Parameter   (AnimMontage, ButtonImage, Distant, ActorCastAgent)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<FAttachActionParam> AttachActionParam;

	// ** Where Weapon Drawn, when EQUIP but it's Unactivated (on the Back or on the Belt)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		FName SocketUnactivated = FName("none");




};


