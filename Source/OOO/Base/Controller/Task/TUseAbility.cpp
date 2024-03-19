

// #include "Base/Controller/Task/TUseAbility.h"
#include "TUseAbility.h"

#include "../UnitAI.h"
#include "../../Unit/Base/Unit.h"

#include "../../Ability/AbilityTraceReselector.h"
#include "../../Ability/AbilityComponent.h"
#include "../../Ability/AbilityDT.h"

// -------------------

#include "NiagaraFunctionLibrary.h"			// ** SpawnSystemAttached()
#include "NiagaraComponent.h"				// ** UNiagaraComponent*

#include "Kismet/KismetMathLibrary.h"		// ** FindLookAtRotation()
#include "Kismet/GameplayStatics.h"			// ** FinishSpawningActor()

UTUseAbility::UTUseAbility()
{
	TaskType = ETaskType::UseAbility;
}


void UTUseAbility::StartTask(AUnitAI* _OwnerAI)
{
	if (!_OwnerAI)
		return;

	OwnerAI = _OwnerAI;

	// ** if start other Ability (Permanent or instance)
	if (CurrAbilityDT && CurrAbilityDT != LastAbilityDT)
	{
		StopPerformHoldingAbilityPose(_OwnerAI); 
		return;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_AbilityTick);
		AnimTimeLeft = 0.f;
		//StepStage = EStepStage::PrepareStage;
	}

	AbilityComponent = _OwnerAI->UnitOwner->Ability;
	if (!AbilityComponent)
		return;

	IdentifyTask(_OwnerAI);
	
	ContinueTask(OwnerAI);
}




void UTUseAbility::PerformHoldingAbilityPose(AUnitAI* _OwnerAI)
{

	if (GetWorld()->GetTimerManager().IsTimerActive(TH_AbilityTick))
		return;

	OwnerAI = _OwnerAI;

	//-----if(StepStage != EStepStage::ReadyToCastStage)
		StepStage = EStepStage::PrepareStage;
	//-----IsPrepareStageDone = false;
	//-----IsReadyToFire = false;


	GetPreAbilityStepDTbyCurrIndex(_OwnerAI, PreparingAbilityStep);

	// ** just has selected other Ability
/*	if (CurrAbilityDT != LastAbilityDT)
	{
		StopPerformHoldingAbilityPose(_OwnerAI);
		GetPreAbilityStepDTbyCurrIndex(_OwnerAI, PreparingAbilityStep);
	}

	LastAbilityDT = CurrAbilityDT;
*/
	if (PreparingAbilityStep)// && _OwnerAI->CurrTaskRef->TaskType = ETaskType::UseAbility)
	{
		LastAbilityDT = CurrAbilityDT;

		AnimMontage = OwnerAI->GetGameAnimation(PreparingAbilityStep->AnimationKEY);
		if (AnimMontage)
		{
			float animMontsgeLength = AnimMontage->CalculateSequenceLength();
			AnimTimeLeft = FMath::Max(animMontsgeLength, PreparingAbilityStep->DurationTime);
		}
		else
		{
			AnimTimeLeft = PreparingAbilityStep->DurationTime;
		}
		PlaySelfPrepareEffect(PreparingAbilityStep, AnimMontage);
	}
	else
	{
		StopPerformHoldingAbilityPose(_OwnerAI);
	}

}



