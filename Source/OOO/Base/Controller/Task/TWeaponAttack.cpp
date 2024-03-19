

// ** #include "Base/Controller/Task/TWeaponAttack.h"
#include "TWeaponAttack.h"

#include "../../Unit/Base/Unit.h"
#include "../UnitAI.h"

#include "Enum/TacticalMoveStepLogic.h"
#include "Enum/AttackTaskSeries.h"

#include "../../Amunition/WeaponWorldItem.h"

#include "../../Base/Enum/PossesingGameState.h"
#include "../../Amunition/Enum/UseDistanceType.h"

#include "../../UnitState/Enum/UnitParam.h"

#include "TMoveTo.h"
#include "TWait.h"

// -----------

#include "Kismet/KismetSystemLibrary.h" 


#include "NavigationSystem.h"
#include "NavigationPath.h"




UTWeaponAttack::UTWeaponAttack()
{
	TaskType = ETaskType::WeaponAttack;

	SeriesAttackIndexes.Reset();
}


void UTWeaponAttack::StartTask(AUnitAI* _OwnerAI)
{
	OwnerAI = _OwnerAI;

	if (!IsInAttackSeries() && CurrTargetUnit)
	{
		// ** if dist too close (go back)
		bool isOtherActionStart = CheckAndMoveFromCloserDist(_OwnerAI, CurrTargetUnit, 
													nullptr, ETaskCauser::ChildTask);
		if (isOtherActionStart)
			return;
	}

	ContinueTask(_OwnerAI);
}


void UTWeaponAttack::ContinueTask(AUnitAI* _OwnerAI)
{
	if (!IsUsingAnimate)
	{
		// ** Set data from Task
		if (!IdentifyTask(_OwnerAI))
		{
			TaskComplit(_OwnerAI);
			return;
		}


		// ** Cheak Weapon (Start Sub-Task "Activate-Weapon")
		if (!_OwnerAI->IsWeaponActive())
		{
			ResetAttackData(_OwnerAI);

			FTaskData activateWpnSubTask;
			_OwnerAI->SetTask(false, ETaskType::ActivateWeapon, activateWpnSubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
			return;
		}

		// ** Get Weapon-Parameter (CDO)
		AWeaponWorldItem* weaponItem = _OwnerAI->GetCurrWeaponItem();
		FItemDT* currWpnItemData = &weaponItem->ItemDT;
		UWeaponDT* currWeaponDT = currWpnItemData->WeaponDT->GetDefaultObject<UWeaponDT>();


		

		if (!IsInAttackSeries())
		{
			// ** Generate Attack-Series (select weapon-attack indexes)
			ActualWpnAttackIndex = GenerateAttackIndex(_OwnerAI, weaponItem, currWeaponDT);
			if (ActualWpnAttackIndex == -1)
			{
				TaskComplit(_OwnerAI);
				return;
			}
			else
				LastWeaponDT = currWeaponDT;


			EUseDistanceType AttackUsingDistance = currWeaponDT->AttakParam[ActualWpnAttackIndex].UseDistanceType;
			EPossesingGameState possesingGameState = _OwnerAI->GetPossesingGameState();
			//if (possesingGameState == top_down)
			//{
			//}
			//else // ** EPossesingGameState:  possesing,  possesing_ai;
			//{
			//}

			
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			// ** if Can Fight From Anywhere
			if (AttackUsingDistance == EUseDistanceType::any_dist)
			{
				AttackAction(_OwnerAI);
				return;
			}


			// ** if Can Fight from vary far (clear vision)
			if (AttackUsingDistance == EUseDistanceType::any_dist_clear_vision)
			{
				// +++    Check clear dist
				// +++	  {	
				// +++		  Find and move to clear-Vision position  (EQS)
				// +++		  return;
				// +++	  }	

				// +++ AttackAction(_OwnerAI);
			}


			// ** if dist too far  (Move to TargetActor to Max-Dist)
			bool isOtherActionStart = CheckAndMoveMaxDist(_OwnerAI, currWeaponDT);
			if (isOtherActionStart)
				return;


			// ** Tactical Move
			// +++++++ (DistToPlayer() < 1500 && PlayerLoocOnUnit())
			// +++++++ possesingGameState != EPossesingGameState::top_down
			{
				//++++if(__CONTACT__)
				isOtherActionStart = CheckOnTacticalMove(_OwnerAI, CurrTargetActor, weaponItem);
				if (isOtherActionStart)
					return;
				//++++if(__RANGE_)
				//.......
				//.......
			}


			// -----------4444444
			//	++++ if Attack need clear Vision
			{
				//			isOtherActionStart = CheckAndFindClearVisionPosition(_OwnerAI);
				//			if (isOtherActionStart)
				//				return;
			}

			
			// -----------6666666
			// +++ Correct Attack Distance
			{
				//++++if(__CONTACT__)
				isOtherActionStart = CorectDistBeforeAttack(_OwnerAI, CurrTargetActor, weaponItem);
				if (isOtherActionStart)
					return;

				//++++if(__RANGE_)
				//.......
				//.......
			}


			// -----------7777777
			// ** if(CheckRotate())
			{
				// return;
			}

		}
		else
		{
			ResetTacticalMoveData();
			_OwnerAI->SetFocus(CurrTargetActor);
		}
		



		// ** Get Animate
		UAnimMontage* animate = nullptr;
//		if (AnimAttackStage == -1)
//		{
//			animate = _OwnerAI->GetGameAnimation
//			(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_ByAttackStage(AnimAttackStage));
//		}
//		else
//		{

		bool isPlayTOP = false;
		if(true) //+++++if (_____3rd_____) if (possesingGameState == top_down)
		{
			if (IsInAttackSeries())
			{
				animate = _OwnerAI->GetGameAnimation
				(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_AlternateAttack());
			}
			else
			{
				animate = _OwnerAI->GetGameAnimation
				(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_Attack());
			}
			isPlayTOP = false;
		}
		else
		{
			if (IsInAttackSeries())
			{
				animate = _OwnerAI->GetGameAnimation
				(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_AlternateAttackInPlace());
			}
			else
			{
				animate = _OwnerAI->GetGameAnimation
				(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_AttackInPlace());
			}
			isPlayTOP = true;
		}


		// ** Start Animate
		if (animate)
		{
			////////////////bool isPlayTOP = false;
			//////////////////+++++if (_____3rd_____) if (possesingGameState == top_down)
			////////////////{
			////////////////	isPlayTOP = true; // currWeaponDT->AttakParam[ActualWpnAttackIndex].IsAnimTOP_3rd;
			////////////////}
			//////////////////+++++else
			////////////////{
			////////////////	// isPlayTOP = currWeaponDT->AttakParam[ActualWpnAttackIndex].IsAnimTOP_RTS;
			////////////////}

			float fromTime = 0.f;
			_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);

			IsUsingAnimate = true;
			return;
		}
	}
}


