
#pragma once

// #include "Base/Ability/AbilityDT.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "../Controller/Enum/TargetType.h"

#include "../VisualEffect/Struct/VisualEffectData.h"

#include "../UnitEffect/Struct/UnitEffectDT.h"
#include "Struct/AbilityTraceReselectorDT.h"
//--777--#include "Enum/WeaponType.h"
//--777--#include "../Inventory/Enum/SlotType.h"

//--777--#include "../Unit/Struct/PoseLocomotion.h"
//-------#include "Enum/AttackHitCollisionType.h"
#include "../Amunition/Enum/UseDistanceType.h"

#include "../Animation/Enum/AnimationKey.h"

// ** !!!!!!!!!!!!!!!! Abulity may spend mana, stamina, ..., or item from invertory
//+++++++#include "Struct/AbilityCost.h"


#include "AbilityDT.generated.h"



USTRUCT(BlueprintType, Blueprintable)
struct FPreparingAbilityStep
{

	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()


public:



	// ** for 3rd (if Gamer hold mouse button "DurationTime = infinity")
	//----UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//----	bool HoldingByMouseHold = false;


	// **  0	- Play animate once time
	// **  1...	- Play animate duration secconds
	// ** -1	- Dont play 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float DurationTime = 0;							  


	// ++++++ TArray<Niagara*> SelfEffectOnSocket;
	// ++++++ TArray<FName> SelfEffectSocketName;
	// ++++++ TArray<ETimeToPlay> TimeToPlayEffect			(AllStepsDuration, ThisStepDuration, SelfTimeOnce)

	// ++++++ TArray<Niagara*> SelfSoundOnSocket;
	// ++++++ TArray<FName> SelfSoundSocketName;
	// ++++++ TArray<ETimeToPlay> TimeToPlaySound			(AllStepsDuration, ThisStepDuration, SelfTimeOnce)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		EAnimationKey AnimationKEY; // = EAnimationKey::none;
	// ** if Animation for Full body unit cant be moving while casting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		bool IsAnimationTOP; // = EAnimationKey::none;
	// ++++++ TArray<ETimeToPlay> TimeToPlayAnimate			(AllStepsDuration, ThisStepDuration, SelfTimeOnce)


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<FVisualEffectData> VisualEffectDT;

	//++++	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//++++		Sound* IdleSelfSound;




};



USTRUCT(BlueprintType, Blueprintable)
struct FAbilityStep : public FPreparingAbilityStep
{
	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO! ")
		TArray<FAbilityTraceReselectorDT> AbilityTraceReselectorDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO! ")
		TArray<FUnitEffectDT> UnitEffectDT;
};



// ** -------------------------------------------------------------------------------------------



UCLASS(Blueprintable, BlueprintType)
class OOO_API UAbilityDT : public UObject
{
	GENERATED_BODY()


public:

	UAbilityDT();



	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//---	bool CanBePermanent = true;


public:

	// **!!!!!!!!** Name must be like an "Object" name in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		FName AbilitytName = FName("none");

	// ** Button using Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")	
		UTexture2D* AbilityImage;
	UTexture2D* GetImage() const;

	// ** Target-s selected by ability-Button click and select Target by mouse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		ETargetType DefaultTargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!",
		meta = (EditCondition = "DefaultTargetType == ETargetType::Units ", EditConditionHides))
		int32 DefaultTargetsCount;


	// ** Ability has RollBack-Round-Time and
	// ** has a quantity for use consecutively
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float MaxConsecutiveQuantity = 0;

	// ** Roll-Back-Time (Rounds count)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 RollBackTime = 0;
	

	// ** Allow distance to target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float MinDist = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		float OptimalDist = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		//EUseDistanceType UseDistanceType = EUseDistanceType::optimal_dist;
		float MaxDist = 1200.f;
	

public:

	// ** !!!!!!!!!!!!!!!! Abulity may spend mana, stamina, ..., or item from invertory
	//+++++++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
	//+++++++	TArray<FAbilityCost> AbilityCost;

	// ** Ability select but no use jet (mostly use: AnimMontage, VisualEffect, Sound)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<FPreparingAbilityStep> PreparingAbilityStep;
		//----TArray<FPreparingAbilityStep> PreAbilityPoseStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<FAbilityStep> AbilityStep;

	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
	//---	int32 StartCastingFromStep = 0;




#if WITH_EDITORONLY_DATA  // #if WITH_EDITOR 

	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;

#endif

};