void UTUseAbility::ContinueTask(AUnitAI* _OwnerAI) 
{

	if (GetWorld()->GetTimerManager().IsTimerActive(TH_AbilityTick))
		return;

	if (!OwnerAI)
	{
		TaskComplit(_OwnerAI);
		return;
	}

	bool hesNextAbilityStep = GetAbilityStepDTbyCurrIndex(PreparingAbilityStep);
	if (hesNextAbilityStep)
	{

		// ** Spend unit spell costing
		//---if (IsPrepareStageDone && PreparingAbilityStep == 0)
		if (StepStage == EStepStage::FinishPrepareStage && PreparingAbilityStep == 0)
		{
			// ** Cost
			// ** Cost
			// ** Cost
			// ** Cost
			// ** Cost
			//////for (int32 k = 0; k < traceReselectorActor.Num(); ++k)
			//////{
			//////	traceReselectorActor[k]->CastAbility();
			//////}

			StepStage = EStepStage::FinishPrepareStage;
		}



		// ** Self animation

		if (AnimTimeLeft <= 0.f)
		{			
			AnimMontage = OwnerAI->GetGameAnimation(PreparingAbilityStep->AnimationKEY);
			if (AnimMontage)
			{
				float animMontsgeLength = AnimMontage->CalculateSequenceLength();
				AnimTimeLeft = FMath::Max(animMontsgeLength, PreparingAbilityStep->DurationTime);
			}
			else
			{
				AnimTimeLeft = PreparingAbilityStep->DurationTime;
			}
		}
		
		if (!PlaySelfPrepareEffect(PreparingAbilityStep, AnimMontage) &&
			AnimTimeLeft <= 0)
		{
			TaskComplit(OwnerAI);
		}
	}
	else
	{
		TaskComplit(_OwnerAI);
		_OwnerAI->UnitOwner->SetHoldingAbilityState(ESlotType::none, -1, false); // ** bool isLongClick = false
		return;
	}
}




bool UTUseAbility::PlaySelfPrepareEffect(FPreparingAbilityStep* _PreparingAbilityStep, 
	UAnimMontage* _AnimMontage)//---, bool _ForcePrepareStage) 
{
	if (!_PreparingAbilityStep)
		return false;



	int32 visualEffectNum = _PreparingAbilityStep->VisualEffectDT.Num();

	if (_AnimMontage) 
		//--_AnimMontage->Notifies.Num() > 0 &&
		//--_AnimMontage->Notifies.Last().NotifyName == FName("CanBeFinish")
	{
		//--777--animMontsgeLength = _AnimMontage->Notifies.Last().GetTime();
		//--animMontsgeLength = _AnimMontage->CalculateSequenceLength() - 0.1f;
		bool isPlayTOP = _PreparingAbilityStep->IsAnimationTOP;
		float fromTime = 0.f;
		OwnerAI->PlayAnimate(AnimMontage, isPlayTOP, fromTime);
	}


	// ** Check if process is on last step of Preparing-Ability-Action  ==>>  Dont Start Visual-Effect again but Play Animate again
	//-------if (IsReadyToFire && !IsPrepareStageDone)
	if (StepStage == EStepStage::FinishPrepareStage)
	{
		GetWorld()->GetTimerManager().SetTimer(TH_AbilityTick, this, &ThisClass::AbilityTick, 0.1f, true); // ** GetWorld()->GetDeltaSeconds() * 0.1f
		return false;
	}



	// ** Add new Visual effect
	for (int32 i = 0; i < visualEffectNum; ++i)
	{
		if (_PreparingAbilityStep->VisualEffectDT[i].NiagaraEffect)
		{
			// ** 
			//----bool isAutoActivate = false;

			// **
			FName socketName = _PreparingAbilityStep->VisualEffectDT[i].Socket == FName("none")
				? NAME_None
				: _PreparingAbilityStep->VisualEffectDT[i].Socket;



			// ** 
			UNiagaraComponent* selfVisualEffectTMP = UNiagaraFunctionLibrary::SpawnSystemAttached(
				_PreparingAbilityStep->VisualEffectDT[i].NiagaraEffect,
				OwnerAI->UnitOwner->GetMesh(),
				socketName,
				FVector(0.f),
				FRotator(0.f),
				EAttachLocation::Type::KeepRelativeOffset,
				true,
				true);


			SelfVisualEffect.Add(selfVisualEffectTMP);

		}
	}

	/*
		// ** Sound
		/// .....
		/// .....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		/// .....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	*/

	// ** Break ability Task
	//if (!_AnimMontage && visualEffectNum == 0) 
		// +++++  && Sound.num() == 0
	//	return false;


	GetWorld()->GetTimerManager().SetTimer(TH_AbilityTick, this, &ThisClass::AbilityTick, 0.1f, true); // ** GetWorld()->GetDeltaSeconds() * 0.1f
	return true;
}




