
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "../../Unit/Enum/UnitPose.h"

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

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")				
	//---------------------	float UnitMoveSpeed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		float VelocitySpeed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		float Direction = 0;

	// ** Side = (-1:0:1)	  Speed = (150:300:600)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		float RotateSpeedSide = 0;



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
	// ** DELEGATE_Get( Get/Set, CurrentMontage, IsPlayTOP, MontageStartTime, MontageTimePause, PoseLocomotion, GET_RotateSpeed, GET_MoveSpeed)

	//UFUNCTION(BlueprintCallable)
	///////////////	void GetAnimMontageParam(struct FAnimMontageParam AnimMontageParam);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")												
		EUnitPose PoseLocomotion = EUnitPose::Stand;

		// **   Idle Relax or Idle ready 
	//UPROPERTY()
	//+++++++++++++++++++++++++		bool IsAttackReady_Pose = false;
};
