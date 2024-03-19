

// #include "Base/Ability/AbilityTraceReselector.h"
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enum/AbilityTraseForm.h"

#include "AbilityTraceReselector.generated.h"

UCLASS()
class OOO_API AAbilityTraceReselector : public AActor
{
	GENERATED_BODY()
	





public:

	AAbilityTraceReselector();

	//++++++++++++  FlyForward

	UPROPERTY()
		bool IsOlredyDoneFinalHit = false;

	UPROPERTY()
		class AUnit* CasterUnit;

	UPROPERTY()
		class UAbilityDT* AbilityCDO;

	// ** UPROPERTY()
		struct FAbilityStep* AbilityStep;
	// ** UPROPERTY()
		struct FAbilityTraceReselectorDT* AbilityTraceReselectorDT;
	
	UPROPERTY()
		float LifeTimeAfterHit = 0.f;

	UPROPERTY()
		int32 ChyainingActorIndex = 0;


/*
	UPROPERTY()
		EAbilityTraseForm AbilityTraseForm = EAbilityTraseForm::ApplayEffectToUnit;

	
	UPROPERTY()
		int32 TraceReselectorIndex = -1;
	
	UPROPERTY()
		float MaxDist = 500.f;			//7777777777777777777777777777777  MaxDist
	UPROPERTY()
		float InitAgentRadius = 10.f;
	UPROPERTY()
		float ChangeRadiusAfterHiting = 0.f;
	UPROPERTY()
		float AgentSpeed = 1000.f;
	UPROPERTY()
		bool FlyThroughtAll = false;
	UPROPERTY()
		bool IsTrackingTarget = false;
	//--UPROPERTY()
	//--	bool IsSelectNewTarget = false
	
*/

	UPROPERTY()
		FVector StartLocation;			
	
	UPROPERTY()
		class AUnit* VictimUnit;		// ** Target is Unit (tracking Unit target)
	UPROPERTY()
		FVector GoalLocation;			// ** Target is point (explosion on it)
	UPROPERTY()
		bool FlyToDir = false;	// ** no concrete point (fly to dirrection through "fff" and no explosion if nothing hit)


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UStaticMeshComponent* StMash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class USkeletalMeshComponent* SkMash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UProjectileMovementComponent* ProjectileMovement;

	// ** Transfer Visual Effect
	UPROPERTY()
		class UNiagaraComponent* TraceEffectComponent;
	UPROPERTY()
		class UNiagaraComponent* DurationEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UNiagaraSystem* TransferVisualEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UNiagaraSystem* ExplosionVisualEffect;
	UFUNCTION(BlueprintCallable)
		void OnNiagaraEffectFinished(UNiagaraComponent* _FinishedComponent);
	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//---	class UNiagaraSystem* DurationVisualEffect;



public:

	UFUNCTION(BlueprintCallable)
		void CastAbility();

	UFUNCTION(BlueprintCallable)
		void CastAbilityFinish();

	UPROPERTY()
		FTimerHandle TH_LifeTimeChecker;

	UFUNCTION(BlueprintCallable)
		void LifeTimeChecker();


	UPROPERTY()
		FTimerHandle TH_DistanceChecker;
	UFUNCTION(BlueprintCallable)
		void DistanceChecker();


	//--UFUNCTION()
	//--void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* thisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void ApplayUnitEffect(class AUnit* _TargetUnit);

	UFUNCTION(BlueprintCallable)
		UNiagaraComponent* PlayVisualEffect(class UNiagaraSystem* _VisualEffect);//---, float& _EffectDuration);

	UFUNCTION(BlueprintCallable)
		void SetSphereCollision(float _SphereSize = 5.0f);
	UFUNCTION(BlueprintCallable)
		void InitMoveComponent();
	UFUNCTION(BlueprintCallable)
		void InitConeComponent();

	UFUNCTION(BlueprintCallable)
		void FinishEffectDestroyActor();

public:	

	virtual void Tick(float DeltaTime) override;




/*
protected:

	virtual void BeginPlay() override;
*/


};