void UTUseAbility::AbilityTick()  
{
	if (OwnerAI->CurrTaskRef &&
		OwnerAI->CurrTaskRef->TaskType != ETaskType::UseAbility)
	{
		StopPerformHoldingAbilityPose(OwnerAI);
	}
	else
	{
		AnimTimeLeft -= 0.1f;

		if (AnimTimeLeft < 0.3f)
		{
			++iAbilityStep;

			GetWorld()->GetTimerManager().ClearTimer(TH_AbilityTick);

			if (AbilityIndex == -1)
			{
				PerformHoldingAbilityPose(OwnerAI);
			}
			else
			{
				if (StepStage == EStepStage::FinishStage)
					StepStage = EStepStage::CastingStage;

				else if (StepStage == EStepStage::CastingStage)
					InitTraceAgent();
						

				ContinueTask(OwnerAI);
				//++++++++++++++++++++++++++++
				//if(iAbilityStep > 0)

			}
		}
	}
}





bool UTUseAbility::GetPreAbilityStepDTbyCurrIndex(AUnitAI* _OwnerAI, FPreparingAbilityStep*& _PreparingAbilityStepDT) 
{
	bool isStopAction = false;
	//+++++++if ( _OwnerAI->TaskType != ETaskType::UseAbility && _OwnerAI->IsSingleTask)
	{
		//+++ isStopAction = true;
	}
	if (InstantHoldingAbility)
	{
		CurrAbilityDT = InstantHoldingAbility;
	}
	else if (PermanentHoldingAbility)
	{
		CurrAbilityDT = PermanentHoldingAbility;
	}
	else
	{
		CurrAbilityDT = nullptr;
	}
	
	if(isStopAction || !CurrAbilityDT)
	{
		StopPerformHoldingAbilityPose(_OwnerAI);
		_PreparingAbilityStepDT = nullptr;
		return false;
	}

	/*if (CurrAbilityDT != LastAbilityDT)
	{
		iAbilityStep = 0;
		LastAbilityDT = CurrAbilityDT;
	}*/

	int32 PreAbilityStepNum = CurrAbilityDT->PreparingAbilityStep.Num();
	if (iAbilityStep < 0)
		iAbilityStep = 0;


	// ** Get ability-prepare parameter (Not switch to main stage)

	if (PreAbilityStepNum == 0)
	{
		StepStage = EStepStage::FinishPrepareStage;
		//------IsPrepareStageDone = true;
		return false;
	}

	if (iAbilityStep >= PreAbilityStepNum)
	{
		StepStage = EStepStage::FinishPrepareStage;
		iAbilityStep = PreAbilityStepNum - 1;
		//--IsReadyToFire = true;
	}

	_PreparingAbilityStepDT = &CurrAbilityDT->PreparingAbilityStep[iAbilityStep];

	return true;
}