void UTWeaponAttack::OnAnimationNotify(AUnitAI* _OwnerAI, FString _NotifyName)     
{
												/*
												TArray<FHitResult> XXXtraceHit;

												FHitResult AAA;
												AAA.Actor = _OwnerAI->TasksBuffer.Last().TargetUnit;
												AAA.bBlockingHit = true;
												XXXtraceHit.Add(AAA);

												FHitResult BBB;
												BBB.Actor = _OwnerAI->TasksBuffer.Last().TargetUnit;
												BBB.bBlockingHit = true;
												XXXtraceHit.Add(BBB);
												*/
/*


	UWeaponDT* currWeaponDT = currWpnItemData->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>(); 
	int32 weaponAttackIndex = 0;
	
	FTransform socketParam = _OwnerAI->GetUnitSocketParam(currWeaponDT->SocketActivated);

	FVector unitPosition = _OwnerAI->GetCurrSelfLocation();
	FVector startPosition = socketParam.GetLocation();
	//startPosition.Z = unitPosition.Z;
	//FVector dir = (startPosition - unitPosition).GetSafeNormal();
	//FVector DirPoint = startPosition + dir * currWeaponDT->AttakParam[weaponAttackIndex].MinDist - 50.f;

	FVector upVector = socketParam.GetRotation().GetAxisZ();		// ** Up
	FVector endPosition = startPosition + upVector * currWeaponDT->AttakParam[weaponAttackIndex].MinDist - 50.f;



	FHitResult TraceHit;
	FCollisionQueryParams TraceParams(FName("Ray_Cast"), true, _OwnerAI);
	TraceParams.bTraceComplex = true;
	//---ECollisionChannel CollisionChannel; // ** ECollisionChannel::ECC_WorldStatic, ECC_WorldDynamic, ECC_Pawn, ECC_Visibility, ECC_Camera
	//----FCollisionResponseParams ResponseParams; // ** ECollisionResponse::ECR_Block
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	// ** Single Line
	GetWorld()->LineTraceSingleByObjectType(TraceHit,
		startPosition,		// ** stert
		endPosition,		// ** end
		ObjectQueryParams,
		TraceParams);


	DrawDebugLine(
		GetWorld(),
		startPosition,	
		endPosition,	//TraceEnd,
		FColor::Blue,
		true,			// is visible always
		3.5f,			// visible time
		0,
		5.0f); // siknes

*/



	AWeaponWorldItem* weaponItem = _OwnerAI->GetCurrWeaponItem();
	UWeaponDT* currWeaponDT = weaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

	////////++++++++++++++++++++++
	////////WeaponAttacIndex = weaponItem ? weaponItem->CurrAttacIndex : -1;
	////////float maxTaskDist = -1;			// ** Weapon-Sharp length

	////////if (WeaponAttacIndex == -1)
	////////	return;



	// ** Task can be finish (if need started other task)
	// ** or may continue

	if (_NotifyName == FString("CanBeFinish"))
	{

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   Player Has Player Task-Queue
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



		// ** Get/Check next attck in current series
		int32 currAttackIndex = CheckAndGetNextAttackIndex();

		if (currAttackIndex == -1 || CurrTargetUnit->GetParam(EUnitParam::HP) < CurrTargetUnit->GetParam(EUnitParam::CritHP))
		{
			ResetAttackData(_OwnerAI);
			IsUsingAnimate = false;

			if (!IsInAttackSeries() && CurrTargetUnit)
			{
				// ** if dist too close (go back)
				CheckAndMoveFromCloserDist(_OwnerAI, CurrTargetUnit, weaponItem, ETaskCauser::NpcTask);
			}
			TaskComplit(_OwnerAI);
		}
		else
		{
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    TEST  7777777777777777
			if (_OwnerAI->FractionQueueTaskDT.Num() > 0)
			{
				_OwnerAI->FractionQueueTaskDT.RemoveAt(0);
			}



			FTaskData nextSeriesAttackTask;
			UTWeaponAttack::SetAttackData_AttackUnit(nextSeriesAttackTask, CurrTargetUnit, currAttackIndex);

			ResetTask(_OwnerAI);
			_OwnerAI->CurrTaskRef = nullptr;

			_OwnerAI->SetTask(false, ETaskType::WeaponAttack, nextSeriesAttackTask, ETaskCauser::NpcTask, ETaskPriority::Normal);
			UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:   AttackSeries----( i: _%i_ ) "), currAttackIndex);
			// ** TaskComplit(_OwnerAI);
		}
		return;
	}
	else if (_NotifyName == FString("Finish"))
	{
		/*		IsCanDoAttackSeries = true;
				TimeAttackTickLeft = 0.5f;
				GetWorld()->GetTimerManager().SetTimer(TH_WeaponAttackTick, this, &ThisClass::WeaponAttackTick,
					GetWorld()->GetDeltaSeconds(), false);

				@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*/

		
		return;
	}
/*	 (++++++++++++++++++++++++++++++++)
// ** Attack signal (anim time for <Dodge / Block / Parir>) 
	// ** Send signal to victim for start special Task-anim 

	e;se if (_NotifyName == FString("AttackSignal"))
	{
		AUnit* SelfUnit = _OwnerAI->UnitOwner;
		maxTaskDist = currWeaponDT->AttakParam[WeaponAttacIndex].MaxDist;	// ** fire dist
		TArray<FHitResult> traceBoundHit;


		// ** Get all Target around  (Bound-Trace)

		switch (currWeaponDT->AttakParam[WeaponAttacIndex].AttackCollisionType)
		{
		case EAttackHitCollisionType::Simple:
		case EAttackHitCollisionType::Fire:
		case EAttackHitCollisionType::Bullet:
			{
				FVector targetLocation = _OwnerAI->TasksBuffer.Last().TargetUnit ?
					_OwnerAI->TasksBuffer.Last().TargetUnit->GetActorLocation() :
					_OwnerAI->TasksBuffer.Last().Location;

				float victimDist = FVector::Distance(_OwnerAI->UnitOwner->GetActorLocation(), targetLocation);

				if (victimDist > maxTaskDist)	return;
				
				FHitResult hitResult;
				hitResult.Actor = _OwnerAI->TasksBuffer.Last().TargetUnit;
				hitResult.bBlockingHit = true;
				traceBoundHit.Add(hitResult);
				break;
			}
		case EAttackHitCollisionType::Front:
			{
				WeaponLenght = currWeaponDT->AttakParam[WeaponAttacIndex].OptimalDist;
				StartPoint = EndPoint = _OwnerAI->UnitOwner->GetActorLocation() + _OwnerAI->UnitOwner->GetActorForwardVector() * WeaponLenght / 2.f;
				WeaponLenght *= 1.1f;// *= 0.8f;	// ** Attack dist
				GenerateWeaponBoundHit(_OwnerAI, traceBoundHit, StartPoint, EndPoint, WeaponLenght);
				break;
			}
		case EAttackHitCollisionType::Around:
			{
				WeaponLenght = currWeaponDT->AttakParam[WeaponAttacIndex].OptimalDist;
				StartPoint = EndPoint = _OwnerAI->UnitOwner->GetActorLocation();
				WeaponLenght *= 1.2f;	// ** Attack dist
				GenerateWeaponBoundHit(_OwnerAI, traceBoundHit, StartPoint, EndPoint, WeaponLenght);
				break;
			}
		case EAttackHitCollisionType::Sting:
			{
				WeaponLenght = currWeaponDT->AttakParam[WeaponAttacIndex].OptimalDist;
				StartPoint = _OwnerAI->UnitOwner->GetActorLocation();				
				EndPoint = StartPoint + _OwnerAI->UnitOwner->GetActorForwardVector() * WeaponLenght * 1.7f;
				WeaponLenght = 20.f;	// ** Attack dist
				GenerateWeaponBoundHit(_OwnerAI, traceBoundHit, StartPoint, EndPoint, WeaponLenght);
				break;
			}
		}

		// ** Send signal to victom (Dodge / Block / Parrir)

		for(int32 i = 0; i < traceBoundHit.Num(); ++i)
		{
			AUnit* potentialVictim = Cast<AUnit>(traceBoundHit[i].Actor);
			if (potentialVictim)
			{
				/// ** Calculate probability Victim-Tasks  **
				/// ** ----------------------------------
				/// ** 
				/// ** Dodge
				/// ** Block
				/// ** Parrir
				/// ** 
				ETaskType task = ETaskType::none;


				// **  Calculate  ...
				task = ETaskType::Dodge;				// @@@@@@@@@@@  ...  TEST
				// ++++++++ task = ETaskType::Block;	// @@@@@@@@@@@  ...  TEST 
				// ++++++++ task = ETaskType::Parrir;	// @@@@@@@@@@@  ...  TEST

				FTaskData taskData;
				taskData.TargetUnit = _OwnerAI->UnitOwner;
				bool bAddMoreOneTask_NO_MATTER = false;

				////////switch (task)
				////////{
				////////case ETaskType::Dodge:


				////////	break;
				////////case  ETaskType::Block:
				////////	break;
				////////case  ETaskType::Parrir:
				////////	break;
				////////}
				
				potentialVictim->SetUnitTask(bAddMoreOneTask_NO_MATTER, task, taskData,
					ETaskInstigator::Dominant, ETaskPriority::Hi);
			}
		}

	}


	// **  Hit (anim time)			_NotifyName == FString("Hit")   ||   _NotifyName == FString("AlvaysHit")

	else 
	{
		
		// ** ATTACK-DETECT-Collision-Type:

		switch (currWeaponDT->AttakParam[WeaponAttacIndex].AttackCollisionType)
		{

		case EAttackHitCollisionType::Simple:
			/// ** IGNOR if "Hit" seccond time
			if (_NotifyName == FString("Hit") && 
				_OwnerAI->TasksBuffer.Last().TargetUnit &&
				CurrHittingActors.Contains(_OwnerAI->TasksBuffer.Last().TargetUnit))	
				return;
			/// ** else (_NotifyName == FString("OverHit"))
			TraceHit.Actor = _OwnerAI->TasksBuffer.Last().TargetUnit;
			TraceHit.bBlockingHit = true;
			break;

		case EAttackHitCollisionType::Front:
		case EAttackHitCollisionType::Around:
		case EAttackHitCollisionType::Sting:

			GenerateWeaponContactRayCast(_OwnerAI, weaponItem, TraceHit);
			/// ** IGNOR if "Hit" seccond time
			if (TraceHit.GetActor() && _NotifyName == FString("Hit") &&
				CurrHittingActors.Contains(TraceHit.GetActor()))
				return;
			/// ** else (_NotifyName == FString("OverHit"))
			break;

		case EAttackHitCollisionType::Fire:

			maxTaskDist = currWeaponDT->AttakParam[WeaponAttacIndex].MaxDist;			// ** fire dist
			GenerateWeaponRangeRayCast(_OwnerAI, weaponItem, TraceHit, maxTaskDist);

			if (TraceHit.GetActor() && _NotifyName == FString("Hit") &&
				CurrHittingActors.Contains(TraceHit.GetActor()))
				return;
			/// ** else (_NotifyName == FString("OverHit"))
			break;

		case EAttackHitCollisionType::Bullet:
			// ** @@@@@
			// ** @@@@@ ...... Spawn-Bullet-Actor;
			// ** @@@@@
			return;
		}



		// ** Hit result
		if (TraceHit.bBlockingHit)
		{
			AUnit* unitTarget = Cast<AUnit>(TraceHit.GetActor());
			if (unitTarget)
			{
				if (!CurrHittingActors.Contains(TraceHit.GetActor()))
				{
					// ** This Units don't be attaks seccond time
					CurrHittingActors.Add(TraceHit.GetActor());

					// ** if(unitTarget->(Block / Parir / Dodge)

					// Victim can parrir
					if (unitTarget->AI->CurrTaskRef &&
						unitTarget->AI->CurrTaskRef->TaskType == ETaskType::Parrir)
					{
						// ** Start Animate (Attack failed)
						UAnimMontage* animate = nullptr;
						animate = _OwnerAI->GetGameAnimation(EAnimationKey::failed_attack_parrired);
						if (animate)
						{
							bool isPlayTOP = false;
							float fromTime = 0.f;
							_OwnerAI->PlayAnimate(animate, isPlayTOP, fromTime);

							IsUsingAnimate = true;
							return;
						}
					}
					else
					{
						// ** unitTarget  

						// ** Draw Damage effect
						// ** Victim->SetTask(GetHit)
						// ** Victim->SetDamage


						// **		unitTarget-> SentDamageData(HP / Armor / EP);
						// **		unitTarget-> SentDamageGeometryType;
						// **		unitTarget-> SentDamagePoint;
						// **		unitTarget-> SentDamagePointNormale;
					}
				}
				

				

				return;
			}
		}
		
	}
*/





	




}



