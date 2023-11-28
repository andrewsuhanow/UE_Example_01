
// ** #include "Base/Animation/Enum/AnimationKey.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EAnimationKey : uint8
{
	none,
	
	use,

	equip,
	unequip,

	attack_1_novice,	
	attack1,
	attack_2_novice,
	attack2,
	attack2_altern,
	attack3,
	attack3_altern,
	attack4,
	attack4_altern,
	attack5,

	prepare_and_cast,
	cast,
	prepare_to_cast,


	//-----block,
	parrir,

	dodge_lft,
	dodge_rt,
	dodge_fwd,
	dodge_bwd,

	hit0_easy,
	hit1_normal,
	hit2_push,
	hit3_fall,
	dead,

	up_barier03,
	down_barier03,
	up_barier06,
	down_barier06,
	up_barier1,
	down_barier1,
	up_barier15,
	down_barier15, 

	jump_forward, 
	big_jump_forward, 

	spell_Prepare_mid,
	spell_cast_mid,
	spell_Prepare_up,
	spell_cast_up,
	spell_Prepare_dwn,
	spell_cast_dwn, 

	throw_Prepare_mid,
	throw_cast_mid,
	throw_Prepare_up,
	throw_cast_up,
	throw_Prepare_dwn,
	throw_cast_dwn,

	stun,
	indjure,				// ** hromanie

	sleep1_prepare,
	sleep1_idle,
	sleep2_prepare,
	sleep2_idle,
	sleep3_prepare,
	sleep3_idle,

	cover_idle_stand,
	cover_idle_sit,
	cover_up,
	cover_left,
	cover_right,
	
	MAX
};