bool UTUseAbility::GetAbilityStepDTbyCurrIndex(FPreparingAbilityStep*& _PreparingAbilityStepDT) 
{
	// ** Identity AbilityRef
	if (InstantHoldingAbility)
		CurrAbilityDT = InstantHoldingAbility;
	else if (PermanentHoldingAbility)
		CurrAbilityDT = PermanentHoldingAbility;
	else if (!AbilityComponent->GetUnitAbilityByIndex(AbilityIndex, CurrAbilityDT))
	{
		return false;
	}


	int32 PreAbilityStepNum = CurrAbilityDT->PreparingAbilityStep.Num();
	if (iAbilityStep < 0)
		iAbilityStep = 0;


	// ** Get ability-prepare parameter
	// ----if (!IsPrepareStageDone)
/*	if (StepStage == EStepStage::PrepareStage)
	{
		if (iAbilityStep >= PreAbilityStepNum)//--77--- || IsReadyToFire)
		{
			StepStage = EStepStage::LustPrepareStage;
			//--------IsPrepareStageDone = true;
			iAbilityStep = 0;
		}
		else
			_PreparingAbilityStepDT = &CurrAbilityDT->PreparingAbilityStep[iAbilityStep];
	}
*/

/*	if (StepStage == EStepStage::PrepareStage ||
		StepStage == EStepStage::LustPrepareStage)
	{
		if (iAbilityStep == PreAbilityStepNum - 1)
		{
			StepStage = EStepStage::LustPrepareStage;
			_PreparingAbilityStepDT = &CurrAbilityDT->PreparingAbilityStep[iAbilityStep];
		}
		else if (iAbilityStep >= PreAbilityStepNum)
		{
			StepStage = EStepStage::ReadyToCastStage;
			iAbilityStep = 0;
		}
	}
*/
	if (StepStage == EStepStage::PrepareStage) 
	{
		if (iAbilityStep >= PreAbilityStepNum)//--77--- || IsReadyToFire)
		{
			StepStage = EStepStage::CastingStage;
			//--------IsPrepareStageDone = true;
			iAbilityStep = 0;
		}
		else
			_PreparingAbilityStepDT = &CurrAbilityDT->PreparingAbilityStep[iAbilityStep];
	}
	else if (StepStage == EStepStage::FinishPrepareStage)
	{
		StepStage = EStepStage::CastingStage;
		iAbilityStep = 0;
	}





	if (StepStage == EStepStage::CastingStage)
	{
		// ** hasn't next step (FINISH)
		if (iAbilityStep >= CurrAbilityDT->AbilityStep.Num())
			return false;

		_PreparingAbilityStepDT = &CurrAbilityDT->AbilityStep[iAbilityStep];
		AnimTimeLeft = 0.f;
	}






	// ** Get main-ability parameter
/*
	//-- if (IsPrepareStageDone)
	if (StepStage == EStepStage::LustPrepareStage)
	{
		// ** hasn't next step (FINISH)
		if (iAbilityStep >= CurrAbilityDT->AbilityStep.Num())
			return false;	
	
		_PreparingAbilityStepDT = &CurrAbilityDT->AbilityStep[iAbilityStep];
		AnimTimeLeft = 0.f;
	}
*/
	return true;
}





void UTUseAbility::OnFinishAnimation(AUnitAI* _OwnerAI, UAnimMontage* FinishedAnimMontage, bool _bInterrupted)
{
	// ** Super::OnFinishAnimation(_OwnerAI, FinishedAnimMontage, _bInterrupted);
	// ** _OwnerAI->UpdateLogic();
}



void UTUseAbility::OnAnimationNotify(AUnitAI* _OwnerAI, FString _NotifyName)
{
	if (_NotifyName == FString("Hit"))
	{
		if (StepStage == EStepStage::CastingStage)
		{
			InitTraceAgent();
			StepStage = EStepStage::FinishStage;
		}
	}
}









// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void UTUseAbility::GenrateFinaltarget(TArray<AUnit*>& _FinalTarget, 
	FAbilityTraceReselectorDT& _AbilityTraceReselectorDT)
{
	//if (_AbilityTraceReselectorDT.SelectNewTargetByCollision)
	//{
	//	// ** use "New-Hiting-Target"  (empty)
	//}/
	//else
	{
		switch (_AbilityTraceReselectorDT.SelectTargetType = ESelectTargetType::DefaultTargets)
		{
		case ESelectTargetType::DefaultTargets:


			for (int32 k = 0; k < TargetUnits.Num(); ++k)
				_FinalTarget.Add(TargetUnits[k]);
			break;
			////case ddd:

			////	break;
			////case ddd:

			////	break;

		}
		///SelfCaster,
		///PointAtCasterLocation,
		///PointInFrontOfCaster,
		///RandomUnitsAroundCasterInRadius,
		///RandomPointAroundCasterInRadius,

		///PointAtTargetLocation,
		///PointInFrontOfTarget,
		///RandomUnitsAroundTargetInRadius,
		///RandomPointAroundTargetInRadius,
	}
}