void UTWeaponAttack::WeaponAttackTick()
{
/*	TimeAttackTickLeft -= GetWorld()->GetDeltaSeconds();


	if (IsCanDoAttackSeries && TimeAttackTickLeft <= 0.f)
		ResetAttackData(_OwnerAI);
	else
		GetWorld()->GetTimerManager().SetTimer(TH_WeaponAttackTick, this, &ThisClass::WeaponAttackTick,
			GetWorld()->GetDeltaSeconds(), false);
*/

	//float realDistToTarget = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _CurrTargetActor->GetActorLocation());
}








void UTWeaponAttack::TaskComplit(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	Super::TaskComplit(_OwnerAI);
}


void UTWeaponAttack::BreakTask(AUnitAI* _OwnerAI)
{
	ResetTask(_OwnerAI);

	ResetAttackData(_OwnerAI);

	Super::BreakTask(_OwnerAI);
}



void UTWeaponAttack::ResetTask(class AUnitAI* _OwnerAI)
{

	if (IsUsingAnimate)
	{
		_OwnerAI->StopAnimate();
		IsUsingAnimate = false;
		return;
	}

	CurrHittingActors.Reset();
	// ** ResetTacticalMoveData();

	_OwnerAI->ClearFocus(EAIFocusPriority::Gameplay);

	// **  for DebugTEST_Actor
	StartPoint = FVector(0.f, 0.f, 0.f);
	EndPoint = FVector(0.f, 0.f, 0.f);
	WeaponLenght = 0.f;
	TraceHit.Actor = nullptr;
	TraceHit.bBlockingHit = false;
}


