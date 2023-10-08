
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HumanAnimInst.generated.h"


UCLASS()
class OOO_API UHumanAnimInst : public UAnimInstance
{
	GENERATED_BODY()


public:

	UHumanAnimInst();
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		class AUnit* UnitOwner;

	UFUNCTION(BlueprintCallable)
		virtual void GetOwner();



public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")				
		float MoveSpeed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		float Direction = 0;

	// ** Side = (-1:0:1)	  Speed = (150:300:600)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		float RotateSpeedSide = 0;

	// ** Rotate speed (Set for Creature in Editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float SlowRotateSpeed = 150.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float MediumRotateSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float FastRotateSpeed = 600.f;

	// ** TOP rotate
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		FVector2D RotateTOP = FVector2D(0, 0);

	UFUNCTION(BlueprintCallable)
		void TopRotateAngle(float DeltaTime);


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		class UAnimMontage* CurrentMontage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		float MontageStartTime = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		float MontageTimePause = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		bool IsPlayTOP = true;
	// ** DELEGATE_Get( Get/Set, CurrentMontage, IsPlayTOP, MontageStartTime, MontageTimePause, GET_RotateSpeed, GET_MoveSpeed)


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")												
	//+++++++++++++++++++++++++	EUnitPose PoseLocomotion = EUnitPose::Stand;

		// **   Idle Relax or Idle ready 
	//UPROPERTY()
	//+++++++++++++++++++++++++		bool IsAttackReady_Pose = false;
};