bool UTUseAbility::GetStartTracePosition(bool _IsTargetUnit, int32 _TargetsNum, 
	FAbilityTraceReselectorDT& _AbilityTraceReselectorDT,
	TArray<FVector>& _StartLocations,
	TArray<FRotator>& _Rotations)
{


	// **  Fly-to-Target (start location is Self-Unit)
	if (_AbilityTraceReselectorDT.AbilityTraseForm == EAbilityTraseForm::FlyAgentToGoal)
	{

		// ** Target point-s
		if (!_IsTargetUnit)
		{
			for (int32 i = 0; i < _TargetsNum; ++i)
			{
				_StartLocations.Add(OwnerAI->GetCurrSelfLocation());
				_Rotations.Add(UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), TargetPoints[i]));
			}
		}

		// ** Target Unit-s
		else
		{
			for (int32 i = 0; i < _TargetsNum; ++i)
			{
				_StartLocations.Add(OwnerAI->GetCurrSelfLocation());
				_Rotations.Add(UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), TargetUnits[i]->GetActorLocation()));
			}
		}
	}

	// ** Immediate-Spawn-On-Target
	else if (_AbilityTraceReselectorDT.AbilityTraseForm == EAbilityTraseForm::SpawnAgentAtLoc)
	{
		// ** Target point-s
		if (!_IsTargetUnit)
		{
			for (int32 i = 0; i < _TargetsNum; ++i)
			{
				_StartLocations.Add(TargetPoints[i]);
				_Rotations.Add(UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), TargetPoints[i]));
			}
		}

		// ** Target Unit-s
		else
		{
			for (int32 i = 0; i < _TargetsNum; ++i)
			{
				_StartLocations.Add(TargetUnits[i]->GetActorLocation());
				_Rotations.Add(UKismetMathLibrary::FindLookAtRotation(OwnerAI->GetCurrSelfLocation(), TargetUnits[i]->GetActorLocation()));
			}
		}
	}


	// ** Cone-In-Front
	else if (_AbilityTraceReselectorDT.AbilityTraseForm == EAbilityTraseForm::ConeInFront)
	{
		//++++@@@@@@@@++++ _StartLocations.Add(OwnerAI->GetCurrSelfLocation());
		//++++@@@@@@@@++++ _Rotations.Add(OwnerAI->UnitOwner->GetActorRotation());
	}

	return false;
}