// --------------------------------------------------------------



void UTWeaponAttack::ResetAttackData(AUnitAI* _OwnerAI)
{
	ActualWpnAttackIndex = -1;
	CurrentAttackInSeries = -1;
	SeriesAttackIndexes.Reset();
	GetWorld()->GetTimerManager().ClearTimer(TH_WeaponAttackTick);
}


bool UTWeaponAttack::IsInAttackSeries()
{
	return CurrentAttackInSeries > 0;
}


int32 UTWeaponAttack::GenerateAttackIndex(AUnitAI* _OwnerAI, AWeaponWorldItem* _WeaponItem, 
	UWeaponDT* _CurrWeaponDT)
{
	int32 currAttackIndex = -1;


	// ** Get Player-selected-Index (from Weapon-component)

	currAttackIndex = _WeaponItem ? _WeaponItem->GetSelectedAttackIndex() : -1;
	if (currAttackIndex != -1)
	{
		ResetAttackData(_OwnerAI);
		SeriesAttackIndexes.Add(currAttackIndex);
		CurrentAttackInSeries = 0;
		return currAttackIndex;
	}


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	Player Has Task
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



	// ** if alredy has correct attack-index

	if (ActualWpnAttackIndex != -1 && _CurrWeaponDT == LastWeaponDT)
	{
		return ActualWpnAttackIndex;
	}


	// ** For new target use only first attack-index [0]

	if (CurrTargetActor != LastTargetActor)
	{
		if (_WeaponItem->IsAttackIndexCorrect(0))
		{
			ResetAttackData(_OwnerAI);
			SeriesAttackIndexes.Add(0);
			CurrentAttackInSeries = 0;
			return 0;
		}
		else
		{
			ResetAttackData(_OwnerAI);
			return -1;
		}
	}



	// **
	// ** Generate new series
	// **
	SeriesAttackIndexes.Reset();
	CurrentAttackInSeries = 0;

	int32 selfSkillDepender = _OwnerAI->UnitOwner->GetSkillDepend_FirstAttackSeries();		// ** @@@@@@@@@@@@@@@@@@@@   Level + CurrWeaponLevel  @@@@@@@@@@@@@@@@@@@@@@@@@

	// ** Start new attack series from random attack-Index: (first || seccond || third)

	int32 prob1 = 50;					/// ** first
	int32 prob2 = 50;					/// ** second     
	int32 prob3 = selfSkillDepender;	/// ** third 
	int32 startFromIndexRND = FMath::RandRange(0, prob1 + prob2 + prob3);

	if (startFromIndexRND > prob1 + prob2)	currAttackIndex = 2;
	else if (startFromIndexRND > prob1)		currAttackIndex = 1;
	else									currAttackIndex = 0;

	if (!_WeaponItem->IsAttackIndexCorrect(currAttackIndex))
	{
		if (_WeaponItem->IsAttackIndexCorrect(0))
		{
			currAttackIndex = 0;
			SeriesAttackIndexes.Add(currAttackIndex);
		}
		else
		{
			ResetAttackData(_OwnerAI);
			return -1;
		}
	}
	else
	{
		SeriesAttackIndexes.Add(currAttackIndex);
	}


/* (++++++++++++++++++7777777777777777777777777777+++++++++++++++++++)
	// ** if its complex attack: (Prepare, Holding, Final)  use only one in series

	UAnimMontage* animate = nullptr;
	animate = _OwnerAI->GetGameAnimation
		(currWeaponDT->AttakParam[ActualWpnAttackIndex].GetAnimKey_PrepateAttack());
	if (animate)
	{
		AnimAttackStage = 0;
		return currAttackIndex;
	}
*/
	


	// ** TEST
	currAttackIndex = 0;   // @@@@@@@@@@@@@@@@@@@@@@@@@@ TEST
	// ** TEST


	// ** Generate num attack in series

	prob1 = 50;									// ** one
	prob2 = 50;		// ** TEST     
	prob3 = 50;		// ** TEST
	// +++++ prob2 = 20 + selfSkillDepender;	// ** two     
	// +++++ prob3 = 5 + selfSkillDepender;		// ** three 
	int32 prob4 = selfSkillDepender;			// ** four 
	int32 attackInSeriesRND = FMath::RandRange(0, prob1 + prob2 + prob3 + prob4);


	// ** TEST
	attackInSeriesRND = prob1 + prob2 + prob3 + prob4 - 3; // ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  TEST
	// ** TEST


	int32 num = 0;
	if (attackInSeriesRND > prob1 + prob2 + prob3)	num = 3;
	else if (attackInSeriesRND > prob1 + prob2)		num = 2;
	else if (attackInSeriesRND > prob1)				num = 1;
	else											num = 0;
	
	for (int32 i = 1; i <= num; ++i)
	{
		if (!_WeaponItem->IsAttackIndexCorrect(currAttackIndex + i) || i >= 3)
			return currAttackIndex;
		SeriesAttackIndexes.Add(currAttackIndex + i);
	}

	return currAttackIndex;
}


int32 UTWeaponAttack::CheckAndGetNextAttackIndex()
{
	//--int32 currIndex = CurrentAttackInSeries;
	//-- ++currIndex;
	++CurrentAttackInSeries;
	return  (SeriesAttackIndexes.Num() > CurrentAttackInSeries) ?
		SeriesAttackIndexes[CurrentAttackInSeries] : -1; 
		// ** (SeriesAttackIndexes.Reset(), -1);
}

/* (-----7777777------)
bool UTWeaponAttack::IsInTacticalMove()
{
	if(TacticalMoveStep > 0)
		return true;
	return false;
}
*/

bool UTWeaponAttack::IsTacticalMoveOwerflow(AWeaponWorldItem* _WeaponItem)
{
	if (_WeaponItem)
	{
		TArray<ETacticalMoveStepLogic>& tacticalMoveStepsLogic = *(_WeaponItem->GetCurrTacticalMoveSteps());
		if (TacticalMoveStep >= tacticalMoveStepsLogic.Num())
			return true;
	}
	return false;
}

bool UTWeaponAttack::IsTacticalMoveTotalOwerflow()
{
	if (TotalTacticalMoveStep >= TotalTacticalMoveStepMAX)
		return true;
	return false;
}

void UTWeaponAttack::ResetTacticalMoveData()
{
	TacticalMoveStep = 0;
	TotalTacticalMoveStep = 0;
}




// --------------------------------------------------------------




