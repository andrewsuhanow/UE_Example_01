

// #include "Base/Amunition/WeaponDT.h"
#include "WeaponDT.h"

UWeaponDT::UWeaponDT()
{
	if (PoseLocomotionParamMOD.Num() == 0)
	{
		PoseLocomotionParamMOD.Add(FPoseLocomotion());
		PoseLocomotionParamMOD.Last().Pose = EUnitPose::RelaxMove;
		PoseLocomotionParamMOD.Last().MoveSpeed = 0.f;
		PoseLocomotionParamMOD.Last().RotateSpeed = 0.f;
	}
}






EAnimationKey FAttakParam::GetAnimKey_Attack()
{
	if (AnimationKEY.Num() > 0)
		return AnimationKEY[0];
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponDT:  '%s'   _____Weapon dont has any Attack animate"), *StaticStruct()->GetName());
		return EAnimationKey::none;
	}
}
EAnimationKey FAttakParam::GetAnimKey_AlternateAttack()
{
	if (AnimationKEY.Num() > 1)
		return AnimationKEY[1];
	else
		return GetAnimKey_Attack();
}


EAnimationKey FAttakParam::GetAnimKey_AttackInPlace()
{
	if (AnimationKEY.Num() > 2)
		return AnimationKEY[2];
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponDT:  '%s'   _____Weapon dont has any AttackOnePlace animate"), *StaticStruct()->GetName());
		return EAnimationKey::none;
	}
}
EAnimationKey FAttakParam::GetAnimKey_AlternateAttackInPlace()
{
	if (AnimationKEY.Num() > 3)
		return AnimationKEY[3];
	else
		return GetAnimKey_AttackInPlace();
}


/*
EAnimationKey FAttakParam::GetAnimKey_PrepateAttack()
{
	if (AnimationKeyNum > 2)
		return AnimationKEY[2];
	else
		return EAnimationKey::none;
}

EAnimationKey FAttakParam::GetAnimKey_AttackHolding()
{
	if (AnimationKeyNum > 3)
		return AnimationKEY[3];
	else
		return EAnimationKey::none;
}
*/