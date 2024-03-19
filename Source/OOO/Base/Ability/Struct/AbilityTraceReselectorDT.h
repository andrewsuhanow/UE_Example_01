
// #include "Base/Ability/Struct/AbilityTraceReselectorDT.h"

#pragma once

#include "../Enum/AbilityTraseForm.h"
#include "../Enum/SelectTargetType.h"	// ** @@@@@@@@@@@@@@@@@ 7777777777777 @@@@@@@@@@@@@@@@  select other targets (if NEED)

#include "AbilityTraceReselectorDT.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FAbilityTraceReselectorDT
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

public:
	
	// ** UnitEffectIndexes to applay by this Reselector Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		TArray<int32> UnitEffectIndexes;

	// ** This "Trace Reselector index" dont use in first casting
	// ** but it can be started from AbilityEffect when effect will be applay (for chain effect)
	// ** Need: Set it index in "Ability World Effect" in "Generate New Trase Reselector"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		bool ActivateWithStartingAbility = true;




	// ** 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		EAbilityTraseForm AbilityTraseForm = EAbilityTraseForm::FlyAgentToGoal;



	// ** Fly throught all hiting targets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			DisplayName = "** Fly through all (ignore hiting)",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal ", EditConditionHides))
		bool FlyThroughtAll = false;

	// ** Smart fly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
		DisplayName = "** Chasing the target",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal ", EditConditionHides))
		bool IsTrackingTarget = false;

	// ** Applae Effect to new selected targets
	//--UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
	//--	DisplayName = "Select new target(s) (by Trace collider)")
	//--	bool IsSelectNewTarget = true;

	// ** 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
				meta = (EditCondition = "!SelectNewTargetByCollision"))
		ESelectTargetType SelectTargetType = ESelectTargetType::DefaultTargets;		// ** @@@@@@@@@@@@@@@@@ 7777777777777 @@@@@@@@@@@@@@@@  select other targets (if NEED)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO",
		DisplayName = "** Radius for AroundAgentSelected",
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  TAG, Enter
		meta = (EditCondition = "SelectTargetType == ESelectTargetType::RandomUnitsAroundCasterInRadius || 			SelectTargetType == ESelectTargetType::RandomPointAroundCasterInRadius || 			SelectTargetType == ESelectTargetType::RandomUnitsAroundTargetInRadius || 			SelectTargetType == ESelectTargetType::RandomPointAroundTargetInRadius",
			EditConditionHides))
		float RandomTargetCount = 200.f;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ") 
		float InitAgentRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal", EditConditionHides))
		float AgentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal", EditConditionHides))
		float ChangeRadiusAfterHiting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			meta = (EditCondition = "AbilityTraseForm != EAbilityTraseForm::ConeInFront", EditConditionHides))
		float LifeTimeAfterHit;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal", EditConditionHides))
		UStaticMesh* AgentStMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ",
			meta = (EditCondition = "AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal", EditConditionHides))
		USkeletalMesh* AgentSkMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		class UNiagaraSystem* TransferVisualEffect;
	//++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
	//++	USoind* AgentSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		class UNiagaraSystem* ExplosionVisualEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		class UNiagaraSystem* DurationVisualEffect;
	//++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
	//++	USoind* DurationSound;

	
};