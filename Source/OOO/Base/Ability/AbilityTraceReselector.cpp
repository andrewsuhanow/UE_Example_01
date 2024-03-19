

// #include "Base/Ability/AbilityTraceReselector.h"
#include "AbilityTraceReselector.h"


#include "../Unit/Base/Unit.h"
#include "../Controller/UnitAI.h"

#include "../Ability/AbilityDT.h"

#include "../WorldObject/GameObject/MovableObject.h"
#include "Struct/AbilityTraceReselectorDT.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"  // ** SpawnSystemAtLocation

// --- TEST ---

#include "DrawDebugHelpers.h"			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@






AAbilityTraceReselector::AAbilityTraceReselector()
{

	PrimaryActorTick.bCanEverTick = true;




	//SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	//SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // QueryAndPhysics  // QueryOnly  // PhysicsOnly // NoCollision
	//SphereCollision->SetCollisionProfileName(TEXT("NoCollision"));  // "Pawn" // OverlapAll  // NoCollision
	//SphereCollision->SetSphereRadius(InitAgentRadius, true);
	//SphereCollision->SetEnableGravity(false);

	//RootComponent = SphereCollision;

	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);




	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	//ProjectileMovement->ProjectileGravityScale = 0.0f;



	//StMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//StMash->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // QueryAndPhysics
	//StMash->SetCollisionProfileName(TEXT("NoCollision"));  // "Pawn"
	//StMash->SetEnableGravity(false);  // "Pawn"
	//StMash->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	////StMash->SetRelativeScale3D(FVector(2, 2, 2));

	//StMash->SetupAttachment(RootComponent);




/*	if (_AgressorSelf && _BulletEffect && Collision)
	{
		BulletEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(_BulletEffect, Collision, NAME_None,
			FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::KeepRelativeOffset, true, true);
	}
*/


}


void AAbilityTraceReselector::CastAbility()
{
	if (!CasterUnit ||
		!AbilityCDO ||
		!AbilityStep ||
		!AbilityTraceReselectorDT)
	{
		FinishEffectDestroyActor();
		return;
	}



	switch (AbilityTraceReselectorDT->AbilityTraseForm)
	{
	////case EAbilityTraseForm::ApplayEffectToUnit:
	////	
	////	FinishEffectDestroyActor(); // ....   ERROR
	////	return;

	case EAbilityTraseForm::SpawnAgentAtLoc:

		SetSphereCollision(AbilityTraceReselectorDT->InitAgentRadius);
		CastAbilityFinish();

		// ** Play Hit-Effect
		if (AbilityTraceReselectorDT->TransferVisualEffect)
			TraceEffectComponent = PlayVisualEffect(AbilityTraceReselectorDT->TransferVisualEffect);

		return; // ++77++ break;
	case EAbilityTraseForm::FlyAgentToGoal:

		SetSphereCollision(AbilityTraceReselectorDT->InitAgentRadius);
		InitMoveComponent();

		if (FlyToDir)
		{
			FVector goalPoint = (VictimUnit) ? CasterUnit->GetActorLocation() : GoalLocation;
			GoalLocation = CasterUnit->GetActorLocation() + 
					(goalPoint - CasterUnit->GetActorLocation()).GetSafeNormal() * 10000.f;
		}

		break;
	case EAbilityTraseForm::ConeInFront:

		InitConeComponent();

		break;
	}


	// **   Fly-Agent-Effect  Play-Visual-Effect()
	TraceEffectComponent = PlayVisualEffect(AbilityTraceReselectorDT->TransferVisualEffect);//--- , effectDuration);
	// ++++++if( ribon effect && TraceEffectComponent)
	{	
		//+++++VisualEffectComponent->SetFirstEffectPoint(CasterUnitSocketLocation());
	}


}