bool UTWeaponAttack::CheckAndMoveFromCloserDist(AUnitAI* _OwnerAI, AUnit* _TargetUnit, 
	AWeaponWorldItem* _WeaponItem, ETaskCauser _TaskCauser)
{

	if (IsTacticalMoveOwerflow(_WeaponItem))
		return false;

	UWeaponDT* currWeaponDT = nullptr;
	if(_WeaponItem)
	{
		FItemDT* currWpnItemData = &_WeaponItem->ItemDT;
		currWeaponDT = currWpnItemData->WeaponDT->GetDefaultObject<UWeaponDT>();
	}

	float realDistToTarget = _OwnerAI->GetDistanceToTarget(_TargetUnit, false);
	float minAttackDist = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::min, currWeaponDT);
	float safeDistToTarget = GetDist_SafeSparingWithTarget(_OwnerAI, _TargetUnit, currWeaponDT);

	// ** Too-close to target
	if (realDistToTarget <= minAttackDist)
	{
		EndPoint = FindLoc_OnDistFromTargetByDir(_OwnerAI, _TargetUnit, //  ** BackPoint;
			safeDistToTarget + FMath::RandRange(0.f, _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 3.f));

		if (EndPoint != _OwnerAI->UnitOwner->GetActorLocation())
		{
			
			// ** Navigation Sys  (NOT)
			

			// ** move Back from target (fast move)
			FTaskData SubTask;
			float stopDist = 0.f;
			UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(SubTask, _OwnerAI->UnitOwner, EndPoint,
				_TargetUnit, stopDist, EUnitPose::NormalMove);

			_OwnerAI->SetTask(false, ETaskType::MoveTo, SubTask, _TaskCauser, ETaskPriority::Normal);
			UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Move-Back (if too close)) "));
			return true; /// ** Stop Next
		}
	}
	return false;
}

bool UTWeaponAttack::CheckAndMoveMaxDist(AUnitAI* _OwnerAI, UWeaponDT* _WeaponDT)
{

	if (!CurrTargetActor || !_WeaponDT)
	{
		TaskComplit(_OwnerAI);
		return true;	// ** Stop next code
	}

	float distToTarget = _OwnerAI->GetDistanceToTarget(CurrTargetActor, true);
	float stopDist_MaxDist = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::max, _WeaponDT);

	// ** if Dist Too Far
	if (stopDist_MaxDist < distToTarget) 
	{
		if (IsInAttackSeries())
			ResetAttackData(_OwnerAI);

		FTaskData SubMoveTask;
		UTMoveTo::SetMoveData_MoveToActor(SubMoveTask, _OwnerAI->UnitOwner, CurrTargetActor, 
			stopDist_MaxDist, EUnitPose::Run);

		UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Run-to-target (if too far)) "));
		_OwnerAI->SetTask(false, ETaskType::MoveTo, SubMoveTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		return true;	// ** Stop next code
	}
	return false;
}