bool UTUseAbility::InitTraceAgent() 
{
	if (!PreparingAbilityStep || !OwnerAI)
		return false;





	// ** Remove All visual effect
	for (int32 i = 0; i < SelfVisualEffect.Num(); ++i)
	{
		if (SelfVisualEffect[i])
			SelfVisualEffect[i]->DestroyComponent();
	}




	// ** Generate and Spawn Trace-Actor or applay effect instant
	///FAbilityStep* abilityStep = Cast<FPreparingAbilityStep*>(PreparingAbilityStep);
	FAbilityStep* abilityStep = static_cast<FAbilityStep*>(PreparingAbilityStep);
	if (!abilityStep)
		return false;

	/// ** index of "TraseReselectors" for dirrectly applay to default-Target(s)
	//-----TArray<int32> DirectApplayTraceAgentIndex;


	///+++++++TArray<AUnit*> finalTarget;
	///----TargetUnits.Num()
	///++++++++++++++GenrateFinaltarget(finalTarget, traceReselectorDT);



	

	// ** Target type (Unit-s or Point-s)
	bool isTargetUnit = true;
	int32 targetsNum = -1;
	if (TargetUnits.Num() > 0)
	{
		targetsNum = TargetUnits.Num();
	}
	else if (TargetPoints.Num() > 0)
	{
		targetsNum = TargetPoints.Num();
	}
	else
	{ 
		return false;
	}


	
	if (CurrAbilityDT->DefaultTargetType == ETargetType::Self)
	{
		if (targetsNum == 0)
		{
			// ** Instant applay Unit-Effect to self
			for (int32 k = 0; k < abilityStep->UnitEffectDT.Num(); ++k)
			{
				OwnerAI->UnitOwner->AddUnitEffect(&abilityStep->UnitEffectDT[k]);
				///--DirectApplayTraceAgentIndex.Add(k); 
			}
			return true;
		}
		else
		{
			// ** Applay to Self by BulletActor
			TargetUnits.Reset();
			TargetPoints.Reset();
			TargetUnits.Add(OwnerAI->UnitOwner);
			isTargetUnit = true;
		}
	}


	// ** Bullet(Arc) to each targets (Units / Points)
	for (int32 n = 0; n < targetsNum; ++n)
	{
		int32 TraceReselectorNum = abilityStep->AbilityTraceReselectorDT.Num();
		if (TraceReselectorNum > 0)
		{
			for (int32 i = 0; i < abilityStep->AbilityTraceReselectorDT.Num(); ++i)
			{
				FAbilityTraceReselectorDT& traceReselectorDT = abilityStep->AbilityTraceReselectorDT[i];

				// 777
				/// ** Dont use trase[i] in initialize ability
				if (!traceReselectorDT.ActivateWithStartingAbility)
					continue;
				// 777


				TArray<FVector> startLocations;
				TArray<FRotator> rotations;
				GetStartTracePosition(isTargetUnit, targetsNum, traceReselectorDT, startLocations, rotations);

				// ** Applay to target/GoalPoint by BulletActor
				for (int32 k = 0; k < startLocations.Num(); ++k)
				{
					SpawnTraceActor(isTargetUnit, targetsNum, traceReselectorDT, startLocations, rotations);
				}
			}
		}

		// ** Instant applay Unit-Effect to each Target-Tnit
		else if(isTargetUnit)
		{
			for (int32 i = 0; i < abilityStep->UnitEffectDT.Num(); ++i)
			{
				TargetUnits[n]->AddUnitEffect(&abilityStep->UnitEffectDT[i]);
			}
		}
		else
		{
			return false;
		}
	}
		/*		for (int32 i = 0; i < abilityStep->AbilityTraceReselectorDT.Num(); ++i)
				{
					FAbilityTraceReselectorDT& traceReselectorDT = abilityStep->AbilityTraceReselectorDT[i];

					/// ** Dont use trase[i] in initialize ability
					if (!traceReselectorDT.ActivateWithStartingAbility)
						continue;


					/// ** Generate startLocation and rotation (Fly-To or InstantSpawn-At)
					TArray<FVector> startLocations;
					TArray<FRotator> rotations;
					if (GetStartTracePosition(OwnerAI, TargetUnits, traceReselectorDT, startLocations, rotations))
					{
						for (int32 k = 0; k < traceReselectorDT.UnitEffectIndexes.Num(); ++k)
						{
							DirectApplayTraceAgentIndex.Add(traceReselectorDT.UnitEffectIndexes[k]);
						}
						continue;
					}

					/// ** Spawn actor
					SpawnTraceActor(TargetUnits, traceReselectorDT, startLocations, rotations);
				}
			}

			// ** DirectApplay UnitEffect
			for (int32 n = 0; n < DirectApplayTraceAgentIndex.Num(); ++n)
			{
				if (DirectApplayTraceAgentIndex[n] < 0 ||
					DirectApplayTraceAgentIndex[n] >= abilityStep->UnitEffectDT.Num())
					continue;
				for (int32 k = 0; k < TargetUnits.Num(); ++k)
					TargetUnits[k]->AddUnitEffect(&abilityStep->UnitEffectDT[DirectApplayTraceAgentIndex[n]]);
			}
		*/
	return true;
}