void AAbilityTraceReselector::CastAbilityFinish()
{
	if (!IsOlredyDoneFinalHit)
	{
		if (!CasterUnit ||
			!AbilityCDO ||
			!AbilityStep ||
			!AbilityTraceReselectorDT)
		{
			FinishEffectDestroyActor();
			return;
		}

		//---FAbilityTraceReselectorDT& traceReselectorDT = AbilityTraceReselectorDT;

	
	
		// ** Stop Fly
		if (ProjectileMovement)
		{
			ProjectileMovement->Velocity = FVector(0, 0, 0);
			ProjectileMovement->InitialSpeed = 0.f;
			ProjectileMovement->MaxSpeed = 0.f;
			ProjectileMovement->UpdateComponentVelocity();
		}

		GetWorld()->GetTimerManager().ClearTimer(TH_DistanceChecker);
		IsOlredyDoneFinalHit = true;

		// ** Play Hit-Effect
		if (AbilityTraceReselectorDT->ExplosionVisualEffect)
		{
			TraceEffectComponent->DestroyComponent();
			TraceEffectComponent = PlayVisualEffect(AbilityTraceReselectorDT->ExplosionVisualEffect);
			// ** Effect-Finish DELEGATE
			if (TraceEffectComponent)
				TraceEffectComponent->OnSystemFinished.AddDynamic(this, &ThisClass::OnNiagaraEffectFinished);
		}
		// ** set effect duration
		if (AbilityTraceReselectorDT->DurationVisualEffect)
		{
			DurationEffectComponent = PlayVisualEffect(AbilityTraceReselectorDT->DurationVisualEffect);
			LifeTimeAfterHit = AbilityTraceReselectorDT->LifeTimeAfterHit;
		}
		





		// ** Set new radius
		if (SphereCollision && AbilityTraceReselectorDT->ChangeRadiusAfterHiting != 0.f)
			SphereCollision->SetSphereRadius(AbilityTraceReselectorDT->ChangeRadiusAfterHiting, true);


		// ** Activate-Life-Time
		GetWorld()->GetTimerManager().SetTimer(TH_LifeTimeChecker, this, 
			&ThisClass::LifeTimeChecker, 0.1f, true); // ** GetWorld()->GetDeltaSeconds() * 0.1f
	}
}








void AAbilityTraceReselector::DistanceChecker()
{


	if (!CasterUnit ||
		!AbilityCDO ||
		!AbilityStep ||
		!AbilityTraceReselectorDT)
	{
		FinishEffectDestroyActor();
		return;
	}

	//---FAbilityTraceReselectorDT& traceReselectorDT = AbilityTraceReselectorDT;



	float distToTarget = 0.f;

	// ** Recheck fly dist
	if (VictimUnit)
	{
		distToTarget = FVector::Distance(GetActorLocation(), VictimUnit->GetActorLocation());
		
		// ** Trackint TargetUnit
		if (AbilityTraceReselectorDT->IsTrackingTarget)
		{
			ProjectileMovement->Velocity = (VictimUnit->GetActorLocation() - GetActorLocation()).GetSafeNormal() * 1000.f;
			ProjectileMovement->UpdateComponentVelocity();
		}
	}
	else
	{
		distToTarget = FVector::Distance(CasterUnit->GetActorLocation(), GoalLocation);
	}


	if (distToTarget > 30.f)
	{
		GetWorld()->GetTimerManager().SetTimer(TH_DistanceChecker, this, &ThisClass::DistanceChecker, 0.0001f * distToTarget, false); // ** GetWorld()->GetDeltaSeconds() * 0.1f
	}
	else
	{
		if (!FlyToDir)
			CastAbilityFinish();
		else
			FinishEffectDestroyActor();
	}
}



void AAbilityTraceReselector::LifeTimeChecker()
{
	if (LifeTimeAfterHit <= 0.0f && !TraceEffectComponent)
		FinishEffectDestroyActor();
	else 
		LifeTimeAfterHit -= 0.1f;
  
}


void AAbilityTraceReselector::OnNiagaraEffectFinished(UNiagaraComponent* _FinishedComponent)
{
	TraceEffectComponent->DestroyComponent();
	TraceEffectComponent = nullptr;
}


void AAbilityTraceReselector::FinishEffectDestroyActor()
{
	GetWorld()->GetTimerManager().ClearTimer(TH_DistanceChecker);
	GetWorld()->GetTimerManager().ClearTimer(TH_LifeTimeChecker);
	Destroy();
}