bool UTWeaponAttack::CheckOnTacticalMove(AUnitAI* _OwnerAI, AActor* _CurrTargetActor, 
	AWeaponWorldItem* _WeaponItem)
{

	UWeaponDT* weaponDataCDO = _WeaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

	// ** if Weapon just changed
	if (weaponDataCDO != LastWeaponDT)
	{
		TacticalMoveStep = 0;
		LastWeaponDT = weaponDataCDO;
		ContinueTask(_OwnerAI);
		return true; /// ** Stop Next
	}

	FTaskData SubTask;

	float distToTarget_MoveFixer = _OwnerAI->GetDistanceToTarget(_CurrTargetActor, true);
	float optimalDistToTarget = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::optimal, weaponDataCDO);

	// ** Target stand Back-rotate to self
	ERotateToActorType rotateToActorType = GetTargetRelativeRotPosition(_OwnerAI, _CurrTargetActor);
	if (rotateToActorType == ERotateToActorType::Back)
		return false; /// ** Attack


	// ** Tactical Move-time Total finish 
	if(IsTacticalMoveTotalOwerflow())
		return false; /// ** Attack


	// ** if finish tactical-steps and is correct to attack distance
	if (IsTacticalMoveOwerflow(_WeaponItem))
	{
		float safeDistToTarget = GetDist_SafeSparingWithTarget(_OwnerAI, _CurrTargetActor, weaponDataCDO);

		if (distToTarget_MoveFixer > safeDistToTarget * 1.5f)
			TacticalMoveStep = 0;		// ** Do tactical move Again from begin
		else
			return false; /// ** Attack
	}


	// ** Tactical move
	ETacticalMoveStepLogic currTacticalMoveStepLogic = ETacticalMoveStepLogic::none;
	TArray<ETacticalMoveStepLogic>& AllStepsLogic = *(_WeaponItem->GetCurrTacticalMoveSteps());
	int32 stepsNum = AllStepsLogic.Num();
	
	if (TacticalMoveStep >= 0 && TacticalMoveStep < stepsNum)
	{
		currTacticalMoveStepLogic  = AllStepsLogic[TacticalMoveStep];
	}

	++TacticalMoveStep;
	++TotalTacticalMoveStep;

	switch (currTacticalMoveStepLogic)
	{
	case ETacticalMoveStepLogic::RightOrLeft:
	{
															
															
		EndPoint = FindLoc_GoRndSideAroundTarget(_OwnerAI, CurrTargetUnit, rotateToActorType); // ** SidePoint;
		if (EndPoint != _OwnerAI->GetCurrSelfLocation())
		{
			float stopDist = 0.f;
			UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(SubTask, _OwnerAI->UnitOwner, EndPoint,
				_CurrTargetActor, stopDist, EUnitPose::RelaxMove);

			UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----RightOrLeft) "));
			_OwnerAI->SetTask(false, ETaskType::MoveTo, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
			
			return true; /// ** Stop Next
		}
		break;
	}
	case ETacticalMoveStepLogic::Forward:
	{
		EndPoint = FindLoc_GoForwardToTargetOnDist(_OwnerAI, CurrTargetUnit, distToTarget_MoveFixer * 0.5f); // ** ForwardPoint;
		float stopDist = 0.f;
		UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(SubTask, _OwnerAI->UnitOwner, EndPoint,
			_CurrTargetActor, stopDist, EUnitPose::RelaxMove);

		UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Forward"));
		_OwnerAI->SetTask(false, ETaskType::MoveTo, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		
		return true; /// ** Stop Next
	}
	case ETacticalMoveStepLogic::LongWait:
	{
		float time = 2.2f;														// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		UTWait::SetTaskData_WaitParam(SubTask, _OwnerAI->UnitOwner, time);

		UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Wait (Long)"));
		_OwnerAI->SetTask(false, ETaskType::Wait, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		return true; /// ** Stop Next
	}
	case ETacticalMoveStepLogic::NormalWait:
	{

		float time = 1.0f;														// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		UTWait::SetTaskData_WaitParam(SubTask, _OwnerAI->UnitOwner, time);

		UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Wait (Normal)"));
		_OwnerAI->SetTask(false, ETaskType::Wait, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		return true; /// ** Stop Next
	}
	case ETacticalMoveStepLogic::ShortWait:
	{

		float time = 0.4f;														// ** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		UTWait::SetTaskData_WaitParam(SubTask, _OwnerAI->UnitOwner, time);

		UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----Wait (Short)"));
		_OwnerAI->SetTask(false, ETaskType::Wait, SubTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
		return true; /// ** Stop Next
	}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	case ETacticalMoveStepLogic::none:
		/*
			float stopDist = 0.f;
			UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(SubTask, _OwnerAI->UnitOwner, EndPoint,
			_CurrTargetActor, stopDist, EUnitPose::NormalMove);
		*/
		break;

	}

	return false;
}


ERotateToActorType UTWeaponAttack::GetTargetRelativeRotPosition(AUnitAI* _OwnerAI, AActor* _CurrTargetActor)
{
	if (_CurrTargetActor)
	{
		FVector vector_TargetToSelf = (_OwnerAI->GetCurrSelfLocation() - _CurrTargetActor->GetActorLocation()).GetSafeNormal();

		float SideFrontBack = FVector::DotProduct(_CurrTargetActor->GetActorForwardVector(), vector_TargetToSelf);

		if (SideFrontBack < 0)
		{
			return ERotateToActorType::Back;
		}
		else
		{
			float sideLrftRight = FVector::DotProduct(_CurrTargetActor->GetActorRightVector(), vector_TargetToSelf);

			if (sideLrftRight > 0.1f)		
				return ERotateToActorType::ForwardRight;

			else if (sideLrftRight < -0.1f)		
				return ERotateToActorType::ForwardLeft;

			else
				return ERotateToActorType::Forward;
		}
	}
	return ERotateToActorType::none;
}


// **  SelfOprimal*2  orIF(<)  SelfMax orIF(<)  TargetOptimal
float UTWeaponAttack::GetDist_SafeSparingWithTarget(AUnitAI* _OwnerAI, AActor* _CurrTargetActor, UWeaponDT* _WeaponDT)
{
	
	if (!_CurrTargetActor)
		return -1.f;

	float selfMaxDist = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::optimal, _WeaponDT);
	float selfOptimalDist = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::optimal, _WeaponDT); 
	float TargetOptimalDist = GetDist_WeaponParam(_CurrTargetActor, EDistType::optimal, _WeaponDT);

	selfOptimalDist *= 2.f;
	TargetOptimalDist *= 1.5f;

	if (selfOptimalDist > selfMaxDist)
		selfOptimalDist = selfMaxDist;

	if (TargetOptimalDist > selfOptimalDist)
		return TargetOptimalDist;
	else
		return selfOptimalDist;

}


float UTWeaponAttack::GetDist_WeaponParam(AActor* _Actor, EDistType _WpnDistType, UWeaponDT* _WeaponDT)
{
	// ** Get data-dist from curr weapon
	if (_WeaponDT)
	{
		switch (_WpnDistType)
		{
		case EDistType::min:
			return _WeaponDT->MinDist;
		case EDistType::max:
			return _WeaponDT->MaxDist;
		case EDistType::optimal:
			return _WeaponDT->OptimalDist;
		}
	}

	// ** Alternate way (Get data-dist from curr weapon)
	AUnit* unit = Cast<AUnit>(_Actor);
	if (unit)
	{
		AWeaponWorldItem* weapon = unit->GetCurrWeaponItem();
		if (weapon)
		{
			_WeaponDT = weapon->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
			if (_WeaponDT) 
			{
				switch (_WpnDistType)
				{
				case EDistType::min:
					return _WeaponDT->MinDist;
				case EDistType::max:
					return _WeaponDT->MaxDist;
				case EDistType::optimal:
					return _WeaponDT->OptimalDist;
				}
			}
		}

		// ** Generate dist from Unit collision
		else
			switch (_WpnDistType)
			{
			case EDistType::min:
				return unit->GetUnitCapsuleRadius() * 3.f;	
			case EDistType::max:
				return unit->GetUnitCapsuleRadius() * 15.f;	
			case EDistType::optimal:
				return unit->GetUnitCapsuleRadius() * 5.f;	
			}
	}

	// ** Generate native Actor radius
	float CapsuleRadius;
	float CapsuleHalfHaight;
	bool bNonColliding = false;
	bool bIncludeFromChildActors = true;
	_Actor->GetComponentsBoundingCylinder(CapsuleRadius,
		CapsuleHalfHaight, bNonColliding, bIncludeFromChildActors);

	switch (_WpnDistType)
	{
	case EDistType::min:
		return CapsuleRadius * 3.f;
	case EDistType::max:
		return CapsuleRadius * 15.f;
	case EDistType::optimal:
		return CapsuleRadius * 5.f;
	}

	return 0.f;
}


FVector UTWeaponAttack::FindLoc_OnDistFromTargetByDir(AUnitAI* _OwnerAI, AActor* _TargetActor, float _Dist)
{
	FVector dirTragetToSelf = (_OwnerAI->UnitOwner->GetActorLocation() - _TargetActor->GetActorLocation()).GetSafeNormal();
	FVector pointOnDirDist = _TargetActor->GetActorLocation() + dirTragetToSelf * _Dist;
	
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation ResultNavLocation;
	float zoneRadius = _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 3.f;	

	// ** Attempt = 5
	for (int32 i = 0; i < 5; ++i)
	{
		bool bSuccess = NavSys->GetRandomPointInNavigableRadius(pointOnDirDist, zoneRadius, ResultNavLocation);
		if (bSuccess)
			return ResultNavLocation.Location;
	}
	return _OwnerAI->UnitOwner->GetActorLocation();
}



FVector UTWeaponAttack::FindLoc_GoRndSideAroundTarget(AUnitAI* _OwnerAI, AUnit* _TargetUnit, ERotateToActorType _RotateToActorType)
{
	if(!_TargetUnit)
		return _OwnerAI->UnitOwner->GetActorLocation();


	float currDistToTarget = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _TargetUnit->GetActorLocation());
	FVector dirTargetToSelf = (_OwnerAI->GetCurrSelfLocation() - _TargetUnit->GetActorLocation()).GetSafeNormal();

	// ** Calculate point arount Target
	float moveSide = 20.f;  // ** right or left (-X or X)
	if (_RotateToActorType == ERotateToActorType::ForwardLeft)		
		moveSide *= -1;

	FVector newLocation;
	float TargetOptimalDist = GetDist_WeaponParam(_TargetUnit, EDistType::optimal);
	float selfCapsuleWidth = _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 2.f;

	// ** check both sides (2 case)
	for (int32 LeltRight = -1; LeltRight <= 1; LeltRight +=2)
	{
		// ** On closer dist
		if (currDistToTarget < TargetOptimalDist * 3.f)
		{
			moveSide *= 2.5f;

			newLocation = _TargetUnit->GetActorLocation() + FRotator(0.f, moveSide, 0.f).
				RotateVector(dirTargetToSelf) * currDistToTarget;
			if (IsWayCorrect_RayCastCapsule(_OwnerAI, newLocation))
				return newLocation;
		}

		// ** On farer dist
		else
		{
			newLocation = _TargetUnit->GetActorLocation() + FRotator(0.f, moveSide, 0.f).
				RotateVector(dirTargetToSelf) * currDistToTarget;

			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
			FNavLocation ResultNavLocation;
			float zoneRadius = selfCapsuleWidth;
			bool bSuccess = NavSys->GetRandomPointInNavigableRadius(newLocation, selfCapsuleWidth, ResultNavLocation);
			if (bSuccess &&
				IsWayCorrect_RayCastCapsule(_OwnerAI, ResultNavLocation.Location))
				return ResultNavLocation.Location;
		}

		// ** one side is failed. Check other side
		moveSide *= -1;
	}

	return _OwnerAI->UnitOwner->GetActorLocation();
}