void UTUseAbility::SpawnTraceActor(bool _IsTargetUnit, int32 _TargetsNum,  
							FAbilityTraceReselectorDT& _AbilityTraceReselectorDT,
							TArray<FVector>& _StartLocations, TArray<FRotator>& _Rotations)
{
	// ** Spawn actor
	//-----int32 finalGoalNum = _StartLocations.Num();
	TArray<AAbilityTraceReselector*> traceReselectorActor;
	//-----bool isUnitOrPoint = _FinalTarget.Num() > 0 ? true : false;

	for (int32 i = 0; i < _TargetsNum; ++i)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = OwnerAI->UnitOwner;
		SpawnParameters.Owner = OwnerAI;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AAbilityTraceReselector* traceReselectorTMP = 
				GetWorld()->SpawnActor<AAbilityTraceReselector>(AAbilityTraceReselector::StaticClass(),
				_StartLocations[i],
				_Rotations[i],
				SpawnParameters);

		if (traceReselectorTMP)
		{
			traceReselectorActor.Add(traceReselectorTMP);


			//----FAbilityStep* abilityStep = Cast<FPreparingAbilityStep>(PreparingAbilityStep);

			traceReselectorTMP->StartLocation = _StartLocations[i];
			traceReselectorTMP->AbilityCDO = CurrAbilityDT;
			traceReselectorTMP->AbilityStep = static_cast<FAbilityStep*>(PreparingAbilityStep);
			traceReselectorTMP->AbilityTraceReselectorDT = &_AbilityTraceReselectorDT;
			traceReselectorTMP->CasterUnit = OwnerAI->UnitOwner;
			traceReselectorTMP->ChyainingActorIndex = 0;	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  ToDo


			if (_IsTargetUnit)
			{
				traceReselectorTMP->VictimUnit = TargetUnits[i];
			}
			else
			{
				traceReselectorTMP->GoalLocation = TargetPoints[i];
				//+++++++++++++traceReselectorTMP->FlyToDir = Is-Possesed;
			}

			////traceReselectorTMP->TraceReselectorIndex = i;
			////traceReselectorTMP->ExistingTimeAfterHit = traceReselectorDT.ExistingTimeAfterHit;
			////traceReselectorTMP->InitAgentRadius = traceReselectorDT.InitAgentRadius;
			////traceReselectorTMP->ChangeRadiusAfterHiting = traceReselectorDT.ChangeRadiusAfterHiting;
			////traceReselectorTMP->FlyThroughtAll = traceReselectorDT.FlyThroughtAll;
			////traceReselectorTMP->AgentSpeed = speed;
			////traceReselectorTMP->MaxDist = AbilityCDO->MaxDist;								//7777777777777777777777777777777  MaxDist
			////traceReselectorTMP->IsTrackingTarget = traceReselectorDT.IsTrackingTarget;
			//////--traceReselectorTMP->IsSelectNewTarget = traceReselectorDT.IsSelectNewTarget;
			////traceReselectorTMP->TransferVisualEffect = traceReselectorDT.TransferVisualEffect;
			//////++77++traceReselectorTMP->DurationVisualEffect = traceReselectorDT.DurationVisualEffect;

			traceReselectorTMP->CastAbility();
		}
	}
}







void UTUseAbility::StopPerformHoldingAbilityPose(AUnitAI* _OwnerAI)
{
	GetWorld()->GetTimerManager().ClearTimer(TH_AbilityTick);

	CurrAbilityDT = nullptr;
	LastAbilityDT = nullptr;
	PreparingAbilityStep = nullptr;
	//---IsPrepareStageDone = false;
	//---IsReadyToFire = false;
	StepStage = EStepStage::PrepareStage;
	AbilityIndex = -1;
	iAbilityStep = 0;
	AnimMontage = nullptr;
	AnimTimeLeft = 0.f;

	if (_OwnerAI->UnitOwner->GetCurrentMontage() == CurrAnimMontage)
	{
		_OwnerAI->UnitOwner->StopAnimate();
	}

	for (int32 i = 0; i < SelfVisualEffect.Num(); ++i)
		if (SelfVisualEffect[i]) SelfVisualEffect[i]->DestroyComponent();
	SelfVisualEffect.Reset();
}