void AAbilityTraceReselector::OnOverlapBegin(UPrimitiveComponent* thisComp, AActor* OtherActor, 
												UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
												bool bFromSweep, const FHitResult& SweepResult)
{

	if (!CasterUnit ||
		!AbilityCDO ||
		!AbilityStep ||
		!AbilityTraceReselectorDT)
	{
		FinishEffectDestroyActor();
		return;
	}


	if (!AbilityTraceReselectorDT->FlyThroughtAll)
	{
		CastAbilityFinish();
	}



	AUnit* unit = Cast<AUnit>(OtherActor);
	if (unit)
	{
		ApplayUnitEffect(unit);
	}
	

	//+++AMovableObject* movableObject = Cast<AMovableObject>(OtherActor);
	//+++AStaticObject* staticObject = Cast<AStaticObject>(OtherActor);


/*	AMovableObject* movableObject = Cast<AMovableObject>(OtherActor);
	AStaticObject* staticObject = Cast<AStaticObject>(OtherActor);
	AUnit* unit = Cast<AUnit>(OtherActor);

	if (!FlyThroughtAll)
	{
		ProjectileMovement->Velocity = FVector(0, 0, 0);
		ProjectileMovement->InitialSpeed = 0.f;
		ProjectileMovement->MaxSpeed = 0.f;
		ProjectileMovement->ProjectileGravityScale = 0.f;
		ProjectileMovement->UpdateComponentVelocity();
		GetWorld()->GetTimerManager().ClearTimer(TH_DistanceChecker);


		if (ChangeRadiusAfterHiting != InitAgentRadius)
		{

			float effectDuration = PlayVisualEffect(ExplosionVisualEffect);   // @@@@@@@@@@@@@@@@@@@@@@@@@@@ Duration 7777
			if(LifeTimeAfterHit < effectDuration)
				LifeTimeAfterHit = effectDuration;

			if (IsOlredyHasFinalHit)
			{
				SphereCollision->SetSphereRadius(ChangeRadiusAfterHiting, true);

				//+++ Play AOE VisualEffect

				//+++++++GetWorld()->GetTimerManager().SetTimer(TH_LifeTimeChecker, this, &ThisClass::LifeTimeChecker,
				//+++++++	LifeTimeAfterHit, false); // ** GetWorld()->GetDeltaSeconds() * 0.1f

				IsOlredyHasFinalHit = false;
			}

			if (unit)
			{
				//++++unit->ApplayDamage();
			}


			/// // ** Detect by current collision
			///TArray<AActor*> ActorsRef;
			///SphereCollision->GetOverlappingActors(ActorsRef, AUnit::StaticClass());
			///for (int32 i = 0; i < ActorsRef.Num(); ++i)
			///{
			///	//++++unit->ApplayDamage();
			///}
		}
	}
	else
	{
		if (unit)
		{
			//++++unit->ApplayDamage();
		}
	}
*/


	/*
	//	HitUnit->CurrAiController->AgressorUnit = Agressor_BaseUnit;



	// **************************************     Rotate to side
	//HitUnit->bUseControllerRotationYaw = true;
	//HitUnit->SetActorRotation((FRotationMatrix(Agressor_BaseUnit->CurrAiController->GetControlRotation()).GetScaledAxis(EAxis::X) * (-1)).Rotation());





	//+++if (TargettEffect)
	//+++	TargettEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
	//+++										TargettEffect, SweepResult.ImpactPoint);
	*/
}




void AAbilityTraceReselector::ApplayUnitEffect(AUnit* _TargetUnit)
{
	if (!CasterUnit ||
		!AbilityCDO ||
		!AbilityStep ||
		!AbilityTraceReselectorDT)
	{
		FinishEffectDestroyActor();
		return;
	}


	if (_TargetUnit == CasterUnit)
	{
		return;
	}


	int32 UnitEffectsNum = AbilityStep->UnitEffectDT.Num();
	for (int32 i = 0; i < AbilityTraceReselectorDT->UnitEffectIndexes.Num(); ++i)
	{
		if (i >= UnitEffectsNum)
			continue;

		_TargetUnit->AddUnitEffect(&AbilityStep->UnitEffectDT[i]);
	}
	
	




	//--------------------TEST-----------------------------------
	DrawDebugSphere
	(
		GetWorld(),
		_TargetUnit->GetActorLocation(),
		10,
		12,
		FColor::Red,
		false,
		4.f,
		10,
		10.f
	);
//--------------------TEST-----------------------------------

}