FVector UTWeaponAttack::FindLoc_GoForwardToTargetOnDist(AUnitAI* _OwnerAI, AUnit* _TargetUnit, float _Dist)
{
	if (!_TargetUnit)
		return _OwnerAI->UnitOwner->GetActorLocation();

	float targetOptimalDist = GetDist_WeaponParam(_TargetUnit, EDistType::optimal);
	float currDistToTarget = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _TargetUnit->GetActorLocation());
	float selfCapsuleWidth = _OwnerAI->UnitOwner->GetUnitCapsuleRadius() * 2.f;

	if (targetOptimalDist > currDistToTarget - _Dist)
	{
		return _OwnerAI->UnitOwner->GetActorLocation(); // ** no move
	}

	FVector newLocation = _OwnerAI->GetCurrSelfLocation() + _OwnerAI->GetUnitForwardVector() * _Dist;


	// ** Attempt = 5
	for (int32 i = 0; i < 5; ++i)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		FNavLocation ResultNavLocation;
		float zoneRadius = selfCapsuleWidth;
		bool bSuccess = NavSys->GetRandomPointInNavigableRadius(newLocation, selfCapsuleWidth, ResultNavLocation);
		if (bSuccess && 
			IsWayCorrect_RayCastCapsule(_OwnerAI, ResultNavLocation.Location))
				return ResultNavLocation.Location;
	}
	return _OwnerAI->UnitOwner->GetActorLocation();
}





// --------------------------------------------------------------




void UTWeaponAttack::RayCast(AUnitAI* _OwnerAI, FHitResult& _TraceHit,
	FVector _StartPoint, FVector _EndPoint)
{
	FCollisionQueryParams TraceParams(FName("Ray_Cast"), true, _OwnerAI->UnitOwner);
	TraceParams.bTraceComplex = true;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	// ** Single Line
	GetWorld()->LineTraceSingleByObjectType(
		_TraceHit,
		_StartPoint,		// ** start
		_EndPoint,		// ** end
		ObjectQueryParams,
		TraceParams);
}



void UTWeaponAttack::GenerateWeaponContactRayCast(AUnitAI* _OwnerAI,
	AWeaponWorldItem* _WeaponItem, FHitResult& _TraceHit)
{

	StartPoint = _OwnerAI->GetCurrSelfLocation();

	// ** GetPoint from Weapon-Mesh-Sockets:    "sharp_begin" , "sharp_end"
	if (_WeaponItem->ItemDT.MeshPrimitive)
	{
		FTransform endSharpPoint;

		UStaticMesh* staticMesh = Cast<UStaticMesh>(_WeaponItem->ItemDT.MeshPrimitive);
		if (staticMesh)
			endSharpPoint = _WeaponItem->StaticMeshComponent->GetSocketTransform(FName("sharp_end"), ERelativeTransformSpace::RTS_World);
		/// ** beginSharpPoint = _WeaponItem->StaticMeshComponent->GetSocketTransform(FName("sharp_begin"), ERelativeTransformSpace::RTS_World);

		USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(_WeaponItem->ItemDT.MeshPrimitive);
		if (skeletalMesh)
			endSharpPoint = _WeaponItem->SkeletalMeshComponent->GetSocketTransform(FName("sharp_end"), ERelativeTransformSpace::RTS_World);
		/// ** beginSharpPoint = _WeaponItem->SkeletalMeshComponent->GetSocketTransform(FName("sharp_begin"), ERelativeTransformSpace::RTS_World);

		EndPoint = endSharpPoint.GetLocation();
	}

	// ** if unit Han't <Weapon>Mesh
	// ** GetPoint from Unit-Mesh:    "Unit-Location" , "Weapon-Conected-Socket" (currWeaponDT->SocketActivated)
	else
	{
		UWeaponDT* currWeaponDT = _WeaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
		/// ** beginSharpPoint = _OwnerAI->GetUnitSocketParam(currWeaponDT->SocketActivated);
		/// ** FVector upVector = beginSharpPoint.GetRotation().GetAxisX();		// ** Z-Up  X-Forward
		EndPoint = _OwnerAI->GetUnitSocketParam(currWeaponDT->SocketActivated).GetLocation();
	}


	// ** Draw Ray-Hit
	RayCast(_OwnerAI, _TraceHit, StartPoint, EndPoint);
}




void UTWeaponAttack::GenerateWeaponRangeRayCast(AUnitAI* _OwnerAI,
	AWeaponWorldItem* _WeaponItem, FHitResult& _TraceHit,
	float _RayDist)
{
	// (++++++++++++++++++++++++++++++++++++)
/*
	if (_RayDist <= 0)
		_RayDist = 1;

	// ** Start position   (Weapon socket)
	if (_WeaponItem->ItemDT.MeshPrimitive)
	{
		FTransform beginSharpPoint;

		UStaticMesh* staticMesh = Cast<UStaticMesh>(_WeaponItem->ItemDT.MeshPrimitive);
		if (staticMesh)
		{
			beginSharpPoint = _WeaponItem->StaticMeshComponent->GetSocketTransform(FName("sharp_end"), ERelativeTransformSpace::RTS_World);
		}
		else
		{
			USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(_WeaponItem->ItemDT.MeshPrimitive);
			if (skeletalMesh)
				beginSharpPoint = _WeaponItem->SkeletalMeshComponent->GetSocketTransform(FName("sharp_end"), ERelativeTransformSpace::RTS_World);
		}

		StartPoint = beginSharpPoint.GetLocation();
	}
	// ** Start position   (Unit socket)
	else
	{
		UWeaponDT* currWeaponDT = _WeaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
		StartPoint = _OwnerAI->GetUnitSocketParam(currWeaponDT->SocketActivated).GetLocation();
	}



	// ** Driver-Aiming point   (Target position)
	if (_OwnerAI->TasksBuffer.Last().TargetUnit)
	{
		EndPoint = _OwnerAI->TasksBuffer.Last().TargetUnit->GetActorLocation();
	}
	else
	{
		EndPoint = _OwnerAI->TasksBuffer.Last().Location;
	}

	FVector dir = (EndPoint - StartPoint).GetSafeNormal();
	// ** inaccurate shot  (Get from Unit parameter)
	dir.X += FMath::RandRange(-0.05f, 0.05f);
	dir.Y += FMath::RandRange(-0.05f, 0.05f);
	dir.Z += FMath::RandRange(-0.05f, 0.05f);
	// ++++++++++++  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// ++++++++++++  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// ++++++++++++  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@      inaccurate shot ...
	// ++++++++++++  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// ++++++++++++  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	EndPoint = StartPoint + dir * _RayDist;



	// ** Draw Ray-Hit
	RayCast(_OwnerAI, _TraceHit, StartPoint, EndPoint);
	*/
}





