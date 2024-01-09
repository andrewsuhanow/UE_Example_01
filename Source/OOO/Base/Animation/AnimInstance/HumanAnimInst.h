
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

//----#include "../../Animation/Enum/AnimPose.h"

#include "../../Unit/Enum/UnitPose.h"
#include "../../Amunition/Enum/WeaponType.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Rotate")	
		float RotateAnimSpeedSide = 0;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_Crawl		= 200.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_Crouch		= 300.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_RelaxMove	= 400.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_NormalMove = 800.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_Run		= 1200.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_Sprint		= 1600.f;
	UPROPERTY(BlueprintReadonly, Category = "OOO_Rotate")	float HandlerRotateSpeed_Fly		= 1600.f;
	UFUNCTION(BlueprintCallable)		
		void SetRotateSpeedHandle(TArray<float>& _RotateSpeedSwetcher);
	UFUNCTION(BlueprintCallable)		
		void SetRotateAnimSpeed(float _NewSpeed);


	// ** TOP rotate
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Movement")
		FVector2D RotateTOP = FVector2D(0, 0);

	UFUNCTION(BlueprintCallable)
		void TopRotateAngle(float DeltaTime);


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		class UAnimMontage* CurrentMontage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		bool IsPlayTOP = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		float MontageStartTime = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_AnimMontage")
		float MontageTimePause = 0.f;

//public:

	//--------------------------------------

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//	float ProgressPose = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//	bool Block = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//	bool HoldingAttack = false;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_State")
	//	TMap<EAnimPose, UAnimSequence*> HoldingPose;

public:

	// ** Sit, Crouch, MoveSlow, MoveFast, Run, Sptint 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")												
		EUnitPose UnitPose = EUnitPose::RelaxMove;

	// ** HandFight, Sword, LongSword, Pike, Bow, RupidGun, Rifle, ...
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_State")												
		EWeaponType WeaponAnimType = EWeaponType::Locomotion;

	UFUNCTION(BlueprintCallable)
		void SetWeaponAnimType(EWeaponType _NewWeaponAnim);
	
//----------
//-----------	UFUNCTION(BlueprintCallable)
//---------		float AAA(EWeaponType _NewWeaponAnim) { return 0; };
		// **   Idle Relax or Idle ready 
	//UPROPERTY()
	//+++++++++++++++++++++++++		bool IsAttackReady_Pose = false;
};