UNiagaraComponent* AAbilityTraceReselector::PlayVisualEffect(UNiagaraSystem* _VisualEffect)//--, 
															//--float& _EffectDuration)
{
	if (!_VisualEffect)
		return nullptr;
	
	UNiagaraComponent* selfVisualEffectTMP = UNiagaraFunctionLibrary::SpawnSystemAttached(
		_VisualEffect,
		SphereCollision,
		NAME_None,
		FVector(0.f),
		FRotator(0.f),
		EAttachLocation::Type::KeepRelativeOffset,
		true,
		true);


	//---
	//----_EffectDuration = selfVisualEffectTMP->GetAsset()->GetWarmupTime();//---- selfVisualEffectTMP->GetDesiredAge();

	return selfVisualEffectTMP;
}




void AAbilityTraceReselector::SetSphereCollision(float _SphereSize)
{

	if (!SphereCollision)
	{
		

		SphereCollision = NewObject<USphereComponent>(this, TEXT("SphereCollision"));
		SphereCollision->RegisterComponent();

		RootComponent = SphereCollision;

		SphereCollision->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // QueryAndPhysics  // QueryOnly  // PhysicsOnly // NoCollision
		SphereCollision->SetCollisionProfileName(TEXT("OverlapAll"));		// "Pawn" // OverlapAll  // NoCollision
		SphereCollision->SetSphereRadius(_SphereSize, true);
		SphereCollision->SetEnableGravity(false);
	

		SetActorLocation(StartLocation);

		// ** Overlap
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	}
	else
	{
		SphereCollision->SetSphereRadius(_SphereSize, true);
	}


	 // ** Detect by current collision
	TArray<AActor*> boundingActors;
	SphereCollision->GetOverlappingActors(boundingActors, AUnit::StaticClass());
	for (int32 i = 0; i < boundingActors.Num(); ++i)
	{
		ApplayUnitEffect(Cast<AUnit>(boundingActors[i]));
	}
}



void AAbilityTraceReselector::InitMoveComponent()
{
	if(!CasterUnit ||
		!AbilityCDO ||
		!AbilityStep ||
		!AbilityTraceReselectorDT)
	{
		FinishEffectDestroyActor();
		return;
	}



	//---FAbilityTraceReselectorDT& traceReselectorDT = AbilityTraceReselectorDT;


	ProjectileMovement = NewObject<UProjectileMovementComponent>(this, TEXT("ProjectileMovementComp"));
	ProjectileMovement->RegisterComponent();
	
	float distToTarget = 0.f;

	if (VictimUnit)
	{
		//ProjectileMovement->Velocity = GetActorForwardVector() * 1000.f;
		ProjectileMovement->Velocity = (VictimUnit->GetActorLocation() - CasterUnit->GetActorLocation()).GetSafeNormal() * 1000.f;
		distToTarget = FVector::Distance(CasterUnit->GetActorLocation(), VictimUnit->GetActorLocation());
	}
	else
	{
		ProjectileMovement->Velocity = (GoalLocation - CasterUnit->GetActorLocation()).GetSafeNormal() * 1000.f;
		distToTarget = FVector::Distance(CasterUnit->GetActorLocation(), GoalLocation);
	}

	// ** ProjectileMovement->Velocity = FVector(1000.f, 0, 0);
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->InitialSpeed = AbilityTraceReselectorDT->AgentSpeed; // ** 500.f;
	ProjectileMovement->MaxSpeed = AbilityTraceReselectorDT->AgentSpeed; // **  1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->UpdateComponentVelocity();


	GetWorld()->GetTimerManager().SetTimer(TH_DistanceChecker, this, &ThisClass::DistanceChecker, 0.0001f * distToTarget, false); // ** GetWorld()->GetDeltaSeconds() * 0.1f
}



void AAbilityTraceReselector::InitConeComponent()
{
	//++FRotator Side = UKismetMathLibrary::FindLookAtRotation(Start, End);
	//++SetActorRotation(Side);
	//++SetActorLocation(Start + Side.Vector() * 100.f);

	SetSphereCollision();
}








void AAbilityTraceReselector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}







/*
AAbilityTraceReselector::AAbilityTraceReselector()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAbilityTraceReselector::BeginPlay()
{
	Super::BeginPlay();
	
}

*/





