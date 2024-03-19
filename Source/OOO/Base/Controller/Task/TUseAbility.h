
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../../Ability/Enum/AbilityTraseForm.h"
#include "../../Ability/Enum/SelectTargetType.h"
#include "../../Ability/Struct/AbilityTraceReselectorDT.h"

#include "Base/Task.h"

#include "TUseAbility.generated.h"



UENUM()
enum class EStepStage : uint8
{
	PrepareStage,
	FinishPrepareStage,
	CastingStage,
	//--ReadyToCast,
	FinishStage,
};


UCLASS()
class OOO_API UTUseAbility : public UTask
{
	GENERATED_BODY()

public:

	UTUseAbility();

	UPROPERTY() class UAbilityDT* PermanentHoldingAbility = nullptr;
	UPROPERTY()	class UAbilityDT* InstantHoldingAbility = nullptr;

	// ** Check if ability change
	UPROPERTY()	class UAbilityDT* LastAbilityDT = nullptr;
	UPROPERTY()	class UAbilityDT* CurrAbilityDT = nullptr;
	


	// ** UPROPERTY() 
		//struct FAbilityStep* AbilityStep;
		struct FPreparingAbilityStep* PreparingAbilityStep;

	UPROPERTY() EStepStage StepStage = EStepStage::PrepareStage;
	//--UPROPERTY() bool IsPrepareStageDone = false;
	//--UPROPERTY() bool IsReadyToFire = false;
	//---UPROPERTY() bool IsSpandCost = false;

	UPROPERTY() int32 iAbilityStep = 0;
	UPROPERTY() UAnimMontage* CurrAnimMontage = nullptr;
	UPROPERTY() float AnimTimeLeft = 0.f;
	UPROPERTY() UAnimMontage* AnimMontage = nullptr;


	//-----------SelfVisualEffect
	//-----------StoredVisualEffectData
	UPROPERTY() TArray<class UNiagaraComponent*> SelfVisualEffect;
	UPROPERTY() TArray<bool> IsPlayingOnlyOneStep; 
	//--	_BeforeHit;
	//--UPROPERTY() TArray<class UNiagaraComponent*> SelfVisualEffect_AfterHit;
	// ** use in "UTUseAbility"
	//------TArray<struct FVisualEffectData*> StoredVisualEffectData;
	
	///--UPROPERTY() bool IsAbilityStepStarted = false;
	UPROPERTY() int32 AbilityIndex = -1;				
	///--777--UPROPERTY() class UAbilityDT* AbilityCDO;

	UPROPERTY() bool IsAbilityInItem = false;

	UPROPERTY() TArray<class AUnit*> TargetUnits;
	UPROPERTY() TArray<FVector> TargetPoints;

	UPROPERTY() class UAbilityComponent* AbilityComponent = nullptr;
	
	//-------UPROPERTY() bool IsNoTarget = false;		// ** No Units, no Location

	

public:

	UPROPERTY()	AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	UFUNCTION()
		void PerformHoldingAbilityPose(class AUnitAI* _OwnerAI);

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	//UFUNCTION()
	bool PlaySelfPrepareEffect(struct FPreparingAbilityStep* _PreparingAbilityStep,
								UAnimMontage* _AnimMontage);

	UPROPERTY()	FTimerHandle TH_AbilityTick;
	UFUNCTION()
		void AbilityTick();

	//UFUNCTION()	
	bool GetPreAbilityStepDTbyCurrIndex(class AUnitAI* _OwnerAI, struct FPreparingAbilityStep*& _PreparingAbilityStepDT);
	//UFUNCTION()
	bool GetAbilityStepDTbyCurrIndex(struct FPreparingAbilityStep*& _PreparingAbilityStepDT);

	virtual void OnFinishAnimation(class AUnitAI* _OwnerAI,
								UAnimMontage* FinishedAnimMontage, bool _bInterrupted) override;

	virtual void OnAnimationNotify(AUnitAI* _OwnerAI, FString _NotifyName) override;


	UFUNCTION()
		void StopPerformHoldingAbilityPose(class AUnitAI* _OwnerAI);

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;

	
	
public:


	UFUNCTION()
		void GenrateFinaltarget(TArray<AUnit*>& _FinalTarget, 
			FAbilityTraceReselectorDT& _AbilityTraceReselectorDT);
	UFUNCTION()
		bool GetStartTracePosition(bool _IsTargetUnit, int32 _TargetsNum,
			FAbilityTraceReselectorDT& _AbilityTraceReselectorDT,
			TArray<FVector>& _StartLocations,
			TArray<FRotator>& _Rotations);

	UFUNCTION()
		bool InitTraceAgent();

	UFUNCTION()
		void SpawnTraceActor(bool _IsTargetUnit, int32 _TargetsNum, 
							FAbilityTraceReselectorDT& _AbilityTraceReselectorDT,
							TArray<FVector>& _StartLocations, TArray<FRotator>& _Rotations);


	// ** ---------------------  Static func  ------------------------

public:

//----	UFUNCTION()
//---		static void SetTaskData_ActionPrepareAbility(FTaskData& _TaskData, class AUnit* _SelfUnit,
//---			int32 _AbilityIndex/*, +++++ Bool _IsActivate*/);

	UFUNCTION()
		static void SetTaskData_UseAbilityToUnit(FTaskData& _TaskData, class AUnit* _SelfUnit, 
			int32 _AbilityIndex, bool _IsItemAbility, TArray<class AUnit*>& _TargetUnits);


	UFUNCTION()
		static void SetTaskData_UseAbilityToLocation(FTaskData& _TaskData, class AUnit* _SelfUnit, 
			int32 _AbilityIndex, bool _IsItemAbility, TArray<FVector>& _GoalPoint);


/*	UFUNCTION()
		static void SetTaskData_UseAbility(FTaskData& _TaskData, class AUnit* _SelfUnit, 
			int32 _AbilityIndex, bool _IsItemAbility);
*/
};