void UTUseAbility::TaskComplit(AUnitAI* _OwnerAI)
{
	StopPerformHoldingAbilityPose(_OwnerAI);

	TargetUnits.Reset();

	Super::TaskComplit(_OwnerAI);

	//+++++if(_Get_From_AvilityComp_SELECT_Ability)
	//+++++		iHasActicateAbilityPeparePose = -1;
}


void UTUseAbility::BreakTask(AUnitAI* _OwnerAI)
{
	StopPerformHoldingAbilityPose(_OwnerAI);

	TargetUnits.Reset();

	Super::BreakTask(_OwnerAI);
}




bool UTUseAbility::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Int32Param.Num() < 1)
		return false;
	AbilityIndex = task.Int32Param[0];
	
	if (task.Uint8Param.Num() < 1)
		return false;
	IsAbilityInItem = (bool)task.Uint8Param[0];


	for (int32 i = 0; i < task.Unit.Num(); ++i)
		TargetUnits.Add(task.Unit[i]);


	//---GoalPoint = task.Vector3dParam[0];
	for (int32 i = 0; i < task.Vector3dParam.Num(); ++i)
		TargetPoints.Add(task.Vector3dParam[i]);

/*	else
	{
		IsNoTarget = true;
	}
*/
	return true;
}


// ** ----------------  Static func  ---------------


/*(----------------------)
void UTUseAbility::SetTaskData_ActionPrepareAbility(FTaskData& _TaskData,
	AUnit* _SelfUnit, int32 _AbilityIndex)//, +++++ Bool _IsActivate)
{
	//++++++++++++iHasActicateAbilityPeparePose = _AbilityIndex;
	//--777--IsActicatedAbilityPepaePose = false;

	//--_TaskData.Int32Param.Add(_AbilityIndex);

}
*/

void UTUseAbility::SetTaskData_UseAbilityToUnit(FTaskData& _TaskData, AUnit* _SelfUnit, 
	int32 _AbilityIndex, bool _IsItemAbility, TArray<AUnit*>& _TargetUnits)
{
	//---_TaskData.NameParam.Add(_AbilityName);
	_TaskData.Int32Param.Add(_AbilityIndex);
	
	//** Is item-Ability or Ability itself
	_TaskData.Uint8Param.Add(uint8(_IsItemAbility));

	for(int32 i = 0; i < _TargetUnits.Num(); ++i)
		_TaskData.Unit.Add(_TargetUnits[i]);

}


void UTUseAbility::SetTaskData_UseAbilityToLocation(FTaskData& _TaskData, AUnit* _SelfUnit,
	int32 _AbilityIndex, bool _IsItemAbility, TArray<FVector>& _GoalPoint)
{
	//---_TaskData.NameParam.Add(_AbilityName);
	_TaskData.Int32Param.Add(_AbilityIndex);

	//** Is item-Ability or Ability itself
	_TaskData.Uint8Param.Add(uint8(_IsItemAbility));

	//--_TaskData.Vector3dParam.Add(_GoalPoint);
	for (int32 i = 0; i < _GoalPoint.Num(); ++i)
		_TaskData.Vector3dParam.Add(_GoalPoint[i]);
}

/*
void UTUseAbility::SetTaskData_UseAbility(FTaskData& _TaskData, AUnit* _SelfUnit, 
	int32 _AbilityIndex, bool _IsItemAbility)
{
	//---_TaskData.NameParam.Add(_AbilityName);
	_TaskData.Int32Param.Add(_AbilityIndex);

	//** Is item-Ability or Ability itself
	_TaskData.Uint8Param.Add(uint8(_IsItemAbility));
}
*/