void UTWeaponAttack::GenerateWeaponBoundHit(AUnitAI* _OwnerAI, TArray<FHitResult>& _HitResult,
	FVector _StartPoint, FVector _EndPoint, float _SpherDiametr)
{

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
	//++FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(_OwnerAI->UnitOwner);

	UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		_StartPoint,	// ** Start,
		_EndPoint,		// ** End,
		_SpherDiametr,	// **Radius,
		ObjectTypesQuery,
		false,			// ** bool bTraceComplex,
		ActorsToIgnore,
		EDrawDebugTrace::None,			// ** None, ForOneFrame, ForDuration, ++Persistent++ 
		_HitResult,						// ** TArray< FHitResult >& OutHits,
		true,							// ** bIgnoreSelf
		FColor::Red,					// ** TraceColor
		FColor::Red,					// ** TraceHitColor
		4.5f							// ** float DrawTime
	);
}



bool UTWeaponAttack::CheckClearVisionToActor(AUnitAI* _OwnerAI, AUnit* _Target)
{
	if (!_Target)
		return false;

	FHitResult traceHit;
	FVector targetDir = (_Target->GetActorLocation() - _OwnerAI->GetCurrSelfLocation()).GetSafeNormal();
	float distToActor = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _Target->GetActorLocation());
	float moreLongerThenDist = 400.f;
	FVector statrPoint = _OwnerAI->GetCurrSelfLocation();
	FVector endPoint = _OwnerAI->GetCurrSelfLocation() + targetDir * (distToActor + moreLongerThenDist);

	RayCast(_OwnerAI, traceHit, statrPoint, endPoint);

	if (traceHit.GetActor())
	{
		AUnit* target = Cast<AUnit>(traceHit.GetActor());
		if (target)
		{
			return true;
		}
	}
	return false;
}



bool UTWeaponAttack::IsWayCorrect_RayCastCapsule(AUnitAI* _OwnerAI, FVector _EndPoint)
{

	_EndPoint.Z = _OwnerAI->GetCurrSelfLocation().Z;// +_OwnerAI->UnitOwner->GetUnitCapsuleHalfHaight();


	FHitResult traceHit;			// ** TArray<FHitResult> TraceHit;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
	//++FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(_OwnerAI->UnitOwner);
	UKismetSystemLibrary::CapsuleTraceSingleForObjects(
		GetWorld(),
		_OwnerAI->UnitOwner->GetActorLocation(),
		_EndPoint,
		_OwnerAI->UnitOwner->GetUnitCapsuleRadius(),
		_OwnerAI->UnitOwner->GetUnitCapsuleHalfHaight() * 0.8f,
		ObjectTypesQuery,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,	// ** None, ForOneFrame, ForDuration, ++Persistent++
		traceHit,
		true,							 // ** bIgnoreSelf
		FColor::Blue,					// TraceColor
		FColor::Red,					// TraceHitColor
		4.0f							// float DrawTime
	);

	if (traceHit.bBlockingHit)
	{
		return false;
	}
	return true;
}



//--------------------------------------------------------------




bool UTWeaponAttack::CheckAndFindClearVisionPosition(AUnitAI* _OwnerAI)
{
	// ** if need Clear vision
	if (true)
	{
		// ** Vision is Clear (Ok)
		// ++++ if (CheckClearVisionToActor(_OwnerAI, _Target))
		{
			return false; // ** do next Attack stage
		}

		// ** Has Vision point
		// ++++ else if(mHasBestPositionToFire)
		{
			// ++++ if (CheckClearVisionToActor_POINT (mBestPositionToFire, _Target))
			{
				return false; // ** do next Attack stage
			}
			// ++++ else
			{
				// ++++ mHasBestPositionToFire = false;
			}
		}

		// ++++ if (!mHasBestPositionToFire)
		{
			FindBestFiringPoint( _OwnerAI);
			
			// ++++  mAttackCountTotal = 0;
			// ++++  mAttackCurSeriesCount = 0;

			return true;
		}
	}

	return false;
}


void UTWeaponAttack::FindBestFiringPoint(AUnitAI* _OwnerAI)
{
	return;
}


bool UTWeaponAttack::CorectDistBeforeAttack(AUnitAI* _OwnerAI, AActor* _CurrTargetActor, AWeaponWorldItem* _WeaponItem)
{
	// +++++++++++++++++++++++++ if (!mHasBestPositionToFire)
	//if (true)
	//{
		// +++++++++++++++++++ Move To ClearVisiblePoint Point
	//	return true;
	//}

	// ++ Correct dist to Target
	{
		UWeaponDT* weaponDataCDO = _WeaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
	

		float realDistToTarget = FVector::Distance(_OwnerAI->GetCurrSelfLocation(), _CurrTargetActor->GetActorLocation());
		float optimalDistToTarget = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::optimal, weaponDataCDO);



		//----float minAttackDist = GetDist_WeaponParam(_OwnerAI->UnitOwner, EDistType::min, weaponDataCDO);
		if (FMath::Abs(realDistToTarget - optimalDistToTarget) > 30.f)
		{

			EndPoint = FindLoc_OnDistFromTargetByDir(_OwnerAI, _CurrTargetActor, optimalDistToTarget); ///  ** FVector optimalPoint;
				
			if (EndPoint != _OwnerAI->UnitOwner->GetActorLocation())
			{
				// ** move Back/Front to target (fast move)
				FTaskData SubMoveTask;
				//---777--- SubMoveTask.TaskCauser = ETaskCauser::ChildTask;
				float stopDist = 0.f;
				UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(SubMoveTask, _OwnerAI->UnitOwner, EndPoint,
					_CurrTargetActor, stopDist, EUnitPose::NormalMove);
				UE_LOG(LogTemp, Warning, TEXT("Task::Attack,    Start-SubTask:  Move----CorrectDist-before-Attack"));
				_OwnerAI->SetTask(false, ETaskType::MoveTo, SubMoveTask, ETaskCauser::ChildTask, ETaskPriority::Normal);
				return true; /// ** Stop Next
			}
		}
	}

	return false;
}


bool UTWeaponAttack::AttackAction(AUnitAI* _OwnerAI)
{

	// ++++ mIsTacticalMoving = false;
	// ++++ mTacticalMoveCountTotal = 0;
	// ++++ mTacticalMoveCurSeriesCount = 0;

	return false;
}





bool UTWeaponAttack::IdentifyTask(AUnitAI* _OwnerAI)
{

	FTaskData& task = _OwnerAI->TasksBuffer.Last();

	if (task.Actor.Num() == 0)
		return false;
	if (task.Int32Param.Num() == 0)
		return false;
	
	if (task.Int32Param[0] >= 0)    
	{
		ActualWpnAttackIndex = task.Int32Param[0];		// ** selected weapon-Index  
	}

	LastTargetActor = CurrTargetUnit;
	CurrTargetActor = task.Actor[0];
	AUnit* checkTargetOnUnit = Cast<AUnit>(CurrTargetActor);
	if (checkTargetOnUnit)	CurrTargetUnit = checkTargetOnUnit;

	return true;
}






// ** ----------------  Static func  ---------------




void UTWeaponAttack::SetAttackData_AttackUnit(FTaskData& _TaskData, AActor* _TargetActor, int32 _AttackIndex)
{
	_TaskData.Actor.Add(_TargetActor);
	_TaskData.Int32Param.Add(_AttackIndex);
